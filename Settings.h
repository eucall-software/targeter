#ifndef SETTINGS_H
#define SETTINGS_H 

#include <QDate>
#include <QSettings>
#include <QVector3D>
#include <QMatrix4x4>
#include <QTransform>
#include "globals.h"
#include "Camera.h"

/**
* structure defining setting values (settings values serialised to file and used in settings dialog)
*/
class SettingsValues
{
public:
	SettingsValues();
	~SettingsValues();

	//void saveProjectInfo();
	//void readProjectInfo();

	QMap<QString, QVariant> getProjectInfoMap();
	void setProjectInfoMap(QMap<QString, QVariant>& map);

	QString appendNumber(QString name, long& count);

	void initialize();

	void serialize(QDataStream& stream);

	void deserialize(QDataStream& stream);

public:
	QSettings m_settings;

	// clustering settings & used in thresholding
	int cluster;				/// number of clusters 
	int distance;				/// number of distance pixels
	int distanceBins;			/// number of bins in distance histogram

								// threshold settings
	bool autoThreshold;			/// whether to auto threshold
	
	int NoClustersThreshold;	/// number of clusters in threshold

	bool displayGrid;			/// whether to display grid on image
	bool centerGrid;			// whether to centre grid so lines cross in centre of image
	double gridOffsetX;			/// grid offset X
	double gridOffsetY;			/// grid offset Y
	double gridSpacingX;		/// grid spacing X
	double gridSpacingY;		/// grid spacing Y

	int threshold_min;			/// minimum threshold value
	int threshold_max;			/// maximum threshold value

	int ScoreThreshold;

	double StdevSmaller;	/// tolerance to size of detected regions, if smaller than tolerance then not selected
	double StdevLarger;	    /// tolerance to size of detected regions, if larger than tolerance then not selected
	double AspectTolerance; /// tolerance to aspect ratio of shape of object.

	int huMomentSimilarity;		/// how similar in shape objects should be

								// target detection settings
	algoType::algoType algorithmType;		/// type of algorithm used to find target
	thresholdType::thresholdType ThresholdType;		/// type of threshold to use

	int scoreAreaFactor;		/// sums score value over a region (proportional to training target size)

								// calibration settings
	bool bCV_CALIB_CB_ADAPTIVE_THRESH;	/// Type of corner finding algorithm for chessboard - Use adaptive thresholding to convert the image to black and white, rather than a fixed threshold level (computed from the average image brightness)
	bool bCV_CALIB_CB_NORMALIZE_IMAGE;	/// Type of corner finding algorithm for chessboard - Normalize the image gamma with equalizeHist() before applying fixed or adaptive thresholding
	bool bCV_CALIB_CB_FILTER_QUADS;		/// Type of corner finding algorithm for chessboard - Use additional criteria (like contour area, perimeter, square-like shape) to filter out false quads extracted at the contour retrieval stage
	bool bCALIB_CB_FAST_CHECK;			/// Type of corner finding algorithm for chessboard - Run a fast check on the image that looks for chessboard corners, and shortcut the call if none is found. This can drastically speed up the call in the degenerate condition when no chessboard is observed
	bool bCALIB_CB_CLUSTERING;			/// Type of algorithm for finding circle centers - uses asymmetric pattern of circles
	bool FixedAspect;				/// Consider only fy as a free parameter, the ratio fx/fy stays the same as in the input cameraMatrix.
	bool ZeroDistortion;			/// If true (non-zero) tangential distortion coefficients  are set to zeros and stay zero
	bool FixPrincipalPointCenter;	/// If checked the principal point is not changed during the global optimization
	bool UseIntrinsicGuess;			/// if checked then the focal length and CCD pixel size used in calibration
	bool TargetImageAsMask;			/// Output target image is a mask rather than crosses
	bool FixFocalLength;

	int focalDistanceOverviewCamera; /// focal length of lens on overview camera
	int focalDistanceMicroscopeCamera; /// focal length of lens on microscope camera

	QIntColorMap objectColours;		// colours to be used for current image drawing (eg. grid, hough lines etc)

	QInt3DMap fiducial_marks_stage;
	QInt3DMap fiducial_marks_stageAndImage;
	QIntPointMap fiducial_marks_image;
	QPointF overviewStagePosition;
	QVector3Dlist focusPoints;

	// target training data

	// cooc histogram
	QScopedPointer<COOCMatrix> coocMatrix;
	// laws texture method
	QVector<cv::Mat> lawsHistTarget;
	QVector<float> lawsHistBiases;

	double mmPerPixel;
	int imageWidth;
	int imageHeight;

	int mosaicImageCols;

	bool bPaddTargetImage;
	int numWaveletLevels;

	QTransform m_coordinateTransform;
	QMatrix4x4 m_transformationMatrix, m_invTransformationMatrix;

	bool bLockFiducial;

	calibrateAlgoType::algoType CalibrateAlgorithm;  /// Type of image : CHESSBOARD = chessboard pattern; CIRCLES_GRID = filled circles spaced in grid pattern; ASYMMETRIC_CIRCLES_GRID = spaced asymmetric circles in grid(body centered cubic in XY plane)

	int calibrateNoRows;	/// Number of inner corners per item for square vertically (ie. number of squares in column -1), for circles it is the number of circles in column
	int calibrateNoCols;	/// Number of inner corners per item for square horizontally (ie. number of squares in row -1), for circles it is the number of circles in row
	int SizeOfSquare;		/// The size of a square in some user defined metric system (pixel, millimeter)

	int overviewCameraSN;	/// Serial number address for overview camera
	int microscopeCameraSN;	/// Serial number address for microscope camera

	QPoint samplingSpacing;
	QPoint samplingOffset;
	
	double XPositionAbsoluteXY;
	double YPositionAbsoluteXY;
	double XPositionRelativeXY;
	double YPositionRelativeXY;
	double PositionRelativeZ;
	double PositionAbsoluteZ;
	double VelocityXY;
	int BaudXY;

	// current stage position - should not be serialised
	double m_stage_position_XY_X;
	double m_stage_position_XY_Y;
	double m_image_position_XY_X;
	double m_image_position_XY_Y;
	double m_stage_position_Z;

	double m_FocusRange;
	double m_DefaultFocusPosition;
	double m_CoarseFocusStep;
	double m_FineFocusStep;
	double m_FocusThresholdFraction;

	int BarcodeThreshold;
	bool BarcodeAutoThreshold;
	bool bProcessGrayscale;
	bool bCorrectBackGround;

	QString s_CommandTextXY;
	QString s_CommandTextZ;

	cameraType::camera activeCamera; /// active camera - defines which camera images will be obtained from 

	FIDUCIAL::position fiducialPos;
	SAMPLINGTYPE::type samplingType;

	FOCUSALGO::algo FocusAlgorithm;

	bool m_bOptimiseFocusRange;
	bool m_bInterpolateFocusPosition;
	bool m_bUseFocusThreshold;
	bool m_bUseCoarseFocusRange;
	bool m_bUseFineFocusRange;
	bool m_bCenterFocus;
	bool m_bUseRegisteredFocusPoints;
	bool m_bShowBestFocusImage;
	bool m_bDetectTargetsWhileScanning;

	Camera calibrationDataOverview;	/// class for camera calibration data
	Camera calibrationDataMicroscope;	/// class for camera calibration data

	QRect s_BarCodeImageRect;

	QString s_project_Username;
	QString s_project_Institute;
	QString s_project_Name;
	QString s_project_Directory;
	QString s_project_ID;
	QString s_project_Version;
	QString s_project_Description;
	QString s_project_FilenamePrefix;
	QString s_project_SampleDescription;
	QString s_project_Barcode;
	QDate d_project_Date;
};

#endif
