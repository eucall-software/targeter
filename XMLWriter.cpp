#include <QStandardPaths>
#include <QXmlStreamWriter>
#include <QtXml/QDomDocument>
#include <QtCore/QtCore>

#include <QRegularExpression>
#include <QMetaObject>
#include <opencv2/imgproc/imgproc.hpp>
#include "targeterimage.h"
#include "settings2xml.hpp"
#include "XMLWriter.h"


// saving settings class

XMLWriter::XMLWriter()
{
	m_pXMLFile = nullptr;
}

XMLWriter::~XMLWriter()
{
	if (m_pXMLFile)
		delete m_pXMLFile;
}

void XMLWriter::normalizeString(QString& s)
{
	s.remove(QRegularExpression("[" + QRegularExpression::escape("'!*,?|¡¿") + "]"));

	// Performance: Check for characters
	if (s.contains(QRegularExpression("[" + QRegularExpression::escape("$/:ÀÁÄÙÛÜàáäçèéêëïñóöùûü") + "]")))
	{
		// Special Characters 
		// Escape function is a safety measure in case you accidentally insert "^" in the square brackets.
		s.replace(QRegularExpression("[" + QRegularExpression::escape(":/") + "]"), "-");
		s.replace(QRegularExpression("[$]"), "s");

		// Upper Case
		s.replace(QRegularExpression("[ÁÀ]"), "A");
		s.replace(QRegularExpression("[Ä]"), "Ae");
		s.replace(QRegularExpression("[ÜÛÙ]"), "U");

		// Lower Case
		s.replace(QRegularExpression("[áà]"), "a");
		s.replace(QRegularExpression("[ä]"), "ae");
		s.replace(QRegularExpression("[ç]"), "c");
		s.replace(QRegularExpression("[ëêéè]"), "e");
		s.replace(QRegularExpression("[ï]"), "i");
		s.replace(QRegularExpression("[ñ]"), "n");
		s.replace(QRegularExpression("[óö]"), "o");
		s.replace(QRegularExpression("[ûù]"), "u");
		s.replace(QRegularExpression("[ü]"), "ue");
	}
}

bool XMLWriter::openXMLFile(QString XMLFilename, QFlags<QIODevice::OpenModeFlag> flag)
{
	normalizeString(XMLFilename);

	if (m_pXMLFile == nullptr)
		m_pXMLFile = new QFile(XMLFilename);

	return m_pXMLFile->open(flag);
}

void XMLWriter::writeProjectInformation(QMap<QString, QVariant>& map)
{
	m_pXMLFile->seek(0);	// rewind file before writing
	writeSettingsXml((QIODevice&)*m_pXMLFile, map);
}

void XMLWriter::readProjectInformation(QMap<QString, QVariant>& map)
{
	readSettingsXml((QIODevice&)*m_pXMLFile, map);
}

void XMLWriter::writeProjectInformation(QString XMLFilename, QMap<QString, QVariant>& map)
{
	normalizeString(XMLFilename);

	QFile XMLFile(XMLFilename);

	XMLFile.open(QIODevice::WriteOnly);

	writeSettingsXml((QIODevice&)XMLFile, map);

	XMLFile.close();
}

void XMLWriter::readProjectInformation(QString XMLFilename, QMap<QString, QVariant>& map)
{
	normalizeString(XMLFilename);

	QFile XMLFile(XMLFilename);

	XMLFile.open(QIODevice::ReadOnly);

	readSettingsXml((QIODevice&)XMLFile, map);

	XMLFile.close();
}

void XMLWriter::readXMLFile(QString filename, SettingsValues* settings, ExperimentalData* data)
{
	//readSettingsXml(m_pXMLFile, &settings);
}

void XMLWriter::appendFeedback(int score, QString name, QString email, QString institute, QString desc)
{
	QDomDocument xml;

	QString errorStr;
	int errorLine;
	int errorColumn;

	QDomElement root;

	// cant open file it doesnt exist
	if (!xml.setContent(m_pXMLFile, false, &errorStr, &errorLine, &errorColumn))
	{
		emit LOGCONSOLE("creating new feedback file", CONSOLECOLOURS::Information);

		root = xml.createElement("feedback");
		xml.appendChild(root);
	}
	else // file does exist, then append to the feedback node
	{
		root = xml.documentElement();
		if (root.tagName() != "feedback") {
			emit LOGCONSOLE("wrong file to append to - missing feedback node", CONSOLECOLOURS::Information);
		}
	}

	QDomElement feedback = xml.createElement("item");

	QDomElement usernode = xml.createElement("user");
	usernode.setAttribute("name", name);
	usernode.setAttribute("institute", institute);
	usernode.setAttribute("email", email);
	feedback.appendChild(usernode);

	QDomElement scorenode = xml.createElement("score");
	QDomText txttextnode = xml.createTextNode(QString::number(score));
	scorenode.appendChild(txttextnode);
	feedback.appendChild(scorenode);

	QDomElement descnode = xml.createElement("description");
	QDomText desctextnode = xml.createTextNode(desc);
	descnode.appendChild(desctextnode);
	feedback.appendChild(descnode);

	root.appendChild(feedback);

	// write DOM to file
	QTextStream stream(m_pXMLFile);
	stream.seek(0);	// important or it just appends xml to whatever is already in file!
	stream.setCodec("UTF-8");
	stream.setDevice(m_pXMLFile);
	stream << xml.toString();
	stream.flush();

	m_pXMLFile->close();
}

void XMLWriter::writeCentroids(cv::Mat& centroidsImage, cv::Mat& stats)
{
	QTextStream stream(m_pXMLFile);
	stream.setCodec("UTF-8");
	stream.setDevice(m_pXMLFile);

	QDomDocument xml("targeter SYSTEM \"targeter.dtd\"");

	QDomElement coords = xml.createElement("target-coordinates");
	xml.appendChild(coords);

	QString output = "target coordinates\n";

	for (int i = 1; i < centroidsImage.rows; i++)
	{
		double x = centroidsImage.at<double>(i, 0);
		double y = centroidsImage.at<double>(i, 1);
		int *row = &stats.at<int>(i, 0);

		writeCentroid(&xml, &coords, QPoint(x, y), QRect(row[cv::CC_STAT_LEFT], row[cv::CC_STAT_TOP], row[cv::CC_STAT_WIDTH], row[cv::CC_STAT_HEIGHT]));

		output += "x:" + QString::number(x) + " y:" + QString::number(y) + "\n";
	}

	QMetaObject::invokeMethod(this, "LOGCONSOLE", Qt::QueuedConnection, Q_ARG(QString, output), Q_ARG(CONSOLECOLOURS::colour, CONSOLECOLOURS::colour::Data));

	//doc.save(stream);

	stream << xml.toString();
	stream.flush();

	m_pXMLFile->close();
}

void XMLWriter::writeCentroids(QVector<QPoint> targetPoints, QVector<QRect> targetRect)
{
	QTextStream stream(m_pXMLFile);

	stream.setCodec("UTF-8");
	stream.setDevice(m_pXMLFile);

	QDomDocument xml("targeter SYSTEM \"targeter.dtd\"");

	QDomElement coords = xml.createElement("target-coordinates");
	xml.appendChild(coords);

	QString output = "target coordinates\n";

	for (int i = 0; i < targetPoints.size(); i++)
	{
		if(i<targetRect.size())
			writeCentroid(&xml, &coords, targetPoints[i], targetRect[i]);
		else
			writeCentroid(&xml, &coords, targetPoints[i], QRect());

		if(!targetPoints[i].isNull())
		{
			output += "x:" + QString::number(targetPoints[i].x()) + " y:" + 
						QString::number(targetPoints[i].y()) + "\n";
		}
	}

	stream << xml.toString();
	stream.flush();

	m_pXMLFile->close();
}

void XMLWriter::writeCentroid(QDomDocument* xml, QDomElement* coords, QPoint pt, QRect rect)
{
	QDomElement target;

	if (!pt.isNull())
	{
		target = xml->createElement("target");
		coords->appendChild(target);

		QDomElement tag2 = xml->createElement("centroid");

		tag2.setAttribute("x", QString::number(pt.x()));
		tag2.setAttribute("y", QString::number(pt.y()));

		target.appendChild(tag2);
	}
	
	if (!rect.isEmpty())
	{
		if(pt.isNull())
			target = xml->createElement("target");

		QDomElement tag3 = xml->createElement("bounding-rectangle");

		tag3.setAttribute("top", QString::number(rect.top()));
		tag3.setAttribute("left", QString::number(rect.left()));
		tag3.setAttribute("width", QString::number(rect.width()));
		tag3.setAttribute("height", QString::number(rect.height()));

		target.appendChild(tag3);
	}
}





