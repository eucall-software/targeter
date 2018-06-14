#ifndef GLOBALS_H
#define GLOBALS_H

//#include <vld.h>
#include <QPolygon>
#include <QString>
#include <QRect>
#include <QDebug>
#include <QMessageBox>
#include <QIcon>
#include <QString>
#include <qimage.h>


#ifdef _MSC_VER
#define WINDOWS_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <opencv/cxcore.h>

#define _HAVE_IMAGEMAGICK

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
	enum drawingMode { rect, poly, circle, cross, fiducial, centerObjective, sampleSpacing, shift, select, any, none };
}

#define DRAWINGMODESTRINGS(i) (	\
	(i==drawingMode::rect? "rectangle": \
	(i==drawingMode::poly? "polygon": \
	(i==drawingMode::circle? "circle":  \
	(i==drawingMode::cross? "cross":  \
	(i==drawingMode::fiducial? "fiducial":  \
	(i==drawingMode::centerObjective? "Center Objective": \
	(i==drawingMode::sampleSpacing? "Define Sample Spacing": \
	(i==drawingMode::shift? "shift":  \
	(i==drawingMode::select? "select": \
	(i==drawingMode::any? "any": \
	(i==drawingMode::none? "none": \
	"NOTFOUND") )))))))))) )

/**
* enum to set type of image
*/
namespace imageType {
	enum imageType { display, target, test, mask, background, roi, cclabels, score, centroids, hue, any, mosaic };
}

namespace thresholdType {
	enum thresholdType { Range, Otzu, cluster2, adaptive, posterize };
}

/**
* enum to set algorithm type for target detection
*/
namespace algoType { 
	enum algoType { SQDIFF, SQDIFF_NORMED, CCORR, CCORR_NORMED, CCOEFF, CCOEFF_NORMED, COOC, LAPLACIAN, CROSSENTROPY };
#define LASTALGO algoType::CROSSENTROPY
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
	(i==algoType::COOC? "COOC": \
	(i==algoType::CROSSENTROPY? "CROSSENTROPY": \
	(i==algoType::LAPLACIAN? "LAPLACIAN":  \
	(i==algoType::SQDIFF? "SQDIFF": \
	(i==algoType::SQDIFF_NORMED? "SQDIFF_NORMED": \
	(i==algoType::CCORR? "CCORR": \
	(i==algoType::CCORR_NORMED? "CCORR_NORMED": \
	(i==algoType::CCOEFF? "CCOEFF": \
	(i==algoType::CCOEFF_NORMED ? "CCOEFF_NORMED" : \
	"NOTFOUND") )))))))) )

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


typedef struct {
	double focusValue;
	cv::Mat focusImage;
} FocusImage;

typedef struct {
	double z;
	ACTIONS::action act; 
	double focusValue;
	cv::Mat focusImage;
} FocusResult;

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

/**
* structure to represent shape being drawn
*/
struct drawingShape {
    QRect boundingBox;
	drawingMode::drawingMode type;
	drawingColour::colour colour;
    QPolygon polygon;
    int radius;


    void printDebug()
    {
        qDebug() << "boundingBox="<< boundingBox << " type= " << type << " polygon=" << polygon << " radius= " << radius << endl;
    }
};



#define _BASLER_PYLON
//#define DEBUGPRINT
//#define ONMOUSEPAINTDEBUGPRINT

#endif // GLOBALS_H
