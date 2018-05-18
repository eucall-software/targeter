#ifndef XMLWRITER_H
#define XMLWRITER_H 

#include <QFile>
#include <QtXml/QDomDocument>
#include "opencv2/core.hpp"
#include "Settings.h"
#include "ExperimentalData.h"


class XMLWriter : public QObject
{
	Q_OBJECT

public:
	XMLWriter();
	~XMLWriter();

	void writeCentroids(cv::Mat& centroidsImage, cv::Mat& stats);
	void writeCentroids(QVector<QPoint> targetPoints, QVector<QRect> targetRect);
	void writeCentroid(QDomDocument* xml, QDomElement* coords, QPoint pt, QRect rect);
	
	void writeProjectInformation(QMap<QString, QVariant>& map);
	void readProjectInformation(QMap<QString, QVariant>& map);

	void writeProjectInformation(QString XMLFilename, QMap<QString, QVariant>& map);
	void readProjectInformation(QString XMLFilename, QMap<QString, QVariant>& map);

	void readXMLFile(QString filename, SettingsValues* settings, ExperimentalData* data);

	void appendFeedback(int score, QString name, QString email, QString institute, QString desc);

	bool openXMLFile(QString XMLFilename, QFlags<QIODevice::OpenModeFlag> flag);
	void normalizeString(QString& s);

	QFile* m_pXMLFile;

signals:
	void LOGCONSOLE(QString strText, CONSOLECOLOURS::colour col);



};


#endif