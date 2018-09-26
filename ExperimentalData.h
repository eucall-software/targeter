#ifndef EXPERIMENTALDATA_H
#define EXPERIMENTALDATA_H

#include <QString>
#include <QPoint>
#include <QRect>
#include <vector>
#include "Settings.h"

/*
struct target 
{
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
	QVector<QString> targets_filenames;
	QVector<QPoint> targets_center;	// belongs to image
	QVector<QRect> targets_rect;

	QVector<QPoint> fiducial_marks;
};
*/

/* image : 
		scanRegions : []
			stageMovements : []
				image -> targets  : []
*/

// information about target
class Target{
public:
	Target(){};

	QVector3D position;		/// position of target
	QPoint imagePosition;
	QRect region;			/// roi of target region in image
	QString image;			/// link to image file of target roi
	int ID;					/// uid number of target
} ;

class ImageData;

// information about position of stage
class StageCoordinates {
public:
	StageCoordinates() {};

	StageCoordinates(const StageCoordinates& sc)
	{
		index = sc.index;
		stagePosition3D = sc.stagePosition3D;
		tileSize = sc.tileSize;
		childImage = sc.childImage;
	}

	QPoint index;				/// raster index position of image
	QVector3D stagePosition3D;	/// actual stage positions of image
	QSize tileSize;				/// actual size of region in image		

	// image scanned of this region
	QSharedPointer<ImageData> childImage;		/// scanned image
};


// description of region to be scanned for image
class ScanRegion {
public:
	ScanRegion(){
		stagePositionIndex = 0;
		ID = "";
		name = "";
		regionDescription = "";
		scanRegion = QRectF();
	};
	~ScanRegion(){ clear(); };
	void clear(){ stagePositions.empty(); }

	ScanRegion(const ScanRegion& sr)
	{
		regionShape = sr.regionShape;
		ID = sr.ID;
		name = sr.name;
		regionDescription = sr.regionDescription;
		scanRegion = sr.scanRegion;
		scanRegionIndex = sr.scanRegionIndex;

		stagePositions.empty();

		foreach(StageCoordinates sc, sr.stagePositions)
			stagePositions.append(sc);
		stagePositionIndex = sr.stagePositionIndex;
	}

	StageCoordinates& getStagePosition(bool& bFound){
	bFound = false;
		if (stagePositionIndex < stagePositions.length()) {
			bFound = true;
			return stagePositions[stagePositionIndex];
		}
	}

	StageCoordinates& incrementStagePosition(bool& bFound)
	{
		stagePositionIndex++;
		StageCoordinates sc = getStagePosition(bFound);
		if(!bFound)
			stagePositionIndex--;
		else
			return sc;
	}

	// scan region shape information
	drawingMode::drawingMode regionShape;	/// region shape type
	
	// annotation information for region (copied from drawing shape)
	QString ID;
	QString name;
	QString regionDescription;	/// annotated region descriptor

	QRectF scanRegion;			/// position of region in image
	int scanRegionIndex;		/// index of region

	// scan information
	QVector<StageCoordinates> stagePositions;			/// list of stage coordinates for this region
	int stagePositionIndex;								/// index of stage position being processed	
};



// information obtained from a single image 
 class ImageData
 {
 public:
	ImageData(){
	scanRegionIndex=0;
	targetListIndex=0;
	filename = "";
	imageDescription = "";
	shapeType = drawingMode::none;
	FrameID = "";
	patternRegion = QRect();
	SubFrameID = "";
	subRegionID = "";
	};

	~ImageData(){clear();}

	void clear(){
		scanRegion.clear();
		scanRegion.empty();
		targetList.empty();
	}

	ImageData(const ImageData& id)
	{
		filename = id.filename;
		imageDescription = id.imageDescription;
		shapeType = id.shapeType;
		FrameID = id.FrameID;
		patternRegion = id.patternRegion;
		SubFrameID = id.SubFrameID;
		subRegionID = id.subRegionID;

		scanRegion.empty();
		foreach(ScanRegion sl, id.scanRegion)
			scanRegion.append(sl);	
		
		scanRegionIndex = id.scanRegionIndex;					
		
		targetList.empty();
		foreach(Target tar, id.targetList)
			targetList.append(tar);	
	}

	Target& getTarget(bool& bFound) {
		bFound = false; 
		if (targetListIndex < targetList.length()) {
			bFound = true;
			return targetList[targetListIndex];
		}
	};
	ScanRegion& getScanRegion(bool& bFound) {
		bFound = false;
		if (scanRegionIndex < scanRegion.length()){
			bFound = true;
			return scanRegion[scanRegionIndex];
		}
	};

	ScanRegion& incrementScanRegion(bool& bFound)
	{
		scanRegionIndex++;
		ScanRegion sc = getScanRegion(bFound);

		sc.stagePositionIndex = 0;
		if (!bFound)
			scanRegionIndex--;
		else
			return sc;
	}

	QString filename;
	QString imageDescription;

	// target region shape information in the case of single image
	drawingMode::drawingMode shapeType;
	
	// image information in the case of single image (ie. not scanned)
	QString FrameID;
	QRect patternRegion;
	QString SubFrameID;
	QString subRegionID;

	// scan region information (if any)
	QVector<ScanRegion> scanRegion;			/// regions in image that will be scanned
	int scanRegionIndex;					/// index of region being processed

	// list of targets
	QVector<Target> targetList;		/// list of targets	
	int targetListIndex;	
};





//QVector<StageMovement> scannedAreas;	/// scanned information if any


/*
// image and its corresponding stage position
typedef struct {
	QVector3D stagePosition3D;	/// position of stage for this image
	ImageData imageData;
} scannedImage;

// a scan of a frame, with scan regions, frame id and image filename
typedef struct {
	QVector<scanRegion> scanRegion;	/// string can be region description or ID number
	QString FrameID;
	QString filename;
} TargetDetectionExperiments;

// information on scanned areas
typedef struct {
	QVector<QSharedPointer<drawingObject>> m_overviewShape;

	StagePosition<double> stagePositionsZ;
	StagePosition<StageMovement> stagePositionsXY;
	QVector<Target> m_Targets;
} ScanResult;



class ExperimentalData
{
public:
	ExperimentalData() {
		stagePositionsZ = QSharedPointer<StagePosition<double>>(new StagePosition<double>());
		stagePositionsXY = QSharedPointer<StagePosition<StageMovement>>(new StagePosition<StageMovement>());
	};

	~ExperimentalData() {
		scannedAreas.clear(); 
		shapes.clear();
		m_detected_targets.clear();
		image_filenames.clear();
		subimage_filename.clear();
		processedImages.clear();
	};

	// list of all images in experiment with information about that image and children images
	QVector<ImageData> processedImages;

	// the below not necessary! contained in processed Images
	QVector<QString> image_filenames;
	QVector<QString> subimage_filename;

	QSharedPointer<StagePosition<double>> stagePositionsZ;
	QSharedPointer<StagePosition<StageMovement>> stagePositionsXY;

	// shapes drawn on an image
	QVector<drawingShape> shapes;

	QVector<ScanResult> scannedAreas;									
	
	QVector<Target> m_detected_targets;		/// list of detected target positions 
};

*/

#endif