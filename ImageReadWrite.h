#ifndef IMAGEREADWRITE_H
#define IMAGEREADWRITE_H

#include "opencv2/opencv.hpp"
#include "globals.h"
#include <QObject>

class ImageReadWrite : public QObject
{
	Q_OBJECT

public:
	ImageReadWrite(QObject *parent);
	ImageReadWrite() {};
	~ImageReadWrite();

	cv::Mat readImage(QString filename, QString& jsondata);
	void writeImage(QString filename, cv::Mat image, QString jsondata = "{}");

signals:
	//Signal to output frame to be displayed
	void LOGCONSOLE(QString strText, CONSOLECOLOURS::colour col = CONSOLECOLOURS::colour::Information);
};

#endif
