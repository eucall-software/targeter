#ifndef GLOBALS_H
#define GLOBALS_H

//#include <vld.h>
#include <QPolygon>
#include <QRect>
#include <QDebug>
#include <QMessageBox>
#include <QIcon>
#include <qimage.h>

#ifdef _MSC_VER
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

/**
* enum to set drawing mode of drawing object
*/
namespace drawingMode {
	enum drawingMode { rect, poly, circle, none };
}
/**
* enum to set type of image
*/
namespace imageType {
	enum imageType { display, target, test, mask, roi, cclabels, score, centroids };
}
/**
* enum to set algorithm type for target detection
*/
namespace algoType { 
	enum algoType{ COOC, LAPLACIAN, SQDIFF, SQDIFF_NORMED, CCORR, CCORR_NORMED, CCOEFF, CCOEFF_NORMED };
}

//0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED

/**
* macro function to return strings for enum algoType
*/
#define ALGOSTRINGS(i) (	\
	(i==algoType::COOC? "COOC": \
	(i==algoType::LAPLACIAN? "LAPLACIAN":  \
	(i==algoType::SQDIFF? "SQDIFF": \
	(i==algoType::SQDIFF_NORMED? "SQDIFF_NORMED": \
	(i==algoType::CCORR? "CCORR": \
	(i==algoType::CCORR_NORMED? "CCORR_NORMED": \
	(i==algoType::CCOEFF? "CCOEFF": \
	(i==algoType::CCOEFF_NORMED ? "CCOEFF_NORMED" : \
	"NOTFOUND") ))))))) )


//	const char* algoTypes[] = { "COOC", "LAPLACIAN", "SQDIFF", "SQDIFF_NORMED", "CCORR", "CCORR_NORMED", "CCOEFF", "CCOEFF_NORMED"}; \
//	algoTypes[ i<0?0:(i>CCOEFF_NORMED?CCOEFF_NORMED:i)]; \

/**
* structure defining setting values (settings values serialised to file and used in settings dialog)
*/
struct SettingsValues {
	int cluster;				/// number of clusters 
	int distance;				/// number of distance pixels
	bool autoThreshold;			/// whether to auto threshold
	int NoClustersThreshold;	/// number of clusters in threshold

	int threshold_min;			/// minimum threshold value
	int threshold_max;			/// maximum threshold value

	int ScoreThreshold;

	int sizeToleranceSmaller;	/// tolerance to size of detected regions, if smaller than tolerance then not selected
	int sizeToleranceLarger;	/// tolerance to size of detected regions, if larger than tolerance then not selected

	int huMomentSimilarity;		/// how similar in shape obects should be

	algoType::algoType algorithmType;		/// type of algorithm used to find target

	/**
	*
	*  function to serialise settings parameters to file
	*
	* @author    David Watts
	* @since     2017/03/07
	* 
	* FullName   SettingsValues::serialize
	* Qualifier 
	* @param     QDataStream & stream 
	* @return    void
	* Access     public 
	*/
	void serialize(QDataStream& stream)
	{
		stream.setVersion(QDataStream::Qt_4_5);

		stream << cluster
			<< distance
			<< NoClustersThreshold
			<< threshold_min
			<< threshold_max
			<< sizeToleranceSmaller
			<< sizeToleranceLarger
			<< huMomentSimilarity
			<< ScoreThreshold
			<< autoThreshold
			<< (int)algorithmType;
	}

	/**
	*
	*  function to read settings values from file
	*
	* @author    David Watts
	* @since     2017/03/07
	* 
	* FullName   SettingsValues::deserialize
	* Qualifier 
	* @param     QDataStream & stream 
	* @return    void
	* Access     public 
	*/
	void deserialize(QDataStream& stream)
	{
		//QDataStream stream(byteArray);
		stream.setVersion(QDataStream::Qt_4_5);

		int algo;

		stream >> cluster 
			>> distance 
			>> NoClustersThreshold 
			>> threshold_min 
			>> threshold_max 
			>> sizeToleranceSmaller 
			>> sizeToleranceLarger 
			>> huMomentSimilarity 
			>> ScoreThreshold
			>> autoThreshold 
			>> algo;

		algorithmType = (algoType::algoType)algo;
	}
};
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
    QPolygon polygon;
    int radius;
    void printDebug()
    {
        qDebug() << "boundingBox="<< boundingBox << " type= " << type << " polygon=" << polygon << " radius= " << radius << endl;
    }
};



//#define PYLON
//#define DEBUGPRINT
//#define ONMOUSEPAINTDEBUGPRINT

#endif // GLOBALS_H
