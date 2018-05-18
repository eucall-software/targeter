#ifndef CAMERA_H
#define CAMERA_H

#include "opencv2/opencv.hpp"
#include <QDataStream>

// class to store camera parameters for calibration
class Camera
{
	
public:
	Camera();
	Camera(cv::Mat intrinsic, cv::Mat distortion);
	~Camera();

	void serialise(QDataStream& stream);
	void deserialise(QDataStream& stream);

	QByteArray mat2ByteArray(const cv::Mat &image);
	cv::Mat byteArray2Mat(const QByteArray & byteArray);

	cv::Mat intrinsic_matrix;
	cv::Mat distortion_coeffs;
};

#endif

