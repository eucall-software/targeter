#include "ImageReadWrite.h"
#include "HelperFunctions.h"
#ifdef _HAVE_IMAGEMAGICK

#include <Magick++.h>

#include <QVector>

using namespace Magick;

ImageReadWrite::ImageReadWrite(QObject *parent)
	: QObject(parent)
{
	
}

ImageReadWrite::~ImageReadWrite()
{

}

cv::Mat ImageReadWrite::readImage(QString filename, QString& jsondata)
{
	// need to build imagemagick debug DLL's
	try {

		Magick::Image im;

		std::string fn = filename.toLocal8Bit().data();
		
		im.read(filename.toUtf8().constData());

		jsondata = QString::fromStdString(im.comment());

		if(jsondata != "")
			emit LOGCONSOLE("image data: " + jsondata);
	
		int w = im.columns();
		int h = im.rows();

		cv::Mat opencvImage(h, w, CV_8UC4);
		cv::Mat outputMat;

		im.write(0, 0, w, h, "BGRA", Magick::CharPixel, opencvImage.data);

		cvtColor(opencvImage, outputMat, CV_BGRA2BGR);

		DBOUT("opencvImage type " << HelperFunctions::type2str(opencvImage.type()).toLocal8Bit().data());
		DBOUT("outputMat type " <<  HelperFunctions::type2str(outputMat.type()).toLocal8Bit().data());

		return outputMat;
	}
	catch (Magick::Exception &error_)
	{
		const char* perr = error_.what();

		QString err = QString::fromLocal8Bit(perr);

		emit LOGCONSOLE("Exception reading image: " + err);

		return cv::Mat();
	}
}

void ImageReadWrite::writeImage(QString filename, cv::Mat image, QString jsondata)
{
	try {
		Magick::Image im(image.cols, image.rows, "BGR", Magick::CharPixel, (char *)image.data);

		im.comment(jsondata.toLocal8Bit().data());

		const std::string fn = filename.toLocal8Bit().data();

		im.write(fn);
	}
	catch (Magick::Exception &error_)
	{
		QString err = QString::fromUtf8(error_.what());

		emit LOGCONSOLE("Exception writing image: " + err);
	}
}
#endif