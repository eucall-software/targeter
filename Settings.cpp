#include <QDir>
#include "Settings.h"

Q_DECLARE_METATYPE(QIntColorMap)
Q_DECLARE_METATYPE(QIntPointMap)


SettingsValues::SettingsValues()
{
	initialize();
}

void SettingsValues::initialize()
{
	distance = 20;
	cluster = 20;
	algorithmType = algoType::COOC;
	threshold_max = 255;
	threshold_min = 0;
	ThresholdType = thresholdType::cluster2;
	autoThreshold = true;
	ScoreThreshold = 70;
	NoClustersThreshold = 2;
	huMomentSimilarity = 0;
	bCV_CALIB_CB_ADAPTIVE_THRESH = true;
	bCV_CALIB_CB_NORMALIZE_IMAGE = false;
	bCV_CALIB_CB_FILTER_QUADS = true;
	bCALIB_CB_FAST_CHECK = false;
	bCALIB_CB_CLUSTERING = false;
	FixedAspect = true;
	ZeroDistortion = true;
	FixPrincipalPointCenter = true;
	FixFocalLength = true;

	CalibrateAlgorithm = calibrateAlgoType::CHESSBOARD;
	scoreAreaFactor = 100;
	calibrateNoRows = 7;
	calibrateNoCols = 7;
	SizeOfSquare = 11;

	mosaicImageCols = 4;

	m_MinFocus=5;
	m_MaxFocus=8;
	m_CoarseFocusStep=0.1;
	m_FineFocusStep=0.02;

	displayGrid = false;
	centerGrid = false;
	gridOffsetX = 0;
	gridOffsetY = 0;
	gridSpacingX = 10;
	gridSpacingY = 10;

	micronsPerPixel = 0.5/816.0;	// measured distance / number of pixels
	imageWidth = 2046;
	imageHeight = 2046;

	m_stage_position_Z = -1;
	m_stage_position_XY_X = -1;
	m_stage_position_XY_Y = -1;
	m_image_position_XY_X = -1;
	m_image_position_XY_Y = -1;

	UseIntrinsicGuess = true;
	focalDistanceOverviewCamera = 35;
	focalDistanceMicroscopeCamera = 20;
	fiducialPos = FIDUCIAL::topleft_overview;
	bLockFiducial = true;
	samplingType = SAMPLINGTYPE::grid;
	samplingSpacing = 10;
	samplingOffset = 0;

	overviewCameraSN = 21799625;
	microscopeCameraSN = 21799596;
	AspectTolerance = 2;
	StdevLarger = 2;
	StdevSmaller = 2;

	BarcodeThreshold = 15;
	BarcodeAutoThreshold = false;

	FocusAlgorithm = FOCUSALGO::DXDY;

	objectColours.insert(0, QColor("red"));
	objectColours.insert(1, QColor("blue"));

	s_project_Username = "Prof. XYZ and Team";
	s_project_Institute = "XFEL";
	s_project_Name = "Solid Sample Experiment XYZ";
	s_project_Directory = "D:\\temp\\";
	s_project_ID = "XYZ";
	s_project_Version = "1";
	s_project_Description = "This is a experiment on material XYZ";
	s_project_FilenamePrefix = "SampleXYZ_";
	s_project_SampleDescription = "material XYZ type 1";
	s_project_Barcode = "";
	d_project_Date = QDate::currentDate();

	s_BarCodeImageRect = QRect(0, 0, 0, 0);

	for (int i = 0; i < FIDUCIAL::position::bottomright_microscope; i++)
	{
		fiducial_marks_image[i] = QPointF(-1, -1);
		fiducial_marks_stage[i] = QVector3D(-1, -1, -1);
	}

	s_CommandTextXY = "?version";
	s_CommandTextZ = "1VE";
	XPositionRelativeXY=0;
	YPositionRelativeXY=0;
	XPositionAbsoluteXY = 0;
	YPositionAbsoluteXY = 0;
	PositionRelativeZ = 0;
	PositionAbsoluteZ = 0;
	VelocityXY =10;
	BaudXY = 9600;
	
}

SettingsValues::~SettingsValues()
{
}
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
void SettingsValues::serialize(QDataStream& stream)
{
	m_settings.setValue("project_prefix", s_project_FilenamePrefix);
	m_settings.setValue("project_Barcode", s_project_Barcode);
	m_settings.setValue("cluster", cluster);
	m_settings.setValue("distance", distance);
	m_settings.setValue("NoClustersThreshold", NoClustersThreshold);
	m_settings.setValue("threshold_min", threshold_min);
	m_settings.setValue("threshold_max", threshold_max);
	m_settings.setValue("StdevSmaller", StdevSmaller);
	m_settings.setValue("StdevLarger", StdevLarger);
	m_settings.setValue("AspectTolerance", AspectTolerance);
	m_settings.setValue("scoreAreaFactor", scoreAreaFactor);
	m_settings.setValue("huMomentSimilarity", huMomentSimilarity);
	m_settings.setValue("ScoreThreshold", ScoreThreshold); 
	m_settings.setValue("autoThreshold", autoThreshold); 
	m_settings.setValue("displayGrid", displayGrid); 
	m_settings.setValue("centerGrid", centerGrid); 
	m_settings.setValue("gridOffsetX", gridOffsetX); 
	m_settings.setValue("gridOffsetY", gridOffsetY); 
	m_settings.setValue("gridSpacingX", gridSpacingX); 
	m_settings.setValue("gridSpacingY", gridSpacingY); 
	m_settings.setValue("CV_CALIB_CB_ADAPTIVE_THRESH", bCV_CALIB_CB_ADAPTIVE_THRESH); 
	m_settings.setValue("CV_CALIB_CB_NORMALIZE_IMAGE", bCV_CALIB_CB_NORMALIZE_IMAGE);
	m_settings.setValue("CV_CALIB_CB_FILTER_QUADS", bCV_CALIB_CB_FILTER_QUADS); 
	m_settings.setValue("CALIB_CB_FAST_CHECK", bCALIB_CB_FAST_CHECK); 
	m_settings.setValue("CALIB_CB_CLUSTERING", bCALIB_CB_CLUSTERING); 
	m_settings.setValue("FixedAspect", FixedAspect); 
	m_settings.setValue("ZeroDistortion", ZeroDistortion); 
	m_settings.setValue("FixPrincipalPointCenter", FixPrincipalPointCenter); 
	m_settings.setValue("activeCamera", (int)activeCamera); 
	m_settings.setValue("UseIntrinsicGuess", UseIntrinsicGuess);
	m_settings.setValue("FixFocalLength", FixFocalLength); 
	m_settings.setValue("calibrateNoRows", calibrateNoRows); 
	m_settings.setValue("calibrateNoCols", calibrateNoCols); 
	m_settings.setValue("SizeOfSquare", SizeOfSquare); 
	m_settings.setValue("ThresholdType", (int)ThresholdType); 
	m_settings.setValue("CalibrateAlgorithm", (int)CalibrateAlgorithm); 
	m_settings.setValue("algorithmType", (int)algorithmType); 
	m_settings.setValue("overviewCameraSN", overviewCameraSN); 
	m_settings.setValue("microscopeCameraSN", microscopeCameraSN);
	m_settings.setValue("micronsPerPixel", micronsPerPixel);
	m_settings.setValue("imageWidth", imageWidth);
	m_settings.setValue("imageheight", imageHeight);
	m_settings.setValue("MinFocus", m_MinFocus);
	m_settings.setValue("MaxFocus",m_MaxFocus);
	m_settings.setValue("CoarseFocusStep", m_CoarseFocusStep);
	m_settings.setValue("FineFocusStep", m_FineFocusStep);
	m_settings.setValue("FocusAlgorithm", (int)FocusAlgorithm);
	m_settings.setValue("focalDistanceOverviewCamera", focalDistanceOverviewCamera); 
	m_settings.setValue("focalDistanceMicroscopeCamera", focalDistanceMicroscopeCamera); 
	m_settings.setValue("fiducialPos", fiducialPos);
	m_settings.setValue("samplingType", samplingType); 
	m_settings.setValue("samplingSpacing", samplingSpacing);
	m_settings.setValue("samplingOffset", samplingOffset); 
	m_settings.setValue("XPositionRelativeXY", XPositionRelativeXY);
	m_settings.setValue("YPositionRelativeXY", YPositionRelativeXY); 
	m_settings.setValue("XPositionAbsoluteXY", XPositionAbsoluteXY); 
	m_settings.setValue("YPositionAbsoluteXY", YPositionAbsoluteXY); 
	m_settings.setValue("PositionRelativeZ", PositionRelativeZ);
	m_settings.setValue("PositionAbsoluteZ", PositionAbsoluteZ);
	m_settings.setValue("VelocityXY", VelocityXY); 
	m_settings.setValue("BaudXY", BaudXY); 
	m_settings.setValue("BarcodeThreshold", BarcodeThreshold); 
	m_settings.setValue("BarcodeAutoThreshold", BarcodeAutoThreshold);
	m_settings.setValue("BarCodeImageRect", s_BarCodeImageRect);
	m_settings.setValue("LockFiducial", bLockFiducial);

	m_settings.beginGroup("objectColours");
	QIntColorMap::const_iterator ic = objectColours.constBegin();
	while (ic != objectColours.constEnd()) {
		m_settings.setValue(QString::number(ic.key()), ic.value().name());
		++ic;
	}
	m_settings.endGroup();

	// write fiducials
	m_settings.setValue("overview_stage_position", overviewStagePosition);

	QIntPointMap::const_iterator ifm = fiducial_marks_image.constBegin();

	QString s("fiducials");

	while (ifm != fiducial_marks_image.constEnd()) 
	{
		QString s2 = FIDUCIAL_POSITION_STRINGS(ifm.key());
		m_settings.setValue(s2 + "_imageXY", ifm.value());
		++ifm;
	}

	QInt3DMap::const_iterator ifm3 = fiducial_marks_stage.constBegin();

	while (ifm3 != fiducial_marks_stage.constEnd()) 
	{
		QString s2 = FIDUCIAL_POSITION_STRINGS(ifm3.key());
		m_settings.setValue(s2 + "_stageX", ifm3.value().x());
		m_settings.setValue(s2 + "_stageY", ifm3.value().y());
		m_settings.setValue(s2 + "_stageZ", ifm3.value().z());
		++ifm3;
	}

	// save project settings to xml
	//saveProjectInfo();
}
/*
stream.setVersion(QDataStream::Qt_4_5);

stream << cluster << distance << NoClustersThreshold << threshold_min << threshold_max	<< StdevSmaller	<< StdevLarger	<< AspectTolerance	<< scoreAreaFactor	<< huMomentSimilarity
<< ScoreThreshold << autoThreshold	<< displayGrid	<< centerGrid << gridOffsetX << gridOffsetY	<< gridSpacingX	<< gridSpacingY	<< bCV_CALIB_CB_ADAPTIVE_THRESH	<< bCV_CALIB_CB_NORMALIZE_IMAGE
<< bCV_CALIB_CB_FILTER_QUADS << bCALIB_CB_FAST_CHECK << bCALIB_CB_CLUSTERING << FixedAspect << ZeroDistortion << FixPrincipalPointCenter << (int)activeCamera << UseIntrinsicGuess
<< FixFocalLength << calibrateNoRows << calibrateNoCols << SizeOfSquare << (int)ThresholdType << (int)CalibrateAlgorithm << (int)algorithmType << overviewCameraSN << microscopeCameraSN
<< pixelSizeCCD << focalDistanceOverviewCamera << focalDistanceMicroscopeCamera << objectColours << s_project_Name << s_project_Institute << s_project_Name << s_project_ID << s_project_Version
<< s_project_Description << s_project_FilenamePrefix << s_project_SampleDescription << s_project_Barcode << s_project_Directory << d_project_Date << fiducialPos << samplingType << samplingSpacing
<< samplingOffset << XPositionRelativeXY << YPositionRelativeXY << XPositionAbsoluteXY << YPositionAbsoluteXY << VelocityXY << BaudXY << BarcodeThreshold << BarcodeAutoThreshold << s_BarCodeImageRect
<< fiducial_marks;
*/



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
void SettingsValues::deserialize(QDataStream& stream)
{
	s_project_FilenamePrefix = m_settings.value("project_prefix").toString();
	s_project_Barcode = m_settings.value("project_Barcode").toString();
	cluster = m_settings.value("cluster").toInt();
	distance = m_settings.value("distance").toInt();
	NoClustersThreshold = m_settings.value("NoClustersThreshold").toInt();
	threshold_min = m_settings.value("threshold_min").toInt();
	threshold_max = m_settings.value("threshold_max").toInt();
	StdevSmaller = m_settings.value("StdevSmaller").toDouble();
	StdevLarger = m_settings.value("StdevLarger").toDouble();
	AspectTolerance = m_settings.value("AspectTolerance").toDouble();
	scoreAreaFactor = m_settings.value("scoreAreaFactor").toInt();
	huMomentSimilarity = m_settings.value("huMomentSimilarity").toInt();
	ScoreThreshold = m_settings.value("ScoreThreshold").toInt();
	autoThreshold = m_settings.value("autoThreshold").toBool();
	displayGrid = m_settings.value("displayGrid").toBool();
	centerGrid = m_settings.value("centerGrid").toBool();
	gridOffsetX = m_settings.value("gridOffsetX").toDouble();
	gridOffsetY = m_settings.value("gridOffsetY").toDouble();
	gridSpacingX = m_settings.value("gridSpacingX").toDouble();
	gridSpacingY = m_settings.value("gridSpacingY").toDouble();
	bCV_CALIB_CB_ADAPTIVE_THRESH = m_settings.value("CV_CALIB_CB_ADAPTIVE_THRESH").toBool();
	bCV_CALIB_CB_NORMALIZE_IMAGE = m_settings.value("CV_CALIB_CB_NORMALIZE_IMAGE").toBool();
	bCV_CALIB_CB_FILTER_QUADS = m_settings.value("CV_CALIB_CB_FILTER_QUADS").toBool();
	bCALIB_CB_FAST_CHECK = m_settings.value("CALIB_CB_FAST_CHECK").toBool();
	bCALIB_CB_CLUSTERING = m_settings.value("CALIB_CB_CLUSTERING").toBool();
	FixedAspect = m_settings.value("FixedAspect").toBool();
	ZeroDistortion = m_settings.value("ZeroDistortion").toBool();
	FixPrincipalPointCenter = m_settings.value("FixPrincipalPointCenter").toBool();
	activeCamera = (cameraType::camera)m_settings.value("activeCamera").toInt();
	UseIntrinsicGuess = m_settings.value("UseIntrinsicGuess").toBool();
	FixFocalLength = m_settings.value("FixFocalLength").toBool();
	calibrateNoRows = m_settings.value("calibrateNoRows").toInt();
	calibrateNoCols = m_settings.value("calibrateNoCols").toInt();
	SizeOfSquare = m_settings.value("SizeOfSquare").toInt();
	ThresholdType = (thresholdType::thresholdType) m_settings.value("ThresholdType").toInt();
	CalibrateAlgorithm = (calibrateAlgoType::algoType) m_settings.value("CalibrateAlgorithm").toInt();
	algorithmType = (algoType::algoType) m_settings.value("algorithmType").toInt();
	overviewCameraSN = m_settings.value("overviewCameraSN").toInt();
	microscopeCameraSN = m_settings.value("microscopeCameraSN").toInt();
	imageWidth = m_settings.value("imageWidth").toInt();
	imageHeight = m_settings.value("imageHeight").toInt();
	m_MinFocus = m_settings.value("MinFocus").toDouble();
	m_MaxFocus = m_settings.value("MaxFocus").toDouble();
	m_CoarseFocusStep = m_settings.value("CoarseFocusStep").toDouble();
	m_FineFocusStep = m_settings.value("FineFocusStep").toDouble();
	FocusAlgorithm = (FOCUSALGO::algo)m_settings.value("FocusAlgorithm").toInt();
	micronsPerPixel = m_settings.value("micronsPerPixel").toDouble();
	focalDistanceOverviewCamera = m_settings.value("focalDistanceOverviewCamera").toInt();
	focalDistanceMicroscopeCamera = m_settings.value("focalDistanceMicroscopeCamera").toInt();
	fiducialPos = (FIDUCIAL::position)m_settings.value("fiducialPos").toInt();
	samplingType = (SAMPLINGTYPE::type)m_settings.value("samplingType").toInt();
	samplingSpacing = m_settings.value("samplingSpacing").toInt();
	samplingOffset = m_settings.value("samplingOffset").toInt();
	XPositionRelativeXY = m_settings.value("XPositionRelativeXY").toDouble();
	YPositionRelativeXY = m_settings.value("YPositionRelativeXY").toDouble();
	XPositionAbsoluteXY = m_settings.value("XPositionAbsoluteXY").toDouble();
	YPositionAbsoluteXY = m_settings.value("YPositionAbsoluteXY").toDouble();
	PositionRelativeZ = m_settings.value("PositionRelativeZ").toDouble();
	PositionAbsoluteZ = m_settings.value("PositionAbsoluteZ").toDouble();
	VelocityXY = m_settings.value("VelocityXY").toDouble();
	BaudXY = m_settings.value("BaudXY").toInt();
	BarcodeThreshold = m_settings.value("BarcodeThreshold").toInt();
	BarcodeAutoThreshold = m_settings.value("BarcodeAutoThreshold").toBool();
	s_BarCodeImageRect = m_settings.value("BarCodeImageRect").toRect();
	bLockFiducial = m_settings.value("LockFiducial").toBool();

	m_settings.beginGroup("objectColours");
	QStringList keysC = m_settings.childKeys();
	foreach(QString key, keysC) {
		QColor c;
		c.setNamedColor(m_settings.value(key).toString());
		objectColours[atoi(key.toLocal8Bit().data())] = c;
	}
	m_settings.endGroup();

	// write fiducials

	overviewStagePosition = m_settings.value("overview_stage_position").toPointF();   

	QString s("fiducials");

	float x, y, z;

	for (int i = 0; i <= FIDUCIAL::position::bottomright_microscope; i++)
	{
		QString s2 = FIDUCIAL_POSITION_STRINGS(i);

		fiducial_marks_image[i] = m_settings.value(s2 + "_imageXY").toPointF();

		fiducial_marks_stage[i] = QVector3D(m_settings.value(s2 + "_stageX").toFloat(), 
			m_settings.value(s2 + "_stageY").toFloat(),
			m_settings.value(s2 + "_stageZ").toFloat());
	}
}

/*
//QDataStream stream(byteArray);
stream.setVersion(QDataStream::Qt_4_5);

int _algorithmType, _CalibrateAlgorithm, _ThresholdType, _activeCamera, fidpos, _samplingtype;

stream >> cluster >> distance >> NoClustersThreshold >> threshold_min >> threshold_max >> StdevSmaller >> StdevLarger >> AspectTolerance >> scoreAreaFactor	>> huMomentSimilarity
>> ScoreThreshold >> autoThreshold >> displayGrid >> centerGrid >> gridOffsetX >> gridOffsetY >> gridSpacingX >> gridSpacingY >> bCV_CALIB_CB_ADAPTIVE_THRESH >> bCV_CALIB_CB_NORMALIZE_IMAGE
>> bCV_CALIB_CB_FILTER_QUADS >> bCALIB_CB_FAST_CHECK >> bCALIB_CB_CLUSTERING >> FixedAspect >> ZeroDistortion >> FixPrincipalPointCenter >> _activeCamera >> UseIntrinsicGuess
>> FixFocalLength >> calibrateNoRows >> calibrateNoCols	>> SizeOfSquare	>> _ThresholdType >> _CalibrateAlgorithm >> _algorithmType >> overviewCameraSN	>> microscopeCameraSN
>> pixelSizeCCD >> focalDistanceOverviewCamera >> focalDistanceMicroscopeCamera >> objectColours >> s_project_Name >> s_project_Institute >> s_project_Name >> s_project_ID >>
s_project_Version >> s_project_Description >> s_project_FilenamePrefix >> s_project_SampleDescription >> s_project_Barcode >> s_project_Directory >> d_project_Date >> fidpos >>
_samplingtype >> samplingSpacing >> samplingOffset >> XPositionRelativeXY >> YPositionRelativeXY >> XPositionAbsoluteXY >> YPositionAbsoluteXY >> VelocityXY >> BaudXY >>
BarcodeThreshold >> BarcodeAutoThreshold >> s_BarCodeImageRect >> fiducial_marks;

//calibrationDataOverview.deserialise(stream);
//calibrationDataMicroscope.deserialise(stream);

activeCamera = (cameraType::camera)_activeCamera;
algorithmType = (algoType::algoType)_algorithmType;
CalibrateAlgorithm = (calibrateAlgoType::algoType)_CalibrateAlgorithm;
ThresholdType = (thresholdType::thresholdType)_ThresholdType;
fiducialPos = (FIDUCIAL::position)fidpos;
samplingType = (SAMPLINGTYPE::type)_samplingtype;
*/

QString SettingsValues::appendNumber(QString name, long& count)
{
	QString s(QString::number(count).rightJustified(5, '0'));
	s += "_" + name;

	count--;

	return s;
}

QMap<QString, QVariant> SettingsValues::getProjectInfoMap()
{
	long count = 99999;

	QMap<QString, QVariant> map;

	map[appendNumber("project_UserName", count)] = s_project_Username;
	map[appendNumber("project_Name", count)] = s_project_Name;
	map[appendNumber("project_Institute", count)] = s_project_Institute;
	map[appendNumber("project_ID", count)] = s_project_ID;
	map[appendNumber("project_Version", count)] = s_project_Version;
	map[appendNumber("project_Description", count)] = s_project_Description;
	map[appendNumber("project_FilenamePrefix", count)] = s_project_FilenamePrefix;
	map[appendNumber("project_SampleDescription", count)] = s_project_SampleDescription;
	map[appendNumber("project_Barcode", count)] = s_project_Barcode;
	map[appendNumber("project_Directory", count)] = s_project_Directory;
	map[appendNumber("project_Date", count)]= d_project_Date;

/*
	map[appendNumber("overview_stage_position/x", count)] = overviewStagePosition.x();
	map[appendNumber("overview_stage_position/y", count)] = overviewStagePosition.y();

	QIntPointMap::const_iterator ifm = fiducial_marks_image.constBegin();

	QString s("fiducials");

	while (ifm != fiducial_marks_image.constEnd()) {
		QString s2 = FIDUCIAL_POSITION_STRINGS(ifm.key());

		map[appendNumber(s, count) + "/" + s2.replace(" ", "_") + "/image/" + "X"] = ifm.value().x();
		map[appendNumber(s, count) + "/" + s2.replace(" ", "_") + "/image/" + "Y"] = ifm.value().y();
		++ifm;
	}

	QInt3DMap::const_iterator ifm3 = fiducial_marks_stage.constBegin();

	while (ifm3 != fiducial_marks_stage.constEnd()) {
		QString s2 = FIDUCIAL_POSITION_STRINGS(ifm3.key());

		map[appendNumber(s, count) + "/" + s2.replace(" ", "_") + "/stage/" + "X"] = ifm3.value().x();
		map[appendNumber(s, count) + "/" + s2.replace(" ", "_") + "/stage/" + "Y"] = ifm3.value().y();
		map[appendNumber(s, count) + "/" + s2.replace(" ", "_") + "/stage/" + "Z"] = ifm3.value().z();
		++ifm3;
	}
*/

	return map;
}

void SettingsValues::setProjectInfoMap(QMap<QString, QVariant>& map)
{
	s_project_Username = map["project_UserName"].toString();
	s_project_Name = map["project_Name"].toString();
	s_project_Institute = map["project_Institute"].toString();
	s_project_ID = map["project_ID"].toString();
	s_project_Version = map["project_Version"].toString();
	s_project_Description = map["project_Description"].toString();
	s_project_FilenamePrefix = map["project_FilenamePrefix"].toString();
	s_project_SampleDescription = map["project_SampleDescription"].toString();
	s_project_Barcode = map["project_Barcode"].toString();
	s_project_Directory = map["project_Directory"].toString();
	d_project_Date = map["project_Date"].toDate();

/*
	overviewStagePosition = QPoint(map["overview_stage_position/x"].toFloat(), map["overview_stage_position/y"].toFloat());

	QString s("fiducials");

	float x, y, z;

	for (int i = 0; i <= FIDUCIAL::position::bottomright_microscope; i++)
	{
		QString s2 = FIDUCIAL_POSITION_STRINGS(i);

		x = map[s + "/" + s2.replace(" ", "_") + "/image/" + "X"].toFloat();
		y = map[s + "/" + s2.replace(" ", "_") + "/image/" + "Y"].toFloat();

		fiducial_marks_image[i] = QPointF(x, y);

		x = map[s + "/" + s2.replace(" ", "_") + "/stage/" + "X"].toFloat();
		y = map[s + "/" + s2.replace(" ", "_") + "/stage/" + "Y"].toFloat();
		z = map[s + "/" + s2.replace(" ", "_") + "/stage/" + "Z"].toFloat();

		fiducial_marks_stage[i] = QVector3D(x, y, z);
	}
*/
}

/*

// serialise
void SettingsValues::saveProjectInfo()
{
	// project settings
	m_settings.setValue("project_Name", s_project_Name);
	m_settings.setValue("project_Institute", s_project_Institute);
	m_settings.setValue("project_ID", s_project_ID);
	m_settings.setValue("project_Version", s_project_Version);
	m_settings.setValue("project_Description", s_project_Description);
	m_settings.setValue("project_FilenamePrefix", s_project_FilenamePrefix);
	m_settings.setValue("project_SampleDescription", s_project_SampleDescription);
	m_settings.setValue("project_Barcode", s_project_Barcode);
	m_settings.setValue("project_Directory", s_project_Directory);
	m_settings.setValue("project_Date", d_project_Date);

	m_settings.beginGroup("fiducial_marks");
	QIntPointMap::const_iterator ifm = fiducial_marks.constBegin();

	while (ifm != fiducial_marks.constEnd()) {
		QString s = FIDUCIAL_POSITION_STRINGS(ifm.key());
		m_settings.setValue(s.replace(" ", "_"), ifm.value());
		++ifm;
	}
	m_settings.endGroup();
}
*/

int getFIDUCIAL_POSITION_NUMBER(QString str) {
	return (str == "top_left_overview_camera"? FIDUCIAL::position::topleft_overview : \
		(str == "top right overview camera"? FIDUCIAL::position::topright_overview : \
		(str == "bottom left overview camera"? FIDUCIAL::position::bottomleft_overview : \
			(str == "bottom right overview camera"? FIDUCIAL::position::bottomright_overview : \
			(str == "top left microscope camera"? FIDUCIAL::position::topleft_microscope : \
				(str == "top right microscope camera"? FIDUCIAL::position::topright_microscope : \
				(str == "bottom left microscope camera"? FIDUCIAL::position::bottomleft_microscope : \
					(str == "bottom right microscope camera"? FIDUCIAL::position::bottomright_microscope : \
								0))))))));
}

/*
void SettingsValues::readProjectInfo()
{
	// project settings
	s_project_Name = m_settings.value("project_Name").toString();
	s_project_Institute = m_settings.value("project_Institute").toString();
	s_project_ID = m_settings.value("project_ID").toString();
	s_project_Version = m_settings.value("project_Version").toString();
	s_project_Description = m_settings.value("project_Description").toString();
	s_project_FilenamePrefix = m_settings.value("project_FilenamePrefix").toString();
	s_project_SampleDescription = m_settings.value("project_SampleDescription").toString();
	s_project_Barcode = m_settings.value("project_Barcode").toString();
	s_project_Directory = m_settings.value("project_Directory").toString();
	d_project_Date = m_settings.value("project_Date").toDate();

	m_settings.beginGroup("fiducial_marks");
	QStringList keysF = m_settings.childKeys();
	foreach(QString key, keysF) {
		QString s = key.replace("_", " ");
		int i = (int)getFIDUCIAL_POSITION_NUMBER(s);
		fiducial_marks[i] = m_settings.value(key).toVector3D();
	}
	m_settings.endGroup();
}
*/