#ifndef XMLWRITER_H
#define XMLWRITER_H 

#include <QFile>
#include <QtXml/QDomDocument>
#include "opencv2/core.hpp"
#include "Settings.h"
#include "globals.h"
#include "ExperimentalData.h"
#include "mainwindow.h"


class XMLWriter : public QObject
{
	Q_OBJECT

public:
	XMLWriter();
	XMLWriter(MainWindow* parent);
	~XMLWriter();

	bool isLegalFilePath(QString path);

	void writePositions(QVector<Target> targetPoints);
	void writePosition(QDomDocument& xml, QDomElement& coords, Target target);

	void writeImageToDOM(QDomDocument& xml, QDomElement& outerElement, ImageData* id);

	void readTargetsFromFile(const QString &fileName);
	QVector<QVector3D> readTargets(QDomElement coords);

	

	void appendImageInformationXML(QString imagefilename, QString sourceType, QVector<QSharedPointer<drawingShape>> shapes, int imageIndex=-1, int regionShapeType=-1);
	void appendMosaicImageInformationXML(QString imagefilename, QString sourceType, QVector<QSharedPointer<drawingShape>> shapes,
										QVector3D absolutePosition, QVector3D relativePosition);
	void writeStageMovementInformation(QDomDocument& xml, QDomElement& tag);
	void addShapeInfo(QDomDocument& xml, QDomElement& tag, QVector<QSharedPointer<drawingShape>> shapes);

	void writeProjectInformation(QMap<QString, QVariant>& map);
	void readProjectInformation(QMap<QString, QVariant>& map);

	void writeProjectInformation(QString XMLFilename, QMap<QString, QVariant>& map);
	void readProjectInformation(QString XMLFilename, QMap<QString, QVariant>& map);

	void writeProjectInfoToDOM(QDomDocument& xml, QDomElement& containerElement, SettingsValues* settings);
	void writeTargetsToDOM(QDomDocument& xml, QDomElement& containerElement, QVector<ImageData> processedImages);

	void readProjectInformation(QString XMLFilename, SettingsValues* settings);
	void writeProjectInformation(QString XMLFilename, SettingsValues* settings);

	void writeShapeInformation(QDomDocument& xml, QDomElement& containerTag, QString imagefilename, QString sourceType, 
								QVector<QSharedPointer<drawingShape>> shapes, int imageIndex, int regionShapeType);

	void readProjectSettings(SettingsValues* settings);
	void writeProjectSettings(SettingsValues* settings);

	void writeElement(QDomDocument& xml, QDomElement& outerElement, QString nodeText, QString text);
	void writeVector3D(QDomDocument& xml, QDomElement& outerElement, QString nodeText, QVector3D vect);

	template <typename T>
	void writePoint(QDomDocument& xml, QDomElement& outerElement, QString nodeText, T pt)
	{
		if (pt.x() >= 0 && pt.y())
		{
			QDomElement tag = xml.createElement(nodeText);

			writeElement(xml, tag, "x", QString::number(pt.x()));
			writeElement(xml, tag, "y", QString::number(pt.y()));

			outerElement.appendChild(tag);
		}
	};

	template <typename T>
	void writeRect(QDomDocument& xml, QDomElement& outerElement, QString nodeText, T rect)
	{
		if (rect.x() >= 0 && rect.y() && rect.width() >= 0 && rect.height() >= 0)
		{
			QDomElement tag = xml.createElement(nodeText);

			writeElement(xml, tag, "x", QString::number(rect.x()));
			writeElement(xml, tag, "y", QString::number(rect.y()));
			writeElement(xml, tag, "width", QString::number(rect.width()));
			writeElement(xml, tag, "height", QString::number(rect.height()));

			outerElement.appendChild(tag);
		}
	};

	void writePolygon(QDomDocument& xml, QDomElement& outerElement, QString nodeText, QVector<QPoint> poly);
	void writeEllipse(QDomDocument& xml, QDomElement& outerElement, QString nodeText, QPoint origin, QSize boundingBox);

	void CreateXMLDocument(QFile* file, QDomDocument& xml, QDomElement& rootTag, QDomElement& tag, QString rootTagName, QString tagName, bool& bCloseRootTag, bool& bCloseTag);
	void CreateReadXMLDocument(QDomDocument& xml, QDomElement& rootTag, QDomElement& containerTag, QString rootTagName, QString containerTagName);
	bool readXMLDoc(QDomDocument& xml, QString rootTagName, bool bFileNotFound, bool bTagNotFound);

	void appendFeedback(int score, QString name, QString email, QString institute, QString desc);
	QString readElement(QDomDocument& xml, QString nodeText);

	bool openXMLFile(QString XMLFilename, QFlags<QIODevice::OpenModeFlag> flag);
	bool OpenFile(QString path, QString filename);
	void normalizeString(QString& s);

	QFile* m_pXMLFile;
	QDomDocument m_XML_DOM;

signals:
	void LOGCONSOLE(QString strText, CONSOLECOLOURS::colour col);



};


#endif