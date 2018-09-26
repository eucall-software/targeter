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

XMLWriter::XMLWriter(MainWindow* parent) : XMLWriter() 
{
	connect(this, SIGNAL(LOGCONSOLE(QString, CONSOLECOLOURS::colour)), parent, SLOT(LOGCONSOLE(QString, CONSOLECOLOURS::colour)));
}
XMLWriter::XMLWriter() 
{
	m_pXMLFile = nullptr;
}

XMLWriter::~XMLWriter()
{
	if(m_pXMLFile != nullptr && m_pXMLFile->isOpen())
		m_pXMLFile->close();

	if (m_pXMLFile)
		delete m_pXMLFile;
}

bool XMLWriter::isLegalFilePath(QString path)
{
	// Anything following the raw filename prefix should be legal.
	if (path.left(4) == "\\\\?\\")
		return true;

	// Windows filenames are not case sensitive.
	path = path.toUpper();
	/*
	// Trim the drive letter off
	if (path[1] == ':' && (path[0] >= 'A' && path[0] <= 'Z'))
		path = path.right(path.length() - 2);
	*/
	QString illegal = "<>\"|?*";

	foreach(const QChar& c, path)
	{
		// Check for control characters
		if (c.toLatin1() > 0 && c.toLatin1() < 32)
			return false;

		// Check for illegal characters
		if (illegal.contains(c))
			return false;
	}

	// Check for device names in filenames
	static QStringList devices;

	if (!devices.count())
		devices << "CON" << "PRN" << "AUX" << "NUL" << "COM0" << "COM1" << "COM2"
		<< "COM3" << "COM4" << "COM5" << "COM6" << "COM7" << "COM8" << "COM9" << "LPT0"
		<< "LPT1" << "LPT2" << "LPT3" << "LPT4" << "LPT5" << "LPT6" << "LPT7" << "LPT8"
		<< "LPT9";

	const QFileInfo fi(path);
	const QString basename = fi.baseName();

	foreach(const QString& s, devices)
		if (basename == s)
			return false;

	// Check for trailing periods or spaces
	if (path.right(1) == "." || path.right(1) == " ")
		return false;

	// Check for pathnames that are too long (disregarding raw pathnames)
	if (path.length() > 260)
		return false;

	// Exclude raw device names
	if (path.left(4) == "\\\\.\\")
		return false;

	// Since we are checking for a filename, it mustn't be a directory
	/*
	if (path.right(1) == "\\")
		return false;
	*/
	return true;
}

void XMLWriter::normalizeString(QString& s)
{
	s.remove(QRegularExpression("[" + QRegularExpression::escape("'!*,?|¡¿") + "]"));

	// Performance: Check for characters
	if (s.contains(QRegularExpression("[" + QRegularExpression::escape("$/:ÀÁÄÙÛÜàáäçèéêëïñóöùûü") + "]")))
	{
		// Special Characters 
		// Escape function is a safety measure in case you accidentally insert "^" in the square brackets.
		s.replace(QRegularExpression("[" + QRegularExpression::escape(":/") + "]"), ":");
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

bool XMLWriter::OpenFile(QString path, QString filename)
{
	if (!this->isLegalFilePath(path))
	{
		QString s = "illegal file path - " + path + " changing path to D:\temp";
		path = "D:\temp";
		LOGCONSOLE(s, CONSOLECOLOURS::colour::Information);
		return false;
	}

	// file for target information
	QString XMLfilename = path + filename;

	// create xml writing class
	return this->openXMLFile(XMLfilename, QIODevice::ReadWrite);
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

	openXMLFile(XMLFilename, QIODevice::WriteOnly);

	writeSettingsXml((QIODevice&)*m_pXMLFile, map);
}

void XMLWriter::readProjectInformation(QString XMLFilename, QMap<QString, QVariant>& map)
{
	normalizeString(XMLFilename);

	openXMLFile(XMLFilename, QIODevice::ReadOnly);

	readSettingsXml((QIODevice&)*m_pXMLFile, map);

}

void XMLWriter::writeProjectInformation(QString XMLFilename, SettingsValues* settings)
{
	normalizeString(XMLFilename);

	writeProjectSettings(settings);
}

void XMLWriter::readProjectInformation(QString XMLFilename, SettingsValues* settings)
{
	normalizeString(XMLFilename);

	openXMLFile(XMLFilename, QIODevice::ReadOnly);

	readProjectSettings(settings);

}

void XMLWriter::readProjectSettings(SettingsValues* settings)
{
	QDomDocument xml;
	QDomElement root;
	QDomElement settingsNode;

	bool bCloseRootTag;
	bool bCloseCoordsTag;

	CreateXMLDocument(m_pXMLFile, xml, root, settingsNode, "frame", "settings", bCloseRootTag, bCloseCoordsTag);

	settings->s_project_Username = readElement(xml, "project_UserName");
	settings->s_project_Name = readElement(xml, "project_Name");
	settings->s_project_Institute = readElement(xml, "project_Institute");
	settings->s_project_ID = readElement(xml, "project_ID");
	settings->s_project_Version = readElement(xml, "project_Version");
	settings->s_project_Description = readElement(xml, "project_Description");
	settings->s_project_FilenamePrefix = readElement(xml, "project_FilenamePrefix");
	settings->s_project_SampleDescription = readElement(xml, "project_SampleDescription");
	settings->s_project_Barcode = readElement(xml, "project_Barcode");
	settings->s_project_Directory = readElement(xml, "project_Directory");
	settings->d_project_Date = QDate::fromString(readElement(xml, "project_Date"), "yyyy-MM-dd");
}

void XMLWriter::writeProjectSettings(SettingsValues* settings)
{
	QDomDocument xml;
	QDomElement root;
	QDomElement settingsNode;

	QString rootTagName = "frame";
	QString containerTagName = "settings";

	QDomElement rootTag;
	QDomElement containerTag;

	CreateReadXMLDocument(xml, rootTag, containerTag, rootTagName, containerTagName);

	writeProjectInfoToDOM(xml, containerTag, settings);

	// write DOM to file
	QTextStream stream(m_pXMLFile);
	stream.seek(0);	// important or it just appends xml to whatever is already in file!
	stream.setCodec("UTF-8");
	stream.setDevice(m_pXMLFile);
	stream << xml.toString();
	stream.flush();
}

void XMLWriter::writeProjectInfoToDOM(QDomDocument& xml, QDomElement& containerElement, SettingsValues* settings)
{
	QString containerTagName = "project_settings";

	QDomElement containerTag = xml.createElement(containerTagName);

	writeElement(xml, containerTag, "project_UserName", settings->s_project_Username);
	writeElement(xml, containerTag, "project_Name", settings->s_project_Name);
	writeElement(xml, containerTag, "project_Institute", settings->s_project_Institute);
	writeElement(xml, containerTag, "project_ID", settings->s_project_ID);
	writeElement(xml, containerTag, "project_Version", settings->s_project_Version);
	writeElement(xml, containerTag, "project_Description", settings->s_project_Description);
	writeElement(xml, containerTag, "project_FilenamePrefix", settings->s_project_FilenamePrefix);
	writeElement(xml, containerTag, "project_SampleDescription", settings->s_project_SampleDescription);
	writeElement(xml, containerTag, "project_Barcode", settings->s_project_Barcode);
	writeElement(xml, containerTag, "project_Directory", settings->s_project_Directory);
	writeElement(xml, containerTag, "project_Date", settings->d_project_Date.toString("yyyy-MM-dd"));

	QDomElement map = xml.createElement("transformation_map");

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			QString name = "M" + QString::number(i + 1) + QString::number(j + 1);
			writeElement(xml, map, name, QString::number(settings->m_transformationMatrix(i, j)));
		}

	containerTag.appendChild(map);

	map = xml.createElement("inv_transformation_map");

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			QString name = "M" + QString::number(i + 1) + QString::number(j + 1);
			writeElement(xml, map, name, QString::number(settings->m_invTransformationMatrix(i, j)));
		}

	containerTag.appendChild(map);

	containerElement.appendChild(containerTag);

	xml.appendChild(containerElement);
}

void XMLWriter::writeElement(QDomDocument& xml, QDomElement& outerElement, QString nodeText, QString text)
{
	QDomElement node = xml.createElement(nodeText);
	QDomText txttextnode = xml.createTextNode(text);
	node.appendChild(txttextnode);
	outerElement.appendChild(node);
}

void XMLWriter::writeVector3D(QDomDocument& xml, QDomElement& outerElement, QString nodeText, QVector3D vect)
{
	if (vect.x() >= 0 && vect.y())
	{
		QDomElement tag = xml.createElement(nodeText);

		writeElement(xml, tag, "x", QString::number(vect.x()));
		writeElement(xml, tag, "y", QString::number(vect.y()));
		writeElement(xml, tag, "z", QString::number(vect.z()));

		outerElement.appendChild(tag);
	}
}


void XMLWriter::writePolygon(QDomDocument& xml, QDomElement& outerElement, QString nodeText, QVector<QPoint> poly)
{
	QDomElement tag = xml.createElement(nodeText);

	foreach(QPoint p, poly)
	{
		QDomElement tag2 = xml.createElement("vertex");

		writeElement(xml, tag2, "x", QString::number(p.x()));
		writeElement(xml, tag2, "y", QString::number(p.y()));

		tag.appendChild(tag2);
	}

	outerElement.appendChild(tag);
}

void XMLWriter::writeEllipse(QDomDocument& xml, QDomElement& outerElement, QString nodeText, QPoint origin, QSize boundingBox)
{
	QDomElement tag = xml.createElement(nodeText);

	QDomElement tag2 = xml.createElement("origin");

	writeElement(xml, tag2, "x", QString::number(origin.x()));
	writeElement(xml, tag2, "y", QString::number(origin.y()));

	tag.appendChild(tag2);

	tag2 = xml.createElement("diameter");

	writeElement(xml, tag2, "width", QString::number(boundingBox.width()));
	writeElement(xml, tag2, "height", QString::number(boundingBox.height()));

	tag.appendChild(tag2);
	
	outerElement.appendChild(tag);
}

QString XMLWriter::readElement(QDomDocument& xml, QString nodeText)
{
	QDomNodeList nodes = xml.elementsByTagName(nodeText);

	if (nodes.size() < 1)
	{
		emit LOGCONSOLE("cant find tag "+ nodeText, CONSOLECOLOURS::Information);
		return "";
	}
	else
	{
		// set to this tag for appends
		QDomElement el = nodes.at(0).toElement();

		return el.text();
	}
}

void XMLWriter::appendFeedback(int score, QString name, QString email, QString institute, QString desc)
{
	QDomDocument xml;

	QString errorStr;
	int errorLine;
	int errorColumn;

	QDomElement root;
	QDomElement feedback;

	//bool bNewFile = openCreateXMLFile(m_pXMLFile, &xml, &root, &feedback, "feedback", "item");

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

	feedback = xml.createElement("item");

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

	
}

// reads XML into document, if correct XML file
bool XMLWriter::readXMLDoc(QDomDocument& xml, QString rootTagName, bool bFileNotFound, bool bTagNotFound)
{
	QString errorStr;
	int errorLine;
	int errorColumn;
	bool bNewFile = false;
	bFileNotFound = false;
	bTagNotFound = false;

	if (!m_pXMLFile->isOpen())
	{
		emit LOGCONSOLE("XML file not open aborting", CONSOLECOLOURS::Information);
		bFileNotFound = true;
		return false;
	}

	if (xml.setContent(m_pXMLFile, false, &errorStr, &errorLine, &errorColumn))
	{
		// found XML file
	
		// get root node
		QDomElement rootTag = xml.documentElement();

		// check to see if correct structure
		if (rootTag.tagName() != rootTagName) 
		{
			emit LOGCONSOLE(m_pXMLFile->fileName() + ": wrong file to append to - missing " + rootTagName + " node", CONSOLECOLOURS::Information);
			bTagNotFound = true;
			return false;
		}
	}
	else
	{
		emit LOGCONSOLE(m_pXMLFile->fileName() + ": error : " + errorStr, CONSOLECOLOURS::Information);
		bFileNotFound = true;
		return false;
	}

	return true;
}

void XMLWriter::CreateReadXMLDocument(QDomDocument& xml, QDomElement& rootTag, QDomElement& containerTag, QString rootTagName, QString containerTagName)
{
	bool bFileNotFound, bTagNotFound;

	if (!readXMLDoc(xml, rootTagName, bFileNotFound, bTagNotFound))
	{
		// create new xml file
		if (bFileNotFound)
		{
			rootTag = xml.createElement(rootTagName);
			containerTag = xml.createElement(containerTagName);
			rootTag.appendChild(containerTag);
			xml.appendChild(rootTag);
		}
	}

	// now all of the XML file will have been read into xml

	// set document to point to containerTag
	QDomNodeList nodes = xml.elementsByTagName(containerTagName);

	if (!nodes.isEmpty())
		containerTag = nodes.at(0).toElement();

	return;
}

void XMLWriter::CreateXMLDocument(QFile* file, QDomDocument& xml, QDomElement& rootTag, QDomElement& tag, QString rootTagName, QString tagName, bool& bCloseRootTag, bool& bCloseTag)
{
	QString errorStr;
	int errorLine;
	int errorColumn;
	bool bNewFile = false;
	bCloseRootTag = false;
	bCloseTag = false;

	if (xml.setContent(file, false, &errorStr, &errorLine, &errorColumn))
	{
		// get root node
		rootTag = xml.documentElement();

		if (rootTag.tagName() != rootTagName) {
			emit LOGCONSOLE(file->fileName() + ": wrong file to append to - missing "+ rootTagName +" node", CONSOLECOLOURS::Information);
			return;
		}

		// get targets tag
		QDomNodeList nodes = xml.elementsByTagName(tagName);

		if (nodes.isEmpty())
		{
			tag = xml.createElement(tagName);
			//rootTag->appendChild(*tag);
			bCloseTag = true;
		}
		else
		{
			// set to this tag for appends
			tag = nodes.at(0).toElement();
		}
	}
	else
	{
		QString filename = file->fileName();
		emit LOGCONSOLE("creating new file: " + filename, CONSOLECOLOURS::Information);

		rootTag = xml.createElement(rootTagName);
		//xml->appendChild(*rootTag);
		tag = xml.createElement(tagName);
		//rootTag->appendChild(*tag);
		bCloseRootTag = true;
		bCloseTag = true;
	}

	// should close file after reading
	// then open it again for writing afterwards with modified dom tree
}

void XMLWriter::writePositions(QVector<Target> targets)
{
	QDomDocument xml("targeter");

	QString errorStr;
	int errorLine;
	int errorColumn;
	QString rootTagName = "frame";
	QString containerTagName = "images";
	
	QDomElement rootTag;
	QDomElement containerTag;

	CreateReadXMLDocument(xml, rootTag, containerTag, rootTagName, containerTagName);
	
	QString filename = m_pXMLFile->fileName();
	emit LOGCONSOLE("writing target positions to file: " + filename, CONSOLECOLOURS::Information);

	QDomElement tag = xml.createElement("image");

	for (int i = 0; i < targets.size(); i++)
	{
		if (targets[i].region.width()>0 && targets[i].region.height()>0)
			writePosition(xml, tag, targets[i]);
		else
			writePosition(xml, tag, targets[i]);
	}
	
	containerTag.appendChild(tag);

	// write DOM to file
	QTextStream stream(m_pXMLFile);
	stream.seek(0);	// important or it just appends xml to whatever is already in file!

	stream.setCodec("UTF-8");
	stream.setDevice(m_pXMLFile);

	stream << xml.toString();
	stream.flush();
}

void  XMLWriter::writeTargetsToDOM(QDomDocument& xml, QDomElement& containerElement, QVector<ImageData> processedImages)
{
	QString containerTagName = "target_images";

	QDomElement rootTag;
	QDomElement containerTag = xml.createElement(containerTagName);

	for(int i=0; i<processedImages.length(); i++)
	{
		QDomElement containerTag2 = xml.createElement("target_image");

		ImageData id = processedImages[i];
		
		writeImageToDOM(xml, containerTag2, &id);

		containerTag.appendChild(containerTag2);
	}

	containerElement.appendChild(containerTag);

	xml.appendChild(containerElement);
}

void XMLWriter::writeImageToDOM(QDomDocument& xml, QDomElement& outerElement, ImageData* id)
{
	QDomElement imageNode = xml.createElement("image");

	writeElement(xml, imageNode, "filename", id->filename);
	writeElement(xml, imageNode, "description", id->imageDescription);
	writeRect(xml, imageNode, "pattern_region", id->patternRegion);

	if (id->scanRegion.length() > 0)
	{
		QDomElement regionTag = xml.createElement("scan_regions");

		for (int k = 0; k < id->scanRegion.length(); k++)
		{
			QDomElement regionTag2 = xml.createElement("scan_region");

			ScanRegion sr = id->scanRegion[k];

			writeElement(xml, regionTag, "ID", sr.ID);
			writeElement(xml, regionTag, "name", sr.name);
			writeElement(xml, regionTag, "description", sr.regionDescription);
			writeRect(xml, regionTag, "region", sr.scanRegion);

			writeElement(xml, regionTag, "shape", DRAWINGMODESTRINGS(sr.regionShape));

			QDomElement stagePositionsTag = xml.createElement("stage_positions");

			if (sr.stagePositions.length() > 0)
			{
				StageCoordinates sc = sr.stagePositions[k];

				QDomElement stagePositionTag = xml.createElement("stage_position");

				for (int l = 0; l < sr.stagePositions.length(); l++)
				{
					writePoint(xml, regionTag, "index", sc.index);
					writeElement(xml, regionTag, "scan_region_index", QString::number(id->scanRegionIndex));
					writeVector3D(xml, regionTag, "stage_position", sc.stagePosition3D);

					QSharedPointer<ImageData> pIm = sc.childImage;

					// recursive call for nested images (if any)
					writeImageToDOM(xml, stagePositionTag, pIm.data());
				}
			}

			regionTag2.appendChild(stagePositionsTag);
			imageNode.appendChild(regionTag2);
		}
	}

	QVector<Target> targets = id->targetList;

	if(targets.length()>0)
	{
		QDomElement targetsTag = xml.createElement("targets");

		for(int i=0;i<targets.length();i++)
		{
			Target tar = targets[i];

			QDomElement targetTag = xml.createElement("target");

			writeElement(xml, targetTag, "ID", QString::number(tar.ID));
			writeElement(xml, targetTag, "image_name", tar.image);
			writePoint(xml, targetTag, "image_position", tar.imagePosition);
			writeVector3D(xml, targetTag, "position", tar.position);
			writeRect(xml, targetTag, "region", tar.region);

			targetsTag.appendChild(targetTag);
		}

		imageNode.appendChild(targetsTag);
	}

	outerElement.appendChild(imageNode);
}

void XMLWriter::appendImageInformationXML(QString imagefilename, QString sourceType, QVector<QSharedPointer<drawingShape>> shapes, 
										int imageIndex, int regionShapeType)
{
	QDomDocument xml("targeter");

	QString errorStr;
	int errorLine;
	int errorColumn;
	QString rootTagName = "frame";
	QString containerTagName = "images";

	QDomElement rootTag;
	QDomElement containerTag;

	CreateReadXMLDocument(xml, rootTag, containerTag, rootTagName, containerTagName);

	writeShapeInformation(xml, containerTag, imagefilename, sourceType, shapes, imageIndex, regionShapeType);

	// write DOM to file
	QTextStream stream(m_pXMLFile);
	stream.seek(0);	// important or it just appends xml to whatever is already in file!

	stream.setCodec("UTF-8");
	stream.setDevice(m_pXMLFile);

	stream << xml.toString();
	stream.flush();
}

void XMLWriter::writeShapeInformation(QDomDocument& xml, QDomElement& containerTag, QString imagefilename, QString sourceType, QVector<QSharedPointer<drawingShape>> shapes, 
									int imageIndex, int regionShapeType)
{
	QDomElement tag = xml.createElement("image");

	writeElement(xml, tag, "name", imagefilename);

	writeElement(xml, tag, "source", sourceType);

	QString s = xml.toString();
	/*
	if (stagePosition->regionShape != drawingMode::none)
		writeStageMovementInformation(xml, tag, stagePosition);
		*/
	if (imageIndex >= 0)
		writeElement(xml, tag, "scanRegionIndex", QString::number(imageIndex));
	if (regionShapeType >= 0)
		writeElement(xml, tag, "shapeType", DRAWINGMODESTRINGS(regionShapeType));

	addShapeInfo(xml, tag, shapes);

	containerTag.appendChild(tag);
}

void XMLWriter::appendMosaicImageInformationXML(QString imagefilename, QString sourceType, QVector<QSharedPointer<drawingShape>> shapes,
												QVector3D absolutePosition, QVector3D relativePosition)
{
	QDomDocument xml("targeter SYSTEM \"targeter.dtd\"");

	QString errorStr;
	int errorLine;
	int errorColumn;

	QDomElement root;
	QDomElement coords;

	bool bCloseRootTag;
	bool bCloseCoordsTag;

	CreateXMLDocument(m_pXMLFile, xml, root, coords, "frame", "images", bCloseRootTag, bCloseCoordsTag);

	QDomElement tag = xml.createElement("image");

	writeElement(xml, tag, "name", imagefilename);

	writeElement(xml, tag, "source", sourceType);

	addShapeInfo(xml, tag, shapes);

	// now add StageMovement information
	writeStageMovementInformation(xml, tag);

	writeVector3D(xml, tag, "absolutePosition", absolutePosition);
	writeVector3D(xml, tag, "relativePosition", relativePosition);

	// now add tile information
	//QString s = ", frameBarcode:" + m_settings->s_project_Barcode + "}";

	coords.appendChild(tag);

	if (bCloseCoordsTag)
		root.appendChild(coords);
	
	if (bCloseRootTag)
		xml.appendChild(root);

	// write DOM to file
	QTextStream stream(m_pXMLFile);
	stream.seek(0);	// important or it just appends xml to whatever is already in file!

	stream.setCodec("UTF-8");
	stream.setDevice(m_pXMLFile);

	stream << xml.toString();
	stream.flush();
}




void XMLWriter::writeStageMovementInformation(QDomDocument& xml, QDomElement& tag)
{
	QDomElement tag2 = xml.createElement("stage_information");
	/*
	// now add StageMovement information
	if (stageInfo->scanRegionIndex >= 0)
		writeElement(xml, tag2, "scanRegionIndex", QString::number(stageInfo->scanRegionIndex));
	if (stageInfo->regionShape >= 0)
		writeElement(xml, tag2, "shapeType", DRAWINGMODESTRINGS(stageInfo->regionShape));

	QPoint ind = stageInfo->index;
	QRect rect = QRect(stageInfo->index, stageInfo->tileSize);

	writeRect(xml, tag2, "tile", rect);
	writePoint(xml, tag2, "stage_position", stageInfo->stagePosition);
	writeRect(xml, tag2, "scan_region", stageInfo->scanRegion);

	QVector<QSharedPointer<drawingShape>> shapes;

	shapes.append(stageInfo->shape);

	addShapeInfo(xml, tag2, shapes);
	*/
	tag.appendChild(tag2);
}

void XMLWriter::addShapeInfo(QDomDocument& xml, QDomElement& tag, QVector<QSharedPointer<drawingShape>> shapes)
{
	if (!shapes.isEmpty())
	{
		foreach(QSharedPointer<drawingShape> shapeInfo, shapes)
		{
			// only valid region shapes
			if (shapeInfo->type == drawingMode::circle || shapeInfo->type == drawingMode::rect || shapeInfo->type == drawingMode::poly)
			{
				QDomElement tag2 = xml.createElement("shape");
				writeElement(xml, tag2, "shapeType", DRAWINGMODESTRINGS(shapeInfo->type));
				writeElement(xml, tag2, "ID", shapeInfo->ID);
				writeElement(xml, tag2, "name", shapeInfo->name);
				writeElement(xml, tag2, "description", shapeInfo->desc);
				if (shapeInfo->regionType != shapeAnnotationType::none)
					writeElement(xml, tag2, "shapeAnnotationType", SHAPEANNOTATIONSTRINGS(shapeInfo->regionType));

				writeRect(xml, tag2, "Region", shapeInfo->boundingBox);

				tag.appendChild(tag2);
			}
		}
	}
}

void XMLWriter::writePosition(QDomDocument& xml, QDomElement& coords, Target target)
{
	QDomElement targetElement;
	QDomElement tag;

	int boxSize = 10;

	QVector3D pt = target.position;
	QRect rect = target.region;
	
	if (target.region.width() <= 0 || target.region.height() <= 0)
		rect = QRect(pt.toPoint() - QPoint(boxSize, boxSize), QSize(boxSize * 2, boxSize * 2));
		
	targetElement = xml.createElement("target");

	if (!pt.isNull())
		writeVector3D(xml, targetElement, "position", pt);
		
	if (!rect.isEmpty())
		writeRect(xml, targetElement, "region", rect);
	
	if(target.ID>=0)
		writeElement(xml, targetElement, "ID", QString::number(target.ID));
	if(target.image != "")
		writeElement(xml, targetElement, "imageName", target.image);			// link to image file
		/*
	if(target.FrameID != "")
		writeElement(xml, targetElement, "FrameID", target.FrameID);		// barcode of frame
	if(target.SubFrameID != "")
		writeElement(xml, targetElement, "SubFrameID", target.SubFrameID);		// sub frame identifier
	if(target.subRegionID != "")
		writeElement(xml, targetElement, "SubRegionID", target.subRegionID);	// Parent region identifier 
		*/
	//QRect r = target.patternRegion;	// Parent region location in image

	coords.appendChild(targetElement);
}

void XMLWriter::readTargetsFromFile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		emit LOGCONSOLE("Error: Cannot read file " + fileName	+ ": " + file.errorString(), CONSOLECOLOURS::Warning);
		return;
	}

	QString errorStr;
	int errorLine;
	int errorColumn;

	QDomDocument doc;
	if (!doc.setContent(&file, false, &errorStr, &errorLine,
		&errorColumn)) {
		emit LOGCONSOLE("Error: Parse error at line " + QString::number(errorLine) + ", " + "column " + QString::number(errorColumn) + ": " + errorStr, CONSOLECOLOURS::Warning);
		return;
	}

	QDomElement root = doc.documentElement();
	if (root.tagName() != "target-coordinates") {
		emit LOGCONSOLE("Error: Not a target file", CONSOLECOLOURS::Warning);
		return;
	}

	readTargets(root);
}

QVector<QVector3D> XMLWriter::readTargets(QDomElement targets_root)
{
	QVector<QVector3D> targets;

	QDomNode child = targets_root.firstChild();

	while (!child.isNull()) 
	{
		if (child.toElement().tagName() == "target")
		{
			QDomElement &node = child.toElement();
			
			node.attribute("centroid");

		//	parseEntryElement(child.toElement(), treeWidget->invisibleRootItem());

		}
		child = child.nextSibling();
	}

	return targets;
}


