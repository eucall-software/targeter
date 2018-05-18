// Targeter - target identification software for EUCALL workpackage 6
// Licensed under the GPL License. See LICENSE file in the project root for full license information.
// Copyright(C) 2017  David Watts 

#include "opencvtoqt.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <QImage>

using namespace opencvtoqt;

inline QImage mat_to_qimage_ref_policy(cv::Mat &mat, QImage::Format format)
{
    return QImage(mat.data, mat.cols, mat.rows, mat.step, format);
}

inline QImage mat_to_qimage_cpy_policy(cv::Mat const &mat, QImage::Format format)
{
    return QImage(mat.data, mat.cols, mat.rows, mat.step, format).copy();
}

/**
 * copy QImage into cv::Mat
 */
struct qimage_to_mat_cpy_policy
{
    static cv::Mat start(QImage const &img, int format)
    {
        return cv::Mat(img.height(), img.width(), format, const_cast<uchar*>(img.bits()), img.bytesPerLine()).clone();
    }
};

/**
 * make Qimage and cv::Mat share the same buffer, the resource of the cv::Mat must not deleted before the QImage finish the jobs.
 */
struct qimage_to_mat_ref_policy
{
    static cv::Mat start(QImage &img, int format)
    {
        return cv::Mat(img.height(), img.width(), format, img.bits(), img.bytesPerLine());
    }
};

/**
 * generic class for reducing duplicate codes
 */
template<typename Policy>
struct qimage_to_mat
{
    template<typename Image>
    static cv::Mat run(Image &&img, bool swap);
};


/**
*
*  transform QImage to cv::Mat
* 
* FullName   qimage_to_mat::run
* Qualifier 
* @param     Image & & img 
* @param     bool swap (true : swap RGB to BGR; false, do nothing)
* @return    cv::Mat
* Access     public static 
*/
template<typename Policy>
template<typename Image>
cv::Mat qimage_to_mat<Policy>::run(Image &&img, bool swap)
{
    if(img.isNull()){
        return cv::Mat();
    }

    switch (img.format()) {
    case QImage::Format_RGB888:{
        cv::Mat result = Policy::start(img, CV_8UC3);
        if(swap){
            cv::cvtColor(result, result, CV_RGB2BGR);
        }
        return result;
    }
    case QImage::Format_Indexed8:{
        return Policy::start(img, CV_8U);
    }
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32:
    case QImage::Format_ARGB32_Premultiplied:{
        return Policy::start(img, CV_8UC4);
    }
    default:
        break;
    }

    return cv::Mat();
}


/**
*
*  copy cv::Mat into QImage
* 
* FullName   opencvtoqt::mat_to_qimage_cpy
* Qualifier 
* @param     cv::Mat const & mat 
* @param     bool swap (true : swap RGB to BGR; false, do nothing)
* @return    QT_NAMESPACE::QImage
* Access     public 
*/
QImage mat_to_qimage_cpy(cv::Mat const &mat, bool swap)
{
    if(!mat.empty()){
        switch(mat.type()){

        case CV_8UC3 :{
            if(swap){
                return mat_to_qimage_cpy_policy(mat, QImage::Format_RGB888).rgbSwapped();
            }else{
                return mat_to_qimage_cpy_policy(mat, QImage::Format_RGB888);
            }
        }

        case CV_8U :{
            return mat_to_qimage_cpy_policy(mat, QImage::Format_Indexed8);
        }

        case CV_8UC4 :{
           return mat_to_qimage_cpy_policy(mat, QImage::Format_ARGB32);
        }

        }
    }

    return QImage();
}

/**
*
*  make Qimage and cv::Mat share the same buffer, the resource of the cv::Mat must not deleted before the QImage finish the jobs.
* 
* FullName   opencvtoqt::mat_to_qimage_ref
* Qualifier 
* @param     cv::Mat & mat 
* @param     bool swap (true : swap RGB to BGR; false, do nothin)
* @return    QT_NAMESPACE::QImage
* Access     public 
*/
QImage mat_to_qimage_ref(cv::Mat &mat, bool swap)
{
    if(!mat.empty()){
        switch(mat.type()){

        case CV_8UC3 :{
            if(swap){
                cv::cvtColor(mat, mat, CV_BGR2RGB);
            }

            return mat_to_qimage_ref_policy(mat, QImage::Format_RGB888);
        }

        case CV_8U :{
            return mat_to_qimage_ref_policy(mat, QImage::Format_Indexed8);
        }

        case CV_8UC4 :{
            return mat_to_qimage_ref_policy(mat, QImage::Format_ARGB32);
        }

        }
    }

    return QImage();
}

/**
*
*  transform QImage to cv::Mat by copy QImage to cv::Mat
*
* FullName   opencvtoqt::qimage_to_mat_cpy
* Qualifier 
* @param     QImage const & img 
* @param     bool swap (true : swap RGB to BGR; false, do nothing)
* @return    cv::Mat
* Access     public 
*/
cv::Mat qimage_to_mat_cpy(QImage const &img, bool swap)
{
    return qimage_to_mat<qimage_to_mat_cpy_policy>::run(img, swap);
}


/**
*
*  transform QImage to cv::Mat by sharing the buffer
*
* FullName   opencvtoqt::qimage_to_mat_ref
* Qualifier 
* @param     QImage & img 
* @param     bool swap 
* @return    cv::Mat
* Access     public 
*/
cv::Mat qimage_to_mat_ref(QImage &img, bool swap)
{
    return qimage_to_mat<qimage_to_mat_ref_policy>::run(img, swap);
}


