// Targeter - target identification software for EUCALL workpackage 6
// Licensed under the GPL License. See LICENSE file in the project root for full license information.
// Copyright(C) 2017  David Watts 

#ifndef PAINTQLABEL_H
#define PAINTQLABEL_H

#include <QLabel>
#include "globals.h"
#include "imagesContainer.h"
#include "imageprocessing.h"

class drawingObject;

/**
* class to manage display of images in Qlabel, manages scaling, panning, drawing objects etc.
*/
class PaintQLabel : public QLabel
{
    Q_OBJECT
protected:
	ImageProcessing m_ImageProcessing;

	// state flags
	bool m_dragButtonPressed;
	bool m_bDragImage;
	bool m_bDragDrawingObject;
	bool m_mouseDown;
	bool m_bObjectClicked;

	drawingMode::drawingMode m_drawingMode;
	drawingMode::drawingMode m_clickedRegionItem;
	drawingMode::drawingMode m_hitObject;

	// mouse positions for rectangle
    QPoint m_mouseStartPos;
    QPoint m_mouseEndPos;

	// shifted object offsets
    QPoint m_imageDragOffset;
    QPoint m_drawingObjectOffset;

	// temporary drawing object
	bool m_bLoopClosed;
	QPolygon m_PolygonPoints;

	QRect m_ObjectPositionRectangle;
	QRect m_MouseRectangle;

	// image position variables
	int m_scale;

	double m_aspectRatio;

	// grid
	bool m_drawGrid;

	// colour of grid
	QColor m_annotationColour;
	drawingColour::colour m_fillColour;

	// current fiducial mark
	FIDUCIAL::position m_fidPosition;

	// grid spacing
	double gOffX;
	double gOffY;
	double gSpaceX;
	double gSpaceY;

	bool bPaddTargetImage;
	int paddlevels;
public:
// variables

// image size in image
	QRect m_imageRect;
	// image size in display
	QRect m_displayRect;


	// images 

	// pointer to image store
	int m_currentImage;
	ImagesContainer* m_pImagesContainer;

	//pointer to index into image store

	GraphicsImage m_currentDisplayImage;
/*
	int imageContainerIndex;

	// list of saved drawing objects
	QVector<drawingObject*> m_drawingObjects;
 */
// functions

	QImage getImage();
	QVector<QSharedPointer<drawingObject>> getImageDrawingObjects();

    explicit PaintQLabel(QWidget * parent = 0);
    ~PaintQLabel();

	void setImageContainerPointer(ImagesContainer* pIC);

    void displayRect(QRect r);
    void getDisplayRect();

	QSharedPointer<drawingObject> getObjectInMouseRect(drawingMode::drawingMode mode = drawingMode::any);
	void checkObjectsInMouseRect(drawingMode::drawingMode mode = drawingMode::any);
	QSharedPointer<drawingObject> getObjectAtPoint(QPoint pt, drawingMode::drawingMode mode = drawingMode::any);

	void setImageIndex(int index);
	QSize getDisplaySize() { return m_displayRect.size(); };

	void addPolygon(drawingMode::drawingMode shape = drawingMode::poly);
	void addPolygonPoint(QPoint mp);

	void addObject(drawingMode::drawingMode mode);

    void zoomToPoint(QPoint windowClick, int zoomAmount);
	void getPolygonRect(QRect* boundingPolygon);

	void addShapeMaskToImage(cv::Mat& mask, QSharedPointer<drawingShape> shape);
	cv::Mat getBinaryImageFromShapes(int imageIndex);
	cv::Mat sampleImageForTargets(cv::Mat im, int edgeThreshold, QPoint gridSpacing, QPoint gridOffset, SAMPLINGTYPE::type type);
	void drawGrid(cv::Mat& im, QPoint gridSpacing, QPoint gridOffset, cv::Scalar s = cv::Scalar(255, 255, 255), bool bPoints = true);
	void getTargetsFromBinaryImage(cv::Mat binImage, QPoint gridSpacing, QPoint gridOffset, int threshold = 10, SAMPLINGTYPE::type sampling = SAMPLINGTYPE::grid, int imageIndex = -1);

	void setTargetPosition(QPoint p, int imageIndex = -1);
    void setDrawingMode(drawingMode::drawingMode mode);
	void setFillColour(drawingColour::colour colour = drawingColour::none);

	drawingMode::drawingMode getDrawingMode() { return m_drawingMode; };
    bool checkForPolygonClose(QPoint mp);

    void startDragging(drawingMode::drawingMode mode, QPoint pos);
	void displayStatusBarPixel(QPoint p);

	void setWaveletPadd(bool padd) { bPaddTargetImage = padd; };

	static QPoint GetImagePosition(QPoint displayPt, QRect* imageRect, QRect* dispRect);
	static QPoint GetDisplayPosition(QPoint imagePt, QRect* imageRect, QRect* dispRect);

	static QRect GetDisplayRectPosition(QRect displayRect, QRect* imageRect, QRect* dispRect);
	static QRect GetImageRectPosition(QRect displayRect, QRect* imageRect, QRect* dispRect);

    void deleteSelectedDrawingObject();
	void deleteDrawingObjects(int imageIndex);

	QVector<QSharedPointer<drawingShape>> getImageShapes(bool bSetAsTarget = true, bool bTargetRegions=false, int imageIndex =-1);
    void resetDrawingObjects();
	void highLightShape(QSharedPointer<drawingObject> pObj, bool highlight = true);

	void drawTempPoly(QVector<QPoint>* pVect, QRect* pBoundingRect, QPainter* painter, drawingMode::drawingMode shape = drawingMode::poly);
	void drawTempRectCircle(QRect* pBoundingRect, QPainter* painter, bool bCircle);
	
	static void getPenBrush(QPainter* painter, bool hover = false, bool selected = false, bool bSelectRect = false, bool drawFilled = false, bool drawHighLight = false,
							drawingColour::colour col = drawingColour::none);

	QVector<QPoint> targetPoints();
signals:
    void disablePanButton();
    void setTargetArea(QSharedPointer<drawingShape> shape);
    void unsetDrawingButtons(QAction* pAct);
	void StatusBarMessage(QString msg);
	void addFiducialMark(FIDUCIAL::position pos, QPoint p);
	void moveObjective(QPoint p);
	void setSamplingDistance(QSharedPointer<QPolygon> poly);

public slots:
	void setFiducialPosition(FIDUCIAL::position position) { m_fidPosition = position; };
	void updatePaddTarget(bool padd, int levels) { bPaddTargetImage = padd; paddlevels = levels; };
	void setGrid(bool bChecked, double offX, double offY, double spaceX, double spaceY, QColor colour);
protected slots:
    virtual void enterEvent ( QEvent* event );
    virtual void leaveEvent ( QEvent* event );
    virtual void mouseMoveEvent ( QMouseEvent* event );
    virtual void mousePressEvent ( QMouseEvent* event );
    virtual void mouseReleaseEvent ( QMouseEvent* event );

    virtual void wheelEvent(QWheelEvent* event );

    virtual void paintEvent(QPaintEvent* event);

    virtual void resizeEvent(QResizeEvent* event);
};


#endif // PAINTQLABEL_H
