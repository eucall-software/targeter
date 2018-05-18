#include "Camera.h"

#include "opencv2/opencv.hpp"

Camera::Camera()
{
	intrinsic_matrix = cv::Mat(3, 3, CV_32F);
	distortion_coeffs = cv::Mat(1, 5, CV_32F);
}

Camera::Camera(cv::Mat intrinsic, cv::Mat distortion)
{
	intrinsic_matrix = intrinsic;
	distortion_coeffs = distortion;
}

Camera::~Camera()
{
}

void Camera::serialise(QDataStream& stream)
{
	stream << mat2ByteArray(intrinsic_matrix) << mat2ByteArray(distortion_coeffs);
}

void Camera::deserialise(QDataStream& stream)
{
	QByteArray b1, b2;

	stream >> b1 >> b2;

	intrinsic_matrix = byteArray2Mat(b1);
	distortion_coeffs = byteArray2Mat(b2);
}

QByteArray Camera::mat2ByteArray(const cv::Mat &image)
{
	QByteArray byteArray;
	QDataStream stream(&byteArray, QIODevice::WriteOnly);
	stream << image.type();
	stream << image.rows;
	stream << image.cols;
	const size_t data_size = image.cols * image.rows * image.elemSize();
	QByteArray data = QByteArray::fromRawData((const char*)image.ptr(), data_size);
	stream << data;
	return byteArray;
}


cv::Mat Camera::byteArray2Mat(const QByteArray & byteArray)
{
	QDataStream stream(byteArray);
	int matType, rows, cols;
	QByteArray data;
	stream >> matType;
	stream >> rows;
	stream >> cols;
	stream >> data;
	cv::Mat mat(rows, cols, matType, (void*)data.data());
	return mat.clone();
}
