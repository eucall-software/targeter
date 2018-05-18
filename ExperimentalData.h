#ifndef EXPERIMENTALDATA_H
#define EXPERIMENTALDATA_H

#include <QString>
#include <QPoint>
#include <QRect>
#include <vector>
#include "Settings.h"



struct target {
	// example test target
	QString test_target_filename;
	QRect test_target_rect;
	QRect test_target_rect_absolute;

	// image file
	QString image_filename;
	QString image_folder;
	QPoint image_absolute_offset;
	QString image_description;		// what is this image scan 1,1 or which target or which sub-frame

	// experimental log (do we save this in xml?)
	SettingsValues settings;		// image analysis settings that gave rise to the analysis 
	QString image_processing_steps;	// lab book record/history of processing with name of image files (eg. image 1) created at 
									// each step with date for each start and end of program usage, with time taken for processing

	// targets within image
	std::vector<QString> targets_filenames;
	std::vector<QPoint> targets_center;	// belongs to image
	std::vector<QRect> targets_rect;

	std::vector<QPoint> fiducial_marks;
};


class ExperimentalData
{
public:
	ExperimentalData();
	~ExperimentalData();


	std::vector<QString> image_filenames;
	std::vector<QPoint> target_center;	// belongs to image
	std::vector<QRect> target_rect;
	std::vector<QString> subimage_filename;

	// target coords/rect in image
	// example target (to find) image filename
	// example target (to find) image coordinate/rect
	// example target (to find) subimage
	// sub images of targets
};

#endif