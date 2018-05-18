// Targeter - target identification software for EUCALL workpackage 6
// Licensed under the GPL License. See LICENSE file in the project root for full license information.
// Copyright(C) 2017  David Watts 

#ifndef OPENCVTOQT_H
#define OPENCVTOQT_H
#include "opencv2/opencv.hpp"
#include "opencv/highgui.h"
#include <QImage>

class QImage;

namespace cv{
    class cv::Mat;
}

namespace opencvtoqt {

    QImage mat_to_qimage_cpy(cv::Mat const &mat, bool swap = true);

    QImage mat_to_qimage_ref(cv::Mat &mat, bool swap = true);

    cv::Mat qimage_to_mat_cpy(QImage const &img, bool swap = true);

    cv::Mat qimage_to_mat_ref(QImage &img, bool swap = true);

}

#endif // OPENCVTOQT_H
