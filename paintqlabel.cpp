// Targeter - target identification software for EUCALL workpackage 6
// Licensed under the GPL License. See LICENSE file in the project root for full license information.
// Copyright(C) 2017  David Watts 

#include <QWheelEvent>
#include <QPainter>
#include <QImage>
#include <QDebug>
#include <iostream>
#include "paintqlabel.h"
#include "globals.h"
#include "BaslerCamera.h"
#include "MainWindow.h"
#include "drawingObjects.h"

using namespace std;

#define _COLOUR_HOVER "#0FF"
#define _COLOUR_SELECT_HOVER "#F0F"
#define _COLOUR_SELECT "#00F"
#define _COLOUR_NORMAL "#0F0"
#define _COLOUR_SELECT_BOUNDING_BOX "#FF0"

#define _CROSS_SIZE 7

/**
*
*  class constructor
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   PaintQLabel::PaintQLabel
* Qualifier  : QLabel(parent)
* @param     QWidget * parent 
* @return    
* Access     public 
*/
PaintQLabel::PaintQLabel(QWidget * parent) : QLabel(parent)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
	m_pImagesContainer = NULL;
	imageContainerIndex = 0;

    resetDrawingObjects();
    setMouseTracking(true);
}

/**
*
*  Resets drawing objects
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   PaintQLabel::resetDrawingObjects
* Qualifier 
* @return    void
* Access     public 
*/
void PaintQLabel::resetDrawingObjects()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

    m_scale = 0;
    m_dragButtonPressed = false;
    m_mouseDown = false;
    m_bDragImage = false;
	m_drawGrid = false;

	m_bDragDrawingObject = false;
	m_bObjectClicked = false;
	m_annotationColour = QColor("red");
	m_fillColour = drawingColour::none;

    m_drawingMode = drawingMode::none;
    m_clickedRegionItem = drawingMode::none;
    m_hitObject = drawingMode::none;

    m_mouseStartPos = QPoint(-1,-1);
    m_mouseEndPos = QPoint(-1,-1);

    m_ObjectPositionRectangle = QRect(-1,-1,0,0);
	m_MouseRectangle =  QRect(-1,-1, 0, 0);

	m_fidPosition = FIDUCIAL::position::topleft_overview;

    emit unsetDrawingButtons(NULL);
}

/**
*
*  class destructor
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   PaintQLabel::~PaintQLabel
* Qualifier 
* @return    
* Access     public 
*/
PaintQLabel::~PaintQLabel()
{
	foreach(QObject* pObj, m_drawingObjects)
	{
		if (pObj)
			delete pObj;
	}
}

void PaintQLabel::setImageContainerPointer(ImagesContainer* pIC)
{
	m_pImagesContainer = pIC;
}

void PaintQLabel::enterEvent ( QEvent * event )
{

}

void PaintQLabel::leaveEvent ( QEvent * event )
{

}

/**
*
*  sets drawing mode for panning/zooming
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   PaintQLabel::setDrawingMode
* Qualifier 
* @param     drawingMode mode 
* @return    void
* Access     public 
*/
void PaintQLabel::setDrawingMode(drawingMode::drawingMode mode)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
    m_drawingMode = mode;
	
	m_ObjectPositionRectangle = QRect(-1, -1, 0, 0);

	m_mouseStartPos = QPoint(-1, -1);
	m_mouseEndPos = QPoint(-1, -1);

	m_MouseRectangle = QRect(-1, -1, 0, 0);

	this->repaint();
}

void PaintQLabel::setGrid(bool bChecked, double offX, double offY, double spaceX, double spaceY, QColor colour)
{
	m_drawGrid = bChecked;

	gOffX = offX;
	gOffY = offY;
	gSpaceX = spaceX;
	gSpaceY = spaceY;
	m_annotationColour = colour;

	this->repaint();
}

void PaintQLabel::addPolygon()
{
	drawingPoly* dObj = new drawingPoly(this);

	dObj->m_pPoly = new QPolygon;

	QPoint poly1 = GetImagePosition(m_PolygonPoints[0], &m_imageRect, &m_displayRect);

	int minx = poly1.x();
	int maxx = minx;
	int miny = poly1.y();
	int maxy = miny;

	for (int i = 0; i < m_PolygonPoints.length(); i++)
	{
		// coordinates relative to image
		QPoint pt = GetImagePosition(m_PolygonPoints[i], &m_imageRect, &m_displayRect);

		dObj->m_pPoly->append(pt);

		minx = std::min(pt.x(), minx);
		miny = std::min(pt.y(), miny);
		maxx = std::max(pt.x(), maxx);
		maxy = std::max(pt.y(), maxy);
	}

	dObj->m_pRect = new QRect(minx, miny, maxx-minx, maxy-miny);
	dObj->m_type = drawingMode::poly;
	dObj->m_fillColour = m_fillColour;

	dObj->m_ImageIndex = imageContainerIndex;

	m_drawingObjects.append(dObj);
}

/**
*
* checks to see if point is in a closed polygon remove point if not
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   PaintQLabel::checkForPolygonClose
* Qualifier 
* @param     QPoint mp 
* @return    bool
* Access     public 
*/
bool PaintQLabel::checkForPolygonClose(QPoint mp)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
	if (m_PolygonPoints.length() > 2)
	{
		for (int i = 0; i < m_PolygonPoints.length(); i++)
		{
			QPoint point = mp - m_PolygonPoints[i];

			if (point.manhattanLength() < 5)
			{
				return true;
			}
		}
	}

    return false;
}



/**
*
*  initialises panning parameters
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   PaintQLabel::startDragging
* Qualifier 
* @param     drawingMode mode 
* @param     QPoint pos 
* @return    void
* Access     public 
*/
void PaintQLabel::startDragging(drawingMode::drawingMode mode, QPoint pos)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
    m_clickedRegionItem = mode;

    m_mouseStartPos = pos;
    m_mouseEndPos = pos;

	// update panning mode
    if(mode == drawingMode::shift)
    {
        this->repaint();

        m_bDragImage = m_dragButtonPressed;
    }
    else
    {
        m_bDragImage = m_dragButtonPressed;

        this->repaint();
    }
}

QRect PaintQLabel::GetDisplayRectPosition(QRect displayRect, QRect* imageRect, QRect* dispRect)
{
	double scaleW = ((double)dispRect->width()) / ((double)imageRect->width());
	double scaleH = ((double)dispRect->height()) / ((double)imageRect->height());

	// get image pixel position
	double ix = displayRect.left();
	double iy = displayRect.top();

	// offset to image
	ix -= imageRect->x();
	iy -= imageRect->y();

	// scale image to display coordinates
	ix *= scaleW;
	iy *= scaleH;

	// offset to display
	ix += dispRect->x();
	iy += dispRect->y();

	int newW = displayRect.width() * scaleW;
	int newH = displayRect.height() * scaleH;

	QRect newRect(QPoint(ceil(ix), ceil(iy)), QSize(newW, newH));

	//if (dispRect->contains(ix, iy))
		return newRect;

	//return displayRect;
}

QRect PaintQLabel::GetImageRectPosition(QRect displayRect, QRect* imageRect, QRect* dispRect)
{
	double scaleW = ((double)imageRect->width()) / ((double)dispRect->width());
	double scaleH = ((double)imageRect->height()) / ((double)dispRect->height());

	double dOffX = displayRect.left() - dispRect->left();
	double dOffY = displayRect.top() - dispRect->top();

	int newW = displayRect.width() * scaleW;
	int newH = displayRect.height() * scaleH;

	return QRect(QPoint((dOffX*scaleW + imageRect->left()), (dOffY*scaleH + imageRect->top())), QSize(newW, newH));
}

QPoint PaintQLabel::GetDisplayPosition(QPoint imagePt, QRect* imageRect, QRect* dispRect)
{
	double scaleW = ((double)dispRect->width()) / ((double)imageRect->width());
	double scaleH = ((double)dispRect->height()) / ((double)imageRect->height());

	// get image pixel position
	double ix = imagePt.x();
	double iy = imagePt.y();

	// offset to image
	ix -= imageRect->x();
	iy -= imageRect->y();

	// scale image to display coordinates
	ix *= scaleW;
	iy *= scaleH;

	// offset to display
	ix += dispRect->x();
	iy += dispRect->y();

	//if (dispRect->contains(ix, iy))
	
	return QPoint(ceil(ix), ceil(iy));

	//return QPoint(-1, -1);
}

QPoint PaintQLabel::GetImagePosition(QPoint displayPt, QRect* imageRect, QRect* dispRect)
{
	double scaleW = ((double)imageRect->width()) / ((double)dispRect->width());
	double scaleH = ((double)imageRect->height()) / ((double)dispRect->height());

	double dOffX = displayPt.x() - dispRect->left();
	double dOffY = displayPt.y() - dispRect->top();

	//if (dOffX >= 0 && dOffY >= 0 && dOffX < dispRect->width() && dOffY < dispRect->height())
		return QPoint((dOffX*scaleW + imageRect->left()), (dOffY*scaleH + imageRect->top()));

	//return QPoint(-1,-1);
}

void PaintQLabel::displayStatusBarPixel(QPoint p)
{
	QPoint imPos = GetImagePosition(p, &m_imageRect, &m_displayRect);

	if (imPos.x() >= 0 && imPos.x() >= 0)
	{
		QColor clrCurrent(getImage().pixel(imPos.x(), imPos.y()));

		QString s = "XY: " + QString::number(imPos.x()) + ", " + QString::number(imPos.y()) +
			" RGBA: " + QString::number(clrCurrent.red()) +
			" , " + QString::number(clrCurrent.green()) +
			" , " + QString::number(clrCurrent.blue()) +
			" , " + QString::number(clrCurrent.alpha());

		// add to status bar
		emit StatusBarMessage(s);
	}
	else
		emit StatusBarMessage("");
}

void PaintQLabel::addPolygonPoint(QPoint mp)
{
	// if polygon is closed then polygon added to m_drawingObjects in this function
	// point should be added to polygon at this point
	bool bLoopClosed = checkForPolygonClose(mp);

	// add point to polygon either as another polygon point or in a new polygon
	m_PolygonPoints.push_front(mp);

	// if loop closed then add polygon to list, do bounding rect and clear temp polygon vector
	if (bLoopClosed)
	{
		addPolygon();

		// if clicked point hits another polygon point then close polygon
		m_PolygonPoints.clear();

		m_bLoopClosed = true;
	}
	else
		m_bLoopClosed = false;
}

/**
*
*  mouse down event, start drawing/panning etc
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   PaintQLabel::mousePressEvent
* Qualifier 
* @param     QMouseEvent * event 
* @return    void
* Access     virtual protected 
*/
void PaintQLabel::mousePressEvent ( QMouseEvent * event )
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
    m_mouseDown = true;

	// check if click in image or on object /////////////////////////////////////////////////////////////////
	// draw 1st polygon point //////////////////////////////////////////////////////////////////////////////
    if ( !getImage().isNull())
    {	
		const QPoint mp = event->pos();

		// record mouse position ///////////////////////////////////////////////////////////////////////////////
		m_mouseStartPos = mp;
		m_mouseEndPos = mp;

		m_MouseRectangle.setTopLeft(mp);

		m_drawingObjectOffset = QPoint(0, 0);

		// if object clicked in, then that object is selected and can be shifted -> object in shift/selected mode
		m_bObjectClicked = false;
		int hitObject = -1;
		for (int i = 0; i < m_drawingObjects.length(); i++)
		{
			bool bHit = m_drawingObjects[i]->m_bHoveredOver;

			if (bHit)
			{
				if (m_drawingMode == drawingMode::shift)
					m_drawingObjects[i]->m_bDragging = true;
				else
					m_drawingObjects[i]->m_bSelected = !m_drawingObjects[i]->m_bSelected;	// toogle state

				m_drawingObjectOffset = mp - GetDisplayPosition(m_drawingObjects[i]->m_pRect->topLeft(), &m_imageRect, &m_displayRect);

				hitObject = i;
			}
			else
			{
				m_drawingObjects[i]->m_bDragging = false;
			}

			m_bObjectClicked |= bHit;
		}

		// put object to back of queue
		if(hitObject>=0)
		{
			// get hit object
			m_drawingObjects.push_back((drawingObject*)m_drawingObjects.takeAt(hitObject));
		}

		// add polygon point
		if (m_drawingMode == drawingMode::poly)
		{
			addPolygonPoint(mp);

			this->repaint();
		}
		else if (m_drawingMode == drawingMode::shift)
		{
			if (!m_bObjectClicked)
			{
				m_bDragImage = true;
				m_bDragDrawingObject = false;
			}
			else
			{
				m_bDragImage = false;
				m_bDragDrawingObject = true;
			}
		}
		
		// drag image
		this->repaint();
        event->accept();
    }
}

/**
*
*  mouse move event, updates drawing of objects / panning of image
*
* @author    David Watts
* @since     2017/03/07
*
* FullName   PaintQLabel::mouseMoveEvent
* Qualifier
* @param     QMouseEvent * event
* @return    void
* Access     virtual protected
*/
void PaintQLabel::mouseMoveEvent(QMouseEvent * event)
{
#ifdef DEBUGPRINT
#ifdef ONMOUSEPAINTDEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
#endif
	QPoint p = event->pos();

	if (!getImage().isNull())
	{
		// if we have an image then show the pixel value at the mouse position /////////////////////////////////////////
		displayStatusBarPixel(p);

		// if object hovered over (or not) then toggle hover over setting //////////////////////////////////////////
		for (int i = 0; i < m_drawingObjects.length(); i++)
			m_drawingObjects[i]->hitTest(p, m_mouseDown);

		// if image in shift mode then shift image /////////////////////////////////////////////////////////////////
		if (m_mouseDown)
		{
			m_mouseEndPos = p;
			
			// drag image
			if (m_bDragImage)
			{
				double scaleW = ((double)m_imageRect.width()) / ((double)m_displayRect.width());
				double scaleH = ((double)m_imageRect.height()) / ((double)m_displayRect.height());

				// need to scale translated Rect to image dimensions
				QPoint distance = (m_mouseStartPos - m_mouseEndPos);

				QPoint scaledDistance = QPoint(distance.x()*scaleW, distance.y()*scaleH);

				m_imageDragOffset = scaledDistance;
			}
			else if(m_bDragDrawingObject)
			{
				for (int i = 0; i < m_drawingObjects.length(); i++)
				{
					if (m_drawingObjects[i]->m_bDragging)
						m_drawingObjects[i]->moveObject(p - m_drawingObjectOffset);
				}
			}
			else if(!m_bObjectClicked)// if object in draw mode then resize object ///////////////////////////////////////////////////////////////////
			{
				// if the background has been clicked
				m_ObjectPositionRectangle = QRect(m_mouseStartPos, m_mouseEndPos);
			}
		}
	}

	// redraw
	this->repaint();
	event->accept();
}

void PaintQLabel::addObject(drawingMode::drawingMode mode)
{
	m_ObjectPositionRectangle = m_MouseRectangle;
	drawingObject* dObj = NULL;

	if (mode == drawingMode::fiducial)
		dObj = new drawingFiducial(this);
	else if (mode == drawingMode::cross)
		dObj = new drawingCross(this);
	else if (mode == drawingMode::circle)
		dObj = new drawingEllipse(this);
	else if (mode == drawingMode::rect)
		dObj = new drawingRect(this);
	else if (mode == drawingMode::poly)
		dObj = new drawingPoly(this);
	else if (mode == drawingMode::centerObjective)
		dObj = new drawingMoveObjective(this);

	dObj->m_fillColour = m_fillColour;
	dObj->m_ImageIndex = imageContainerIndex;

	if(dObj != NULL)
	{
		dObj->m_type = mode;

		QPoint ptEnd = GetImagePosition(m_mouseEndPos, &m_imageRect, &m_displayRect);
		QPoint ptStart = GetImagePosition(m_mouseStartPos, &m_imageRect, &m_displayRect);

		if (mode == drawingMode::fiducial || m_drawingMode == drawingMode::cross)
		{
			if (mode == drawingMode::fiducial)
			{
				// check all other fiducials to see if it already exists if so remove 
				for(int i=0;i<m_drawingObjects.size();i++)
				{
					drawingObject* pObj = m_drawingObjects[i];

					if(pObj->m_ImageIndex == imageContainerIndex && pObj->m_type == drawingMode::fiducial)
					{
						drawingFiducial* pFid = (drawingFiducial*)pObj;

						if(pFid->getPosition() == m_fidPosition)
						{
							delete pFid;
							m_drawingObjects.remove(i);
						}
					}
				}

				((drawingFiducial*)dObj)->setPosition(m_fidPosition);

				emit addFiducialMark(((drawingFiducial*)dObj)->getPosition(), ptEnd);
			}
			dObj->m_pRect = new QRect(ptEnd, ptEnd);
		}
		else if(mode == drawingMode::centerObjective)
		{
			emit moveObjective(ptEnd);
			dObj->m_pRect = new QRect(ptEnd, ptEnd);
		}
		else
		{
			if(ptEnd.x() < ptStart.x() || ptEnd.y() < ptStart.y())
				dObj->m_pRect = new QRect(ptEnd, ptStart);
			else
				dObj->m_pRect = new QRect(ptStart, ptEnd);
		}

		// add to drawing objects list
		m_drawingObjects.append(dObj);
	}
}

/**
*
*  mouse up event, stop drawing/panning etc
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   PaintQLabel::mouseReleaseEvent
* Qualifier 
* @param     QMouseEvent * event 
* @return    void
* Access     virtual protected 
*/
void PaintQLabel::mouseReleaseEvent(QMouseEvent * event)
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
	QPoint pt = event->pos();

	m_mouseEndPos = pt;

	if (m_mouseEndPos.x() >= m_mouseStartPos.x() || m_mouseEndPos.y() >= m_mouseStartPos.y())
		m_MouseRectangle = QRect(m_mouseStartPos, m_mouseEndPos);
	else
		m_MouseRectangle = QRect(m_mouseEndPos, m_mouseStartPos);

	// if dragging then finish object move
	if (m_bDragImage)
	{
		QPoint distance = (m_mouseStartPos - m_mouseEndPos);

		double scaleW = ((double)m_imageRect.width()) / ((double)m_displayRect.width());
		double scaleH = ((double)m_imageRect.height()) / ((double)m_displayRect.height());

		QPoint scaledDistance = QPoint(distance.x()*scaleW, distance.y()*scaleH);

		m_imageRect.translate(scaledDistance);
	}
	else if(m_bDragDrawingObject)
	{
		if (m_drawingMode == drawingMode::shift)
		{
			drawingObject* pObj = getObjectAtPoint(pt, drawingMode::fiducial);

			if (pObj != NULL)
				emit addFiducialMark(((drawingFiducial*)pObj)->getPosition(), pObj->getCenter());
		}
	}
	else if (!m_bObjectClicked && m_drawingMode != drawingMode::none && m_drawingMode != drawingMode::poly)	// no objects being dragged or clicked then add object
	{
		// if object being drawn then stop drawing and add object to list
		addObject(m_drawingMode);
	}
	else if (!m_bObjectClicked)	// select any objects in the rect 
	{
		drawingObject* pObj = getObjectInMouseRect();

		if(pObj != NULL)
			pObj->m_bSelected = true;
	}

	m_mouseDown = false;

	// un-select object, image shift = false, object shift = false
	m_clickedRegionItem = drawingMode::none;
	m_bDragImage = false;
	m_bDragDrawingObject = false;
	m_bObjectClicked = false;

	// if object being shifted then reset object dragging
	if (m_bDragDrawingObject)
	{
		for (int i = 0; i < m_drawingObjects.length(); i++)
			m_drawingObjects[i]->m_bDragging = false;
	}

    //redraw
    this->repaint();

	// reset object shift offset
	m_drawingObjectOffset = QPoint(0, 0);
	m_ObjectPositionRectangle = QRect(-1, -1, 0, 0);
	m_MouseRectangle = QRect(-1, -1, 0, 0);

	// reset image shift offset
	m_imageDragOffset = QPoint(0, 0);

    event->accept();
}

drawingObject* PaintQLabel::getObjectInMouseRect(drawingMode::drawingMode mode)
{
	QRect r = GetImageRectPosition(m_MouseRectangle.normalized(), &m_imageRect, &m_displayRect);

	for (int i = 0; i < m_drawingObjects.length(); i++)
	{
		if (m_drawingObjects[i]->m_pRect->intersects(r) || r.contains(m_drawingObjects[i]->getCenter()))
		{
			if (m_drawingObjects[i]->m_type == mode || mode == drawingMode::any)
				return m_drawingObjects[i];
		}
	}

	return NULL;
}
drawingObject* PaintQLabel::getObjectAtPoint(QPoint pt, drawingMode::drawingMode mode)
{
	for (int i = 0; i < m_drawingObjects.length(); i++)
	{
		if (m_drawingObjects[i]->hitTest(pt, true))
		{
			if (m_drawingObjects[i]->m_type == mode || mode == drawingMode::any)
				return m_drawingObjects[i];
		}
	}

	return NULL;
}


/**
*
*  sets image of widget
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   PaintQLabel::setImage
* Qualifier 
* @param     QImage im 
* @return    void
* Access     public 
*/
void PaintQLabel::setImageIndex(int index)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
	imageContainerIndex = index;
    m_imageRect = getImage().rect();

    this->getDisplayRect();
    this->repaint();
}

/**
*
*  google maps style, zoom in/out to a mouse point
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   PaintQLabel::zoomToPoint
* Qualifier 
* @param     QPoint windowClick 
* @param     int zoomAmount 
* @return    void
* Access     public 
*/
void PaintQLabel::zoomToPoint(QPoint windowClick, int zoomAmount)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
    // increase/decrease size of image area
    double newImageWidth = zoomAmount + m_imageRect.width();
    double newImageHeight = zoomAmount + m_imageRect.height();

    // catch image bigger than a pixel
    if(newImageWidth<0 || newImageHeight<0)
        return;

    // get ratio of window to new image size
    double ratioW = (newImageWidth  / (double)m_displayRect.width());
    double ratioH = (newImageHeight / (double)m_displayRect.height());

    // get clicked coordinate relative to window size
    double imageScaleW = ((double)windowClick.x())/((double)m_displayRect.width());
    double imageScaleH = ((double)windowClick.y())/((double)m_displayRect.height());

    // get pixel clicked in image space
    QPoint imageClickPixel = QPoint(((int)m_imageRect.left() + m_imageRect.width()*imageScaleW),
                                    ((int)m_imageRect.top()  + m_imageRect.height()*imageScaleH));

    // get the window clicked position
    double clickWindowPositionX = (double)windowClick.x();
    double clickWindowPositionY = (double)windowClick.y();

    int left = imageClickPixel.x() - (int)(clickWindowPositionX * ratioW);
    int right = imageClickPixel.y()  - (int)(clickWindowPositionY * ratioH);

    // adjust image boundaries to keep clicked point in same position

    // new size
    QRect r = m_imageRect;

    r.setLeft(left);
    r.setTop(right);

    // resize rect to size of zoomed area
    r.setWidth(newImageWidth);
    r.setHeight(newImageHeight);

    // catch image smaller than window
//    if(r.width() > m_displayRect.width() +50 || r.height() > m_displayRect.width() +50)
 //       return;

    m_imageRect = r;
}

/**
*
*  zoom on mouse wheel movement
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   PaintQLabel::wheelEvent
* Qualifier 
* @param     QWheelEvent * event 
* @return    void
* Access     virtual protected 
*/
void PaintQLabel::wheelEvent ( QWheelEvent * event )
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
    int step = -50;

    if(event->angleDelta().x() > 0 || event->angleDelta().y() > 0)
    {
        step = 50;
    }

    // get mouse position
    int cx = event->x();
    int cy = event->y();

    // make mouse position related to displayRect
    zoomToPoint(QPoint(cx - m_displayRect.left(), cy - m_displayRect.top()), step);

    this->repaint();

    event->accept();
}

/**
*
*  resize image if control resized
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   PaintQLabel::resizeEvent
* Qualifier 
* @param     QResizeEvent * event 
* @return    void
* Access     virtual protected 
*/
void PaintQLabel::resizeEvent(QResizeEvent *event)
{
    this->getDisplayRect();
}

QImage& PaintQLabel::getImage()
{
	targeterImage* t = m_pImagesContainer->getImageAtPtr(imageContainerIndex);

	if (t != NULL)
		return t->getQTImage();
	else
		return QImage();
}

/**
*
*  repaint at new display size
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   PaintQLabel::getDisplayRect
* Qualifier 
* @return    void
* Access     public 
*/
void PaintQLabel::getDisplayRect()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
    if ( !getImage().isNull() )
    {
        double w = (double)getImage().width();
        double h = (double)getImage().height();

        this->m_aspectRatio = w/h;

        this->displayRect(this->rect());
    }
}

/**
*
*  calculate size of rectangle for display of image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   PaintQLabel::displayRect
* Qualifier 
* @param     QRect r 
* @return    void
* Access     public 
*/
void PaintQLabel::displayRect(QRect r)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
    int scaledW = r.width();
    int scaledH = scaledW/m_aspectRatio;

    int offX = 0, offY = 0, displayWidth, displayHeight;

    if( scaledH < r.height() )
    {
        // scale on width
        displayWidth = r.width();
        displayHeight = displayWidth/m_aspectRatio;

        offY = ((double)(r.height() - displayHeight))/2.0;
    }
    else
    {
        displayHeight = r.height();
        displayWidth = displayHeight*m_aspectRatio;

        offX = ((double)(r.width() - displayWidth))/2.0;
    }

    m_displayRect = QRect( QPoint(offX, offY), QPoint(offX+displayWidth, offY+displayHeight) );
}

/**
*
*  print rectangle coordinates/size to screen
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   printRect
* Qualifier 
* @param     QString s 
* @param     QRect r 
* @return    void
* Access     public 
*/
void printRect(QString s, QRect r)
{
    cout << s.toStdString() << ": " << " topleft x = " << r.topLeft().x() << " top left y = " << r.topLeft().y()
         << " bottomright x = " << r.bottomRight().x() << " bottom right y = " << r.bottomRight().y() << endl;
}

/**
*
*  gets target image from drawing shape region
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   PaintQLabel::getTargetImage
* Qualifier 
* @return    void
* Access     public 
*/
QVector<drawingShape> PaintQLabel::getTargetImage(bool bSetAsTarget, bool bTargetRegions, int imageIndex)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
    QRect boundingImageRegion;
	QVector<drawingShape> shapes;
   
	double scaleW = ((double)m_imageRect.width()) / ((double)m_displayRect.width());
	double scaleH = ((double)m_imageRect.height()) / ((double)m_displayRect.height());

	for (int i = 0; i < m_drawingObjects.length(); i++)
	{
		drawingObject* pObj = m_drawingObjects[i];

		// skip images not being indexed -1 indicates return all shapes, if only target sample regions to be returned skip those not filled
		if (imageIndex >= 0 && imageIndex != pObj->m_ImageIndex && bTargetRegions && pObj->m_fillColour == drawingColour::none)
			continue;

		drawingShape shape;

		shape.colour = pObj->m_fillColour;

		//QTransform transform = QTransform().translate(-m_displayRect.left(), -m_displayRect.top()).scale(scaleW, scaleH).translate(m_imageRect.left(), m_imageRect.top());
		if (pObj->m_type == drawingMode::rect)
		{
			shape.type = drawingMode::rect;

			// make coordinates relative to window region by translating
			shape.boundingBox = pObj->m_pRect->normalized();
		}
		else if (pObj->m_type == drawingMode::circle)
		{
			shape.type = drawingMode::circle;
			shape.boundingBox = pObj->m_pRect->normalized();
		}
		else if (pObj->m_type == drawingMode::poly)
		{
			shape.type = drawingMode::poly;

			// translate polygon points to image
			shape.boundingBox = pObj->m_pRect->normalized();

			shape.polygon = *((drawingPoly*)pObj)->m_pPoly;
		}
		else
		{
			shape.type = drawingMode::none;
			resetDrawingObjects();
		}

		//resetDrawingObjects();

		shapes.push_back(shape);

		if (bSetAsTarget)
			emit setTargetArea(shapes[i]);
	}
	return shapes;
}

// need to get true image position
QVector<QPoint> PaintQLabel::targetPoints()
{
	QVector<QPoint> targetPoints;
	QVectorIterator<drawingObject*> pObj(m_drawingObjects);

	while (pObj.hasNext()) {
		drawingObject* pdObj = pObj.next();

		if (pdObj->m_type == drawingMode::cross)
		{
			QPoint p = GetImagePosition(pdObj->m_pRect->topLeft(), &m_imageRect, &m_displayRect);
			
			if(p.x()>=0 && p.y()>=0)
				targetPoints.push_back(p);
		}
	}

	return targetPoints;
}

void PaintQLabel::deleteDrawingObjects(int index)
{
	QMutableVectorIterator<drawingObject*> pObj(m_drawingObjects);
	bool bDeleted = false;

	while (pObj.hasNext()) {
		drawingObject* pdObj = pObj.next();

		// shuffle the other image indexes down that are higher than index
		if (pdObj->m_ImageIndex > index)
		{
			pdObj->m_ImageIndex = pdObj->m_ImageIndex - 1;
		}

		// delete item only do this once
		if (pdObj->m_ImageIndex == imageContainerIndex && !bDeleted)
		{
			pObj.remove();
			bDeleted = true;
			delete pdObj;
		}
	}
}

/**
*
*  delete drawing object
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   PaintQLabel::deleteSelectedDrawingObject
* Qualifier 
* @return    void
* Access     public 
*/
void PaintQLabel::deleteSelectedDrawingObject()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	QMutableVectorIterator<drawingObject*> pObj(m_drawingObjects);

	while (pObj.hasNext()) {
		drawingObject* pdObj = pObj.next();

		if (pdObj->m_bSelected)
		{
			pObj.remove();

			delete pdObj;
		}
	}

    this->repaint();
}

void PaintQLabel::setFillColour(drawingColour::colour colour) 
{
	m_fillColour = colour;

	QMutableVectorIterator<drawingObject*> pObj(m_drawingObjects);

	while (pObj.hasNext()) 
	{
		drawingObject* pdObj = pObj.next();

		if (pdObj->m_bSelected)
			pdObj->m_fillColour = colour;
	}
	this->repaint();
}

void PaintQLabel::getPenBrush(QPainter* painter, bool hover, bool selected, bool bSelectRect, bool drawFilled, drawingColour::colour col)
{
	QPen pen;
	pen.setStyle(Qt::SolidLine);

	if (bSelectRect)	//drawing bounding box for selecting other objects
	{
		pen.setColor(QColor(_COLOUR_SELECT_BOUNDING_BOX));
		pen.setStyle(Qt::DashLine);
	}
	else if (hover && selected)
		pen.setColor(QColor(_COLOUR_SELECT_HOVER));
	else if (hover)
		pen.setColor(QColor(_COLOUR_HOVER));
	else if (selected)
		pen.setColor(QColor(_COLOUR_SELECT));
	else
		pen.setColor(QColor(_COLOUR_NORMAL));
	
	if (drawFilled && col != drawingColour::none)
	{
		if (col == drawingColour::mask_white)
		{
			QColor white50 = Qt::white;
			white50.setAlphaF(0.5);
			painter->setBrush(white50);
		}
		else
		{
			QColor black50 = Qt::black;
			black50.setAlphaF(0.5);
			painter->setBrush(black50);
		}
	}

	painter->setPen(pen);
}

void PaintQLabel::addShapeMaskToImage(cv::Mat& mask, drawingShape shape)
{
	cv::Scalar col;

	if (shape.colour != drawingColour::none)
	{
		if (shape.colour == drawingColour::white || shape.colour == drawingColour::mask_white)
			col = cv::Scalar(255, 255, 255);
		else if (shape.colour == drawingColour::black || shape.colour == drawingColour::mask_black)
			col = cv::Scalar(0, 0, 0);

		// get mask image
		if (shape.type == drawingMode::poly)
		{
			vector <cv::Point> triOut;

			vector<vector<cv::Point> > contours;

			// since poly must be in mask image
			foreach(QPoint p, shape.polygon)
				triOut.push_back(cv::Point(p.x(), p.y()));

			contours.push_back(triOut);

			//cv::fillPoly(mask, triOut, col);

			// fills concave as well as convex polygons
			cv::drawContours(mask, contours, 0, col, CV_FILLED);
		}
		else if (shape.type == drawingMode::circle)
		{
			cv::ellipse(mask, cv::Point(shape.boundingBox.left() + shape.boundingBox.width() / 2, shape.boundingBox.top() + shape.boundingBox.height() / 2),
				cv::Size(shape.boundingBox.width(), shape.boundingBox.height()), 0, 0, 360, col, CV_FILLED);
		}
		else
		{
			cv::rectangle(mask, cv::Rect(shape.boundingBox.left(), shape.boundingBox.top(), shape.boundingBox.width(), shape.boundingBox.height()), col, CV_FILLED);
		}
	}
}

void PaintQLabel::getTargetsFromBinaryImage(cv::Mat binImage, int threshold, SAMPLINGTYPE::type sampling, int gridSpacing, int imageIndex)
{
	cv::Mat sampleRegionsImage = sampleImageForTargets(binImage, threshold, gridSpacing, SAMPLINGTYPE::grid);

	cv::Mat labels, out, stats, centroids;

	out = m_ImageProcessing.getConnectedComponentImage(sampleRegionsImage, labels, stats, centroids);
	
	//imshow("Display window", out);

	for (int i = 1; i < centroids.rows; i++)	// first region is invalid
	{
		double x = centroids.at<double>(i, 0);
		double y = centroids.at<double>(i, 1);

		setTargetPosition(QPoint(x, y), imageIndex);
	}

	this->repaint();
}

void PaintQLabel::setTargetPosition(QPoint imagePoint, int imageIndex)
{
	drawingCross* dObj = new drawingCross(this);

	// get graphics screen position
//	QPoint imagePoint = GetDisplayPosition(p); 

	dObj->m_type = drawingMode::drawingMode::cross;

	dObj->m_pRect = new QRect(imagePoint, imagePoint);

	dObj->m_fillColour = drawingColour::none;
	dObj->m_ImageIndex = imageIndex;

	// add to drawing objects list
	m_drawingObjects.append(dObj);
}

// returns image with sampling positions in white regions
// grid, edge, center, noedge
cv::Mat PaintQLabel::sampleImageForTargets(cv::Mat im, int edgeThreshold, int gridSpacing, SAMPLINGTYPE::type type)
{
	cv::Mat dst;
	cv::Mat bin;

	cv::cvtColor(im, bin, cv::COLOR_BGR2GRAY, 1);

	if (type == SAMPLINGTYPE::center || type == SAMPLINGTYPE::noedge)
	{
		// distance transform to find center and to find distance from edge
		if (SAMPLINGTYPE::center)
		{
			// get center of binary image
			m_ImageProcessing.thinning(bin, dst);
		}
		else
		{
			// get DT
			cv::distanceTransform(bin, dst, cv::DIST_C, CV_DIST_MASK_PRECISE);

			// threshold DT at distance from edge
			threshold(dst, dst, edgeThreshold, 255, CV_THRESH_BINARY);
		}
	}
	else if (type == SAMPLINGTYPE::edge)
	{
		// get contour pixels & subsample them
		vector<vector<cv::Point> > contours;

		cv::findContours(bin, contours, cv::RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

		for (size_t i = 0; i < contours.size(); ++i)
			cv::drawContours(dst, contours, -1, cv::Scalar(255, 255, 255));
	}
	else
	{
		dst = bin;
	}

	// create black grid mask image
	cv::Mat grid = cv::Mat(dst.size(), dst.type(), cv::Scalar(0, 0, 0));
	
	// draw white grid on black area
	drawGrid(grid, gridSpacing, cv::Scalar(255, 255, 255), true);

	// apply AND masking operation 
	bitwise_and(grid, bin, dst);

	return dst;
}

	// now align and sample in grid

	// find min(x,y) point
	/*
	cv::Mat Points;
	cv::findNonZero(dst, Points);

	cv::Rect Min_Rect = cv::boundingRect(Points);
	*/

cv::Mat PaintQLabel::getBinaryImageFromShapes(int imageIndex)
{
	cv::Mat im = m_pImagesContainer->getImageAt(imageIndex).getImage();

	cv::Mat out = cv::Mat(im.cols, im.rows, im.type(), cv::Scalar(255, 255, 255));  // white background
	bool bWhite = false;

	// check for drawing on image 
	QVector<drawingShape> shapes = getTargetImage(false, true, imageIndex);

	if (shapes.length() > 0)
	{
		// any white regions then binary mask with those white regions white in mask, otherwise mask out regions as black
		for (int j = 0; j < shapes.length(); j++)
		{
			 if(shapes[j].colour == drawingColour::mask_white)
				bWhite = true;
		}

		if (bWhite)
			out = cv::Mat(im.cols, im.rows, im.type(), cv::Scalar(0, 0, 0));

		for (int j = 0; j < shapes.length(); j++)
			addShapeMaskToImage(out, shapes[j]);
	}

	return out;
}

// only on uchar images
void PaintQLabel::drawGrid(cv::Mat& im, int gridSpacing, cv::Scalar s, bool bPoints)
{
	int width = im.size().width;
	int height = im.size().height;
	
	if (bPoints)
	{
		if (im.channels() == 1)
		{
			for (int j = 0; j < height; j += gridSpacing)
				for (int i = 0; i < width; i += gridSpacing)
				{
					im.at<uchar>(cv::Point(i, j)) = 255;
				}
		}
		else
		{
			for (int j = 0; j < height; j += gridSpacing)
				for (int i = 0; i < width; i += gridSpacing)
				{

					im.at<cv::Vec3b>(cv::Point(i, j)) = cv::Vec3b(255, 255, 255);
				}
		}
	}
	else
	{
		for (int i = 0; i < height; i += gridSpacing)
			cv::line(im, cv::Point(0, i), cv::Point(width, i), s);

		for (int i = 0; i < width; i += gridSpacing)
			cv::line(im, cv::Point(i, 0), cv::Point(i, height), s);
	}
}

void PaintQLabel::drawTempPoly(QVector<QPoint>* pPoly, QRect* pBoundingRect, QPainter* painter)
{
	if (pPoly == NULL || pPoly->length() < 1)
		return;

	getPenBrush(painter, false, false, m_drawingMode == drawingMode::none, 
				(m_fillColour == drawingColour::white || m_fillColour == drawingColour::black), 
				m_fillColour);

	painter->setPen(QPen(Qt::green));

	// first polygon point
	QPainterPath path;

	path.moveTo(pPoly->at(0).x(), pPoly->at(0).y());

	painter->drawRect(pPoly->at(0).x() - 5, pPoly->at(0).y() - 5, 10, 10);

	// lines
	for (int i = 1; i < pPoly->length(); i++)
	{
		// handle
		painter->drawRect(pPoly->at(i).x() - 5, pPoly->at(i).y() - 5, 10, 10);

		// line
		//painter->drawLine(pPoly->at(i-1).x(), pPoly->at(i-1).y(), pPoly->at(i).x(), pPoly->at(i).y());
		path.lineTo(pPoly->at(i).x(), pPoly->at(i).y());
	}

	painter->strokePath(path, QPen(Qt::green));

	painter->setPen(QPen(Qt::black));
	painter->setBrush(Qt::NoBrush);
}


void PaintQLabel::drawTempRectCircle(QRect* pBoundingRect, QPainter* painter, bool bCircle)
{
	getPenBrush(painter, false, false, m_drawingMode == drawingMode::none, 
				(m_fillColour == drawingColour::white || m_fillColour == drawingColour::black), 
				m_fillColour);

	if (bCircle)
		painter->drawEllipse(*pBoundingRect);
	else
		painter->drawRect(*pBoundingRect);
	
	painter->setPen(QPen(Qt::black));
	painter->setBrush(Qt::NoBrush);
}

/**
*
*  overridden paint event of widget, draws all objects and image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   PaintQLabel::paintEvent
* Qualifier 
* @param     QPaintEvent * event 
* @return    void
* Access     virtual protected 
*/
void PaintQLabel::paintEvent(QPaintEvent* event)
{
#ifdef DEBUGPRINT
#ifdef ONMOUSEPAINTDEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
#endif
    if ( !getImage().isNull() && getImage().paintEngine() != NULL )
    {
        QPainter painter(this);

        if(m_mouseDown && m_bDragImage && m_clickedRegionItem == drawingMode::none)
            painter.drawImage(m_displayRect, getImage(), m_imageRect.translated(m_imageDragOffset));
        else
            painter.drawImage(m_displayRect, getImage(), m_imageRect);

		if (m_drawingMode == drawingMode::poly && m_PolygonPoints.length() > 0 && !m_bLoopClosed)
			drawTempPoly(&m_PolygonPoints, &m_ObjectPositionRectangle, &painter);		// draw temp polygon
		else if (m_ObjectPositionRectangle.x() >= 0 && !(m_drawingMode == drawingMode::fiducial || m_drawingMode == drawingMode::cross))
			drawTempRectCircle(&m_ObjectPositionRectangle, &painter, m_drawingMode == drawingMode::circle);
	
		// paint drawing objects - already drawn rect, circle, poly etc
		for (int i = 0; i < m_drawingObjects.length(); i++)
		{
			if (m_drawingObjects[i]->m_ImageIndex == imageContainerIndex)
				m_drawingObjects[i]->draw(&painter);
		}
		
		if (m_drawGrid)
		{
			painter.setPen(QPen(m_annotationColour));

			for (double i = m_displayRect.left() + gOffX; i <= m_displayRect.right(); i += gSpaceX)
				painter.drawLine(round(i), m_displayRect.top(), round(i), m_displayRect.bottom());

			for (double i = m_displayRect.top() + gOffY; i <= m_displayRect.bottom(); i += gSpaceY)
				painter.drawLine(m_displayRect.left(), round(i), m_displayRect.right(), round(i));

			painter.setPen(QPen(Qt::black));
		}
    }
}

