#ifndef GLOBALS_H
#define GLOBALS_H

//#include <vld.h>
#include <QPolygon>
#include <QString>
#include <QRect>
#include <QDebug>
//#include <QMessageBox>
//#include <QIcon>
#include <QVector3D>
//#include <qimage.h>

class drawingObject;

////////////////////////////////////////////////////////////
// these two defines are for CUDA and IMAGEMAGICK support
#define _HAVE_IMAGEMAGICK
#define _CUDA_CODE_COMPILE_
////////////////////////////////////////////////////////////

#if defined(_CUDA_CODE_COMPILE_) && !defined(LOADED_CUDA)
#pragma comment (lib, "cudart.lib")
#define LOADED_CUDA
#endif

#if defined(_HAVE_IMAGEMAGICK) && defined(_DEBUG) && !defined(LOADED_IM)
#pragma comment (lib, "CORE_DB_MagickCore_.lib")
#pragma comment (lib, "CORE_DB_Magick++_.lib")
#pragma comment (lib, "CORE_DB_MagickWand_.lib")
#define LOADED_IM
#elif defined(_HAVE_IMAGEMAGICK) && !defined(LOADED_IM)
#pragma comment (lib, "CORE_RL_MagickCore_.lib")
#pragma comment (lib, "CORE_RL_Magick++_.lib")
#pragma comment (lib, "CORE_RL_MagickWand_.lib")
#define LOADED_IM
#endif

// #define _CUDA_TEXTURE_MEMORY


#ifdef _MSC_VER
#define NOMINMAX
#define WINDOWS_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <opencv/cxcore.h>
#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}
#else
#define DBOUT( s )            \
{                             \
	std::cout << s            \
}
#endif

#ifndef MIN
#  define MIN(a,b)  ((a) > (b) ? (b) : (a))
#endif

#ifndef MAX
#  define MAX(a,b)  ((a) < (b) ? (b) : (a))
#endif

typedef QMap<int, QColor> QIntColorMap;
typedef QMap<int, QVector3D> QInt3DMap;
typedef QMap<int, QPointF> QIntPointMap;
typedef QList<QVector3D> QVector3Dlist;


namespace NEWPORT_STATUS {
	enum status { ready, config, notref, disable, jogging, homing, moving, null };
}

namespace CONSOLECOLOURS {
	enum colour {Information, Data, Question, Warning, Critical};
}

namespace SAMPLINGTYPE {
	enum type {
		grid, edge, center, noedge
	};
}

#define SAMPLINGTYPE_STRINGS(i) (	\
	(i==SAMPLINGTYPE::type::grid? "Complete region": \
	(i==SAMPLINGTYPE::type::edge? "Edge of region":  \
	(i==SAMPLINGTYPE::type::center? "Center of region": \
	(i==SAMPLINGTYPE::type::noedge? "Avoid edge": \
	"NOTFOUND") ))) )

namespace FIDUCIAL {
	enum position {
		topleft_overview, topright_overview, bottomleft_overview, bottomright_overview, 
		topleft_microscope, topright_microscope, bottomleft_microscope, bottomright_microscope, 
	};
}

namespace ACTIONS {
	enum action {
		nothing, getMosaic, displayOnly, focusStack, addToMosaic, MosaicFinished, fineFocus, coarseFocus, jog, quit
	};
}

#define ACTION_STRINGS(i) (	\
	(i==ACTIONS::action::nothing? "nothing": \
	(i==ACTIONS::action::getMosaic? "getMosaic":  \
	(i==ACTIONS::action::displayOnly? "displayOnly": \
	(i==ACTIONS::action::focusStack? "focusStack": \
	(i==ACTIONS::action::addToMosaic? "addToMosaic": \
	(i==ACTIONS::action::MosaicFinished? "MosaicFinished":  \
	(i==ACTIONS::action::fineFocus? "fineFocus": \
	(i==ACTIONS::action::coarseFocus? "coarseFocus": \
	(i==ACTIONS::action::jog? "jog": \
	(i==ACTIONS::action::quit? "quit":  \
	"NOTFOUND") ))))))))) )

namespace FOCUSALGO {
	enum algo {
		LAPM, LAPV, GLVN, TENG, DXDY, HAARPY
	};
}

#define FOCUS_ALGO_STRINGS(i) (	\
	(i==FOCUSALGO::algo::LAPM? "modified Laplacian": \
	(i==FOCUSALGO::algo::LAPV? "variance Of Laplacian":  \
	(i==FOCUSALGO::algo::GLVN? "normalized Graylevel Variance": \
	(i==FOCUSALGO::algo::TENG? "tenengrad": \
	(i==FOCUSALGO::algo::DXDY? "Horizontal/Vertical derivative energy": \
	(i==FOCUSALGO::algo::HAARPY? "Haar Pyramid energy":  \
	"NOTFOUND") ))))) )

namespace FOCUSOPT {
	enum FocusType {
		fullRange,			// uses ranges from settings page [slowest]
		centered,						// centers focus range at best focus position
		bestRange,						// range adapts to previous focus range
		centeredBestRange,				// combination of centered and bestrange	
		coarse,							// just coarse part of full range
		fine,							// just fine part of full range
		interpolate,					// interpolate next centered range position
		interpolateBestRange,			// as interpolate with adapted focus range
		conditionalFine,				// will use focus image if > threshold do fine focus at this position.
		conditionalSearch,				// will use focus image if > threshold, otherwise search for focus > threshold, if no focus found > threshold take best. 
		interpolateConditionalSearch	// will start with interpolate position but otherwise as conditional Search [fastest]
	};	
}

#define FOCUSOPTSTRINGS(i) (	\
	(i==FOCUSOPT::FocusType::fullRange? "Full Range": \
	(i==FOCUSOPT::FocusType::centered? "Centered": \
	(i==FOCUSOPT::FocusType::bestRange? "Best Range":  \
	(i==FOCUSOPT::FocusType::centeredBestRange? "Centered Best Range": \
	(i==FOCUSOPT::FocusType::coarse? "Coarse Only": \
	(i==FOCUSOPT::FocusType::fine? "Fine Only": \
	(i==FOCUSOPT::FocusType::interpolate ? "Interpolate" : \
	(i==FOCUSOPT::FocusType::interpolateBestRange ? "Interpolate Best Range" : \
	(i==FOCUSOPT::FocusType::conditionalFine ? "fine range if well focused" : \
	(i==FOCUSOPT::FocusType::conditionalSearch ? "Search if not well focused" : \
	(i==FOCUSOPT::FocusType::interpolateConditionalSearch ? "Interpolate focus then search of not well focused" : \
	"NOTFOUND") )))))))))) )

#define FIDUCIAL_POSITION_STRINGS(i) (	\
	(i==FIDUCIAL::position::topleft_overview? "top left overview camera": \
	(i==FIDUCIAL::position::topright_overview? "top right overview camera":  \
	(i==FIDUCIAL::position::bottomleft_overview? "bottom left overview camera": \
	(i==FIDUCIAL::position::bottomright_overview? "bottom right overview camera": \
	(i==FIDUCIAL::position::topleft_microscope? "top left microscope camera": \
	(i==FIDUCIAL::position::topright_microscope? "top right microscope camera":  \
	(i==FIDUCIAL::position::bottomleft_microscope? "bottom left microscope camera": \
	(i==FIDUCIAL::position::bottomright_microscope? "bottom right microscope camera": \
	"NOTFOUND") ))))))) )



#define FIDUCIAL_POSITION_STRINGS_SHORT(i) (	\
	(i==FIDUCIAL::position::topleft_overview? "TL_O": \
	(i==FIDUCIAL::position::topright_overview? "TR_O":  \
	(i==FIDUCIAL::position::bottomleft_overview? "BL_O": \
	(i==FIDUCIAL::position::bottomright_overview? "BR_O": \
	(i==FIDUCIAL::position::topleft_microscope? "TL_M": \
	(i==FIDUCIAL::position::topright_microscope? "TR_M":  \
	(i==FIDUCIAL::position::bottomleft_microscope? "BL_M": \
	(i==FIDUCIAL::position::bottomright_microscope? "BR_M": \
	"NOTFOUND") ))))))) )

#define NEWPORT_STATUS_STRINGS(i) (	\
	(i==NEWPORT_STATUS::ready? "READY": \
	(i==NEWPORT_STATUS::config? "CONFIGURATION":  \
	(i==NEWPORT_STATUS::notref? "NOT REFERENCED": \
	(i==NEWPORT_STATUS::disable? "DISABLE": \
	(i==NEWPORT_STATUS::jogging? "JOGGING": \
	(i==NEWPORT_STATUS::homing? "HOMING": \
	(i==NEWPORT_STATUS::moving? "MOVING": \
	(i==NEWPORT_STATUS::null ? "UNKNOWN" : \
	"NOTFOUND") ))))))) )



namespace CALIBRATE {
	enum { DETECTION = 0, CAPTURING = 1, CALIBRATED = 2 };
}

/************************************************************************/
/* enum for camera types                                                */
/************************************************************************/
namespace cameraType {
	enum camera { overview, microscope, none };
}

#define CAMERATYPE(i) (	\
	(i==cameraType::camera::overview? "overview": \
	(i==cameraType::camera::microscope? "microscope":  \
	(i==cameraType::camera::none? "none":  \
	"NOTFOUND") )))

namespace drawingItems {
	enum drawingItems { hough, grid };
}

#define DRAWINGITEMS(i) (	\
	(i==drawingItems::hough? "hough": \
	(i==drawingItems::grid? "grid":  \
	"NOTFOUND") ))

namespace drawingColour {
	enum colour { black, white, mask_white, mask_black, none };
}

#define DRAWINGCOLOUR(i) (	\
	(i==drawingItems::black? "black": \
	(i==drawingItems::white? "white":  \
	(i==drawingItems::mask_white? "mask white":  \
	(i==drawingItems::mask_black? "mask black":  \
	(i==drawingItems::none? "none":  \
	"NOTFOUND") )))) )

/**
* enum to set drawing mode of drawing object
*/
namespace drawingMode {
	enum drawingMode { rect, poly, circle, cross, fiducial, centerObjective, focusPlane, sampleSpacing, shift, select, any, none };
}

#define DRAWINGMODESTRINGS(i) (	\
	(i==drawingMode::rect? "rectangle": \
	(i==drawingMode::poly? "polygon": \
	(i==drawingMode::circle? "circle":  \
	(i==drawingMode::cross? "cross":  \
	(i==drawingMode::fiducial? "fiducial":  \
	(i==drawingMode::centerObjective? "Center Objective": \
	(i==drawingMode::focusPlane? "Focus Plane": \
	(i==drawingMode::sampleSpacing? "Define Sample Spacing": \
	(i==drawingMode::shift? "shift":  \
	(i==drawingMode::select? "select": \
	(i==drawingMode::any? "any": \
	(i==drawingMode::none? "none": \
	"NOTFOUND") ))))))))))) )

/**
* enum to set type of image
*/
namespace imageType {
	enum imageType { display, target, test, mask, background, roi, cclabels, score, centroids, hue, any, mosaic, video };
}

namespace thresholdType {
	enum thresholdType { Range, Otzu, cluster2, adaptive, posterize };
}

namespace shapeAnnotationType {
	enum Type { target, SubFrame, pattern, barcode, none};
}

#define SHAPEANNOTATIONSTRINGS(i) (	\
	(i==shapeAnnotationType::target? "target": \
	(i==shapeAnnotationType::SubFrame? "SubFrame": \
	(i==shapeAnnotationType::pattern? "pattern":  \
	(i==shapeAnnotationType::barcode? "barcode": \
	(i==shapeAnnotationType::none? "none": \
	"NOTFOUND") )))) )

/**
* enum to set algorithm type for target detection
*/
namespace algoType { 
	enum algoType { SQDIFF, SQDIFF_NORMED, CCORR, CCORR_NORMED, CCOEFF, CCOEFF_NORMED, HAAR, LAWS, COOC, FASTCOOC, LAPLACIAN };
#define LASTALGO algoType::LAPLACIAN
}

namespace RotateFlags {
	enum RotateFlags {
		ROTATE_90_CLOCKWISE = 0, //Rotate 90 degrees clockwise
		ROTATE_180 = 1, //Rotate 180 degrees clockwise
		ROTATE_90_COUNTERCLOCKWISE = 2, //Rotate 270 degrees clockwise
	};
}

/**
* macro function to return strings for enum algoType
*/
#define ALGOSTRINGS(i) (	\
	(i==algoType::HAAR? "HAAR": \
	(i==algoType::COOC? "COOC": \
	(i==algoType::FASTCOOC? "FASTCOOC": \
	(i==algoType::LAWS? "LAWS": \
	(i==algoType::LAPLACIAN? "LAPLACIAN":  \
	(i==algoType::SQDIFF? "SQDIFF": \
	(i==algoType::SQDIFF_NORMED? "SQDIFF_NORMED": \
	(i==algoType::CCORR? "CCORR": \
	(i==algoType::CCORR_NORMED? "CCORR_NORMED": \
	(i==algoType::CCOEFF? "CCOEFF": \
	(i==algoType::CCOEFF_NORMED ? "CCOEFF_NORMED" : \
	"NOTFOUND") )))))))))) )

/**
* macro function to return strings for enum algoType
*/
#define IMAGETYPESTRINGS(i) (	\
	(i==imageType::display? "display": \
	(i==imageType::target? "target": \
	(i==imageType::test? "detection":  \
	(i==imageType::mask? "mask": \
	(i==imageType::background? "background": \
	(i==imageType::roi? "region of interest": \
	(i==imageType::cclabels? "connected components": \
	(i==imageType::score? "score": \
	(i==imageType::centroids? "centroids": \
	(i==imageType::hue ? "hue" : \
	(i==imageType::mosaic ? "mosaic" : \
	(i==imageType::any ? "miscellaneous" : \
	"NOTFOUND") ))))))))))) )

namespace calibrateAlgoType {
	enum algoType { CHESSBOARD, CIRCLES_GRID, ASYMMETRIC_CIRCLES_GRID };
}

//0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED


#define THRESHOLDSTRINGS(i) ( \
	(i==thresholdType::Range? "Range Threshold": \
	(i==thresholdType::Otzu? "Auto Threshold (Otzu)":  \
	(i==thresholdType::cluster2? "Auto Threshold (Cluster)": \
	(i==thresholdType::adaptive? "Adaptive Threshold": \
	(i==thresholdType::posterize? "Posterize (greyscale clusters)": \
	"NOTFOUND"))))) )

//	const char* algoTypes[] = { "COOC", "LAPLACIAN", "SQDIFF", "SQDIFF_NORMED", "CCORR", "CCORR_NORMED", "CCOEFF", "CCOEFF_NORMED"}; \
//	algoTypes[ i<0?0:(i>CCOEFF_NORMED?CCOEFF_NORMED:i)]; \

/**
* structure to represent shape being drawn
*/
class drawingShape {
public:
	drawingShape(){
		boundingBox = QRect();
		type = drawingMode::none;
		colour = drawingColour::black;
		polygon = QPolygon();
		radius = 0;
		drawingObjectIndex = 0;

		// annotation information
		ID = "";
		name = "";
		desc = "";
		regionType = shapeAnnotationType::none;
	}

	drawingShape(const drawingShape& ds)
	{
		boundingBox = ds.boundingBox;
		type = ds.type;
		colour = ds.colour;
		polygon = ds.polygon;
		radius = ds.radius;
		drawingObjectIndex = ds.drawingObjectIndex;

		// annotation information
		ID = ds.ID;
		name = ds.name;
		desc = ds.desc;
		regionType = ds.regionType;
	}

	QRect boundingBox;
	drawingMode::drawingMode type;
	drawingColour::colour colour;
	QPolygon polygon;
	int radius;
	int drawingObjectIndex;

	// annotation information
	QString ID;
	QString name;
	QString desc;
	shapeAnnotationType::Type regionType;

	void printDebug()
	{
		qDebug() << "boundingBox=" << boundingBox << " type= " << type << " polygon=" << polygon << " radius= " << radius << endl;
	}

	QString toJSON()
	{
		QString str = "{shape:{boundingBox:{x:" + QString::number(boundingBox.x()) + ", y:" + QString::number(boundingBox.y()) + 
			", width:" + QString::number(boundingBox.width()) + ", height:" + QString::number(boundingBox.height()) + "}, ";

		QString s = DRAWINGMODESTRINGS(type);
		str += "shape:" + s + ", ID:" + ID + ",name:" + name + ", description:" + desc + ", type:" + SHAPEANNOTATIONSTRINGS(regionType) + "}}";
		return str;
	}
};
/*
class StageMovement {
public:
	StageMovement()
	{
		index = QPoint();
		stagePosition3D = QVector3D();
		tileSize = QSize();
		scanRegion = QRectF();
		regionShape = drawingMode::none;
		scanRegionIndex = 0;
		imageFilename = "";
		shape = QSharedPointer<drawingShape>();
	}

	StageMovement(double nan) : StageMovement() {double local = nan;};

	StageMovement(const StageMovement& sm)
	{
		index = sm.index;
		stagePosition3D = sm.stagePosition3D;
		tileSize = sm.tileSize;
		scanRegion = sm.scanRegion;
		scanRegionIndex = sm.scanRegionIndex;
		regionShape = sm.regionShape;
		shape = sm.shape;
		imageFilename = sm.imageFilename;
	}

	QPoint index;
	QString imageFilename;
	QVector3D stagePosition3D;
	QSize tileSize;
	QRectF scanRegion;
	int scanRegionIndex;
	drawingMode::drawingMode regionShape;
	QSharedPointer<drawingShape> shape;
};
*/
typedef struct {
	double focusValue;
	cv::Mat focusImage;
} FocusImage;

typedef struct {
	float* coMatrixIntensity;
	float* coMatrixHue;
	float averageIntensity;
	float averageHue;
	cv::Mat hueHist;
	cv::Mat intensityHist;
	int coDIMX;
	int coDIMY;
	int coDIMZ;
	float maxDist;
	int regionHeight;
	int regionWidth;
	int incrementWidth;
	int incrementHeight;
} COOCMatrix;

struct FocusParameters {
	FocusParameters(){
		FOCUS_STATE = ACTIONS::coarseFocus;
		noFocusStackImages = 0;
		dBestFocusPosition = 0;
		BestFocusPosition = 999;
		BestFocusRange = 999;
		bestFocusValue = -1;
	}

	ACTIONS::action FOCUS_STATE;
	double BestFocusPosition;
	double dBestFocusPosition;
	int BestFocusRange;
	double bestFocusValue;
	int noFocusStackImages;

	//focus stack
	QMap<double, FocusImage> focusStackData;	/// list of images used for focus stack focus finding or to make focus stack image
	QVector<double> focusValues;			/// focus values to use for optimizing focus routine.
};

template<class T> class StagePosition {
public:
	StagePosition() {
		currentPosition = 0; 
	}
	~StagePosition() { removeAll(); }


	StagePosition(const StagePosition& pos)
	{
		placeToMove = pos.placeToMove;
		currentPosition = pos.currentPosition;
	}

	T head() {
		if (placeToMove.length() > 0)
			return placeToMove[0];
		else
			return T(nan(""));
	}

	T tail() {
		if (placeToMove.length() > 0)
			return placeToMove[placeToMove.length() - 1];
		else
			return T(nan(""));
	}

	bool moveToFirstPosition()
	{
		if (checkIfValid())
		{
			currentPosition = 0;
			return true;
		}
		return false;
	};

	void removeAll() { if(checkIfValid()) placeToMove.clear(); };
	bool checkIfValid() { return !placeToMove.isEmpty() && placeToMove.size() > 0; };
	void setPosition(int pos) { currentPosition = pos; };

	int getSize() { return placeToMove.size(); };
	void append(T val ) { placeToMove.append(val); };
	bool isEmpty() { return placeToMove.isEmpty(); }
	bool checkIfValidPosition() { return currentPosition < placeToMove.length(); };
	
	T getCurentPosition() {
		if (checkIfValidPosition())
			return placeToMove[currentPosition];
		else
			return T(nan(""));
	};

	void moveIterator() { currentPosition++; };
	
private:
	QVector<T> placeToMove;
	int currentPosition;
};

typedef struct {
	ACTIONS::action act; 
	double z;
	double focusValue;
	cv::Mat focusImage;
} FocusResult;

typedef struct {
	int imageIndex;

	// list of drawing objects for this image
	QVector<QSharedPointer<drawingObject>> drawingObjects;
} GraphicsImage;

/**
* structure to represent histogram bar
*/
struct histogramBar {
	float freq;	/// count of histogram (normalised)
	double hue;	/// position of histogram (hue or grayscale)
public:
	void printMe(std::string s = "")
	{
		DBOUT(s.data() << "(h=" << hue << ", f=" << freq << "), " << std::endl);
	}
};

/**
* structure to represent vector of histogram bars, ie. whole histogram
*/
struct histCluster {
	std::vector<histogramBar> column;	/// each histogram column as vector
	float varHue;	/// variance
	float meanHue;  /// mean
	std::vector<int> hueList;
public:
	void printMe(std::string s = "") {
		DBOUT(s.data() << " histCluster: varHue=" << varHue << " meanHue=" << meanHue << std::endl);
		DBOUT("huelist = ");

		std::vector<int>::iterator jI;

		for (jI = hueList.begin(); jI != hueList.end(); jI++)
			DBOUT(*jI << ", ");
		DBOUT(std::endl);

		DBOUT("column <histogramBar> = ");

		std::vector<histogramBar>::iterator iI;

		for (iI = column.begin(); iI != column.end(); iI++)
			(*iI).printMe();

		DBOUT(std::endl);
	}
};

struct entropyCluster {
	float freq;
	std::vector<int> hueList;
public:
	void printMe(std::string s = "") {
		DBOUT(s.data() << " histCluster: freq=" << freq << std::endl);
		DBOUT("huelist = ");

		std::vector<int>::iterator jI;

		for (jI = hueList.begin(); jI != hueList.end(); jI++)
			DBOUT(*jI << ", ");
		DBOUT(std::endl);
	}
};

#define _BASLER_PYLON
//#define DEBUGPRINT
//#define ONMOUSEPAINTDEBUGPRINT

#endif // GLOBALS_H
