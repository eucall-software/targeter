#include <QWheelEvent>
#include <QPainter>
#include <QImage>
#include <QDebug>
#include <iostream>
#include "paintqlabel.h"
#include "globals.h"

using namespace std;

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
    m_bLoopClosed = false;
    m_panMode = false;
    m_mouseDown = false;
    m_isPanning = false;
    m_drawingMode = drawingMode::none;
    m_clickedRegionItem = drawingMode::none;
    m_hitObject = drawingMode::none;

    m_mouseStartPos = QPoint(-1,-1);
    m_mouseEndPos = QPoint(-1,-1);

    m_boundingEllipse = QRect(-1,-1,0,0);
    m_boundingRectangle = QRect(-1,-1, 0, 0);

    emit unsetDrawingButtons();
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

    // the criteria for panning image
    if(m_panMode && m_clickedRegionItem == drawingMode::none)
    {
        m_panMode = false;
        m_imageDragOffset = QPoint(0,0);
        emit disablePanButton();
    }
    this->repaint();
}

/**
*
*  sets mode to panning image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   PaintQLabel::setPanMode
* Qualifier 
* @param     bool bChecked 
* @return    void
* Access     public 
*/
void PaintQLabel::setPanMode(bool bChecked)
{
    m_panMode = bChecked;

    //if(bChecked)
    //     m_drawingMode = drawingMode::none;
}

/**
*
*  checks to see if point is in polygon
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   PaintQLabel::inPoly
* Qualifier 
* @param     QVector<QPoint> verts 
* @param     QPoint p 
* @return    bool
* Access     public 
*/
bool PaintQLabel::inPoly(QVector<QPoint> verts, QPoint p)
{
    int i, j;
    bool c = false;

    for (i=0, j=verts.length()-1; i<verts.length(); j=i++)
    {
        if ( ((verts[i].y() > p.y()) != (verts[j].y() > p.y())) &&
        (p.x() < (verts[j].x() - verts[i].x()) * (p.y() - verts[i].y()) / (verts[j].y() - verts[i].y()) + verts[i].x()) )
            c = !c;
    }

    return c;
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
    for(int i=0;i<m_PolygonPoints.length();i++)
    {
        QPoint point = mp - m_PolygonPoints[i];
        if (point.manhattanLength() < 5)
        {
            m_PolygonPoints[i] = mp;

            // remove other points not used in closed polygon
            m_PolygonPoints.remove(i+1, m_PolygonPoints.length()-i-1);
            getPolygonRect();

            return true;
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
* FullName   PaintQLabel::startPanning
* Qualifier 
* @param     drawingMode mode 
* @param     QPoint pos 
* @return    void
* Access     public 
*/
void PaintQLabel::startPanning(drawingMode::drawingMode mode, QPoint pos)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
    m_clickedRegionItem = mode;

    m_mouseStartPos = pos;
    m_mouseEndPos = pos;

    if(mode == drawingMode::none)
    {
        this->repaint();

        m_isPanning = m_panMode;
    }
    else
    {
        m_isPanning = m_panMode;

        this->repaint();
    }
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

    if ( !m_Image.isNull())
    {
        m_drawingObjectOffset=QPoint(0,0);

        // check the last active object
        if(m_boundingRectangle.contains(event->pos()) && m_drawingMode == drawingMode::rect)
        {
            startPanning(drawingMode::rect, event->pos());
        }
        else if(m_boundingEllipse.contains(event->pos()) && m_drawingMode == drawingMode::circle)
        {
            startPanning(drawingMode::circle, event->pos());
        }
        else if(inPoly(m_PolygonPoints, event->pos()) && m_bLoopClosed && m_drawingMode == drawingMode::poly)
        {
            startPanning(drawingMode::poly, event->pos());
        }
        else if(m_drawingMode == drawingMode::poly)
        {
            const QPoint mp = event->pos();

            // if clicked point hits another polygon point then close polygon
            if(m_bLoopClosed)
            {
                m_PolygonPoints.clear();
                m_bLoopClosed = false;
            }
            else
            {
                if(m_clickedRegionItem != drawingMode::poly)
                    m_bLoopClosed = checkForPolygonClose(mp);
            }
            // add point to polygon either as another polygon point or in a new polygon
            m_PolygonPoints.push_front(mp);

            this->repaint();
        }
        else
        {
            // pann image
            startPanning(drawingMode::none, event->pos());
        }
        event->accept();
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
void PaintQLabel::mouseReleaseEvent ( QMouseEvent * event )
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
    if(m_mouseDown)
    {
        m_mouseEndPos = event->pos();

        // no drawing being performed then move image
        if(m_isPanning)
        {
            if(m_clickedRegionItem == drawingMode::rect)
                m_boundingRectangle.translate(m_drawingObjectOffset);
            else if(m_clickedRegionItem == drawingMode::circle)
                m_boundingEllipse.translate(m_drawingObjectOffset);
            else if(m_clickedRegionItem == drawingMode::poly)
            {
                m_drawingObjectOffset = (m_mouseEndPos - m_mouseStartPos);

                for(int i=0; i<m_PolygonPoints.length(); i++)
                    m_PolygonPoints[i] += m_drawingObjectOffset;

                m_boundingPolygon.translate(m_drawingObjectOffset);
            }
            else
            {
                QPoint distance = (m_mouseStartPos - m_mouseEndPos);

                double scaleW  = ((double)m_imageRect.width())/((double)m_displayRect.width());
                double scaleH = ((double)m_imageRect.height())/((double)m_displayRect.height());

                QPoint scaledDistance = QPoint(distance.x()*scaleW, distance.y()*scaleH);

                m_imageRect.translate(scaledDistance);
            }
        }   // no drawing objects clicked then finish end point of object
        else if(m_clickedRegionItem == drawingMode::none)
        {
            if(m_drawingMode == drawingMode::rect)
                m_boundingRectangle = QRect(m_mouseStartPos, m_mouseEndPos);
            else if(m_drawingMode == drawingMode::circle)
                m_boundingEllipse = QRect(m_mouseStartPos, m_mouseEndPos);
        }
    }

    m_isPanning = false;
    m_mouseDown = false;
    m_clickedRegionItem = drawingMode::none;
    m_drawingObjectOffset = QPoint(0,0);
    m_imageDragOffset = QPoint(0,0);

    //redraw
    this->repaint();
    event->accept();
}

/**
*
* checks if point is in rectangle
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   PaintQLabel::inRect
* Qualifier 
* @param     QRect r 
* @param     QPoint p 
* @return    bool
* Access     public 
*/
bool PaintQLabel::inRect(QRect r, QPoint p)
{
#ifdef DEBUGPRINT
#ifdef ONMOUSEPAINTDEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
#endif
    if(p.x()>=r.left() && p.x()<=r.right() && p.y()>=r.top() && p.y()<=r.bottom())
        return true;
    else
        return false;
}

/**
*
*  checks if point is in ellipse
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   PaintQLabel::inEllipse
* Qualifier 
* @param     QRect r 
* @param     QPoint p 
* @return    bool
* Access     public 
*/
bool PaintQLabel::inEllipse(QRect r, QPoint p)
{
#ifdef DEBUGPRINT
#ifdef ONMOUSEPAINTDEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
#endif
    double w2 = r.width()>>1;
    double h2 = r.height()>>1;

    double dx = (double)abs(p.x() - r.center().x());
    double dy = (double)abs(p.y() - r.center().y());

    if (w2 <= 0.0 || dy <= 0.0)
        return false;

    double val = ((dx*dx)/(w2*w2))+((dy*dy)/(h2*h2));

    if(val <= 1.0)
        return true;
    else
        return false;
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
void PaintQLabel::mouseMoveEvent ( QMouseEvent * event )
{
#ifdef DEBUGPRINT
#ifdef ONMOUSEPAINTDEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
#endif
    if ( !m_Image.isNull())
    {
        //hit test
        if(inRect(m_boundingRectangle, event->pos()))
            m_hitObject = drawingMode::rect;
        else if(inPoly(m_PolygonPoints, event->pos()))
            m_hitObject = drawingMode::poly;
        else if(inEllipse(m_boundingEllipse, event->pos()))
            m_hitObject = drawingMode::circle;
        else
            m_hitObject = drawingMode::none;

        if(m_mouseDown)
        {
            m_mouseEndPos = event->pos();

            if(m_isPanning)
            {
                if(m_clickedRegionItem == drawingMode::none)
                {
                    // need to scale translated Rect to image dimensions
                    QPoint distance = (m_mouseStartPos - m_mouseEndPos);

                    double scaleW  = ((double)m_imageRect.width())/((double)m_displayRect.width());
                    double scaleH = ((double)m_imageRect.height())/((double)m_displayRect.height());

                    QPoint scaledDistance = QPoint(distance.x()*scaleW, distance.y()*scaleH);

                    m_imageDragOffset = scaledDistance;
                }
                else
                {
                    m_drawingObjectOffset = (m_mouseEndPos - m_mouseStartPos);
                }       
            }
            else
            {
                if(m_clickedRegionItem == drawingMode::none)
                {
                    if(m_drawingMode == drawingMode::rect)
                    {
                        m_boundingRectangle = QRect(m_mouseStartPos, m_mouseEndPos);
                    }
                    else if(m_drawingMode == drawingMode::circle)
                    {
                        m_boundingEllipse = QRect(m_mouseStartPos, m_mouseEndPos);
                    }
                }
            }
        }

        this->repaint();
        event->accept();
    }
}

/**
*
*  gets polygon's enclosing rectangle
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   PaintQLabel::getPolygonRect
* Qualifier 
* @return    void
* Access     public 
*/
void PaintQLabel::getPolygonRect()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
    m_boundingPolygon = QRect(m_PolygonPoints[0], m_PolygonPoints[0]);

    // get bounding rectangle
    foreach(QPoint pt, m_PolygonPoints)
    {
        m_boundingPolygon.setLeft(min(m_boundingPolygon.left(), pt.x()));
        m_boundingPolygon.setRight(max(m_boundingPolygon.right(), pt.x()));
        m_boundingPolygon.setTop(min(m_boundingPolygon.top(), pt.y()));
        m_boundingPolygon.setBottom(max(m_boundingPolygon.bottom(), pt.y()));
    }
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
void PaintQLabel::setImage(QImage im)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
    m_Image = im;
    m_imageRect = im.rect();

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
    if ( !m_Image.isNull() )
    {
        double w = (double)m_Image.width();
        double h = (double)m_Image.height();

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
void PaintQLabel::getTargetImage()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
    QRect boundingImageRegion;
    drawingShape shape;

    double scaleW = ((double)m_imageRect.width())/((double)m_displayRect.width());
    double scaleH = ((double)m_imageRect.height())/((double)m_displayRect.height());

    //QTransform transform = QTransform().translate(-m_displayRect.left(), -m_displayRect.top()).scale(scaleW, scaleH).translate(m_imageRect.left(), m_imageRect.top());
    if(m_drawingMode == drawingMode::rect)
    {
        shape.type = drawingMode::rect;

        // make coordinates relative to window region by translating
        boundingImageRegion = m_boundingRectangle.normalized();
    }
    else if(m_drawingMode == drawingMode::circle)
    {
        shape.type = drawingMode::circle;
        boundingImageRegion = m_boundingEllipse.normalized();
    }
    else if(m_drawingMode == drawingMode::poly)
    {
        shape.type = drawingMode::poly;

        // translate polygon points to image

        boundingImageRegion = m_boundingPolygon.normalized();

        shape.polygon = m_PolygonPoints;

        // translate points to window coordinates
        shape.polygon.translate(QPoint(-m_displayRect.left(), -m_displayRect.top()));

        // now scale to image size
        for(int i=0;i<shape.polygon.length();i++)
			shape.polygon[i] = QPoint(shape.polygon[i].x()*scaleW, shape.polygon[i].y()*scaleH);

        shape.polygon.translate(QPoint(m_imageRect.left()+1, m_imageRect.top()+1));
    }
    else
    {
        shape.type = drawingMode::none;
        resetDrawingObjects();
        return;
    }

    //translate mouse points to window coordinates
    boundingImageRegion.translate(QPoint(-m_displayRect.left(), -m_displayRect.top()));

    // scale into image

    //scale offset
    boundingImageRegion.moveTopLeft(QPoint(boundingImageRegion.left()*scaleW, boundingImageRegion.top()*scaleH));

    //scale size
    boundingImageRegion.setSize(QSize(boundingImageRegion.width()*scaleW, boundingImageRegion.height()*scaleH));

    // add to image offset
    boundingImageRegion.translate(QPoint(m_imageRect.left()+1, m_imageRect.top()+1));

    shape.boundingBox = boundingImageRegion;

    //shape.boundingBox =transform.mapRect(boundingImageRegion);

    shape.printDebug();

    resetDrawingObjects();

    emit setTargetArea(shape);
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

    if(m_drawingMode == drawingMode::circle)
    {
        m_boundingEllipse = QRect(-1,-1,0,0);

    }
    else if(m_drawingMode == drawingMode::rect)
    {

       m_boundingRectangle = QRect(-1,-1,0,0);
    }
    else if(m_drawingMode == drawingMode::poly)
    {
        m_PolygonPoints.clear();
    }

    this->repaint();
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
    if ( !m_Image.isNull() )
    {
        QPainter painter(this);

        if(m_mouseDown && m_isPanning && m_clickedRegionItem == drawingMode::none)
        {
            painter.drawImage(m_displayRect, m_Image, m_imageRect.translated(m_imageDragOffset));
        }
        else
            painter.drawImage(m_displayRect, m_Image, m_imageRect);

        if(m_drawingMode == drawingMode::poly &&  m_PolygonPoints.length()>0)
        {
            painter.setPen(QPen(Qt::black));

            // first draw bounding polygon
            if(m_bLoopClosed)
            {
                painter.drawRect(m_boundingPolygon.translated(m_drawingObjectOffset));
                painter.setPen(QPen(Qt::blue));
            }

            if(m_hitObject == drawingMode::poly || (m_clickedRegionItem == drawingMode::poly && m_isPanning))
                painter.setPen(Qt::green);
            else if(m_clickedRegionItem == drawingMode::poly)
                painter.setPen(QPen(Qt::red));
            else if(m_bLoopClosed)
                painter.setPen(QPen(Qt::blue));
            else
                painter.setPen(QPen(Qt::black));

            // first polygon point
            painter.drawRect(QRect(m_PolygonPoints[0]- QPoint(5,5)+ m_drawingObjectOffset, QSize(10,10)));

             // first polygon points and lines
            if(m_PolygonPoints.length()>1)
            {
                for(int i=1; i<m_PolygonPoints.length(); i++)
                {
                    painter.drawRect(QRect(m_PolygonPoints[i]- QPoint(5,5) + m_drawingObjectOffset, QSize(10,10)));
                    painter.drawLine(m_PolygonPoints[i-1] + m_drawingObjectOffset, m_PolygonPoints[i]+m_drawingObjectOffset);
                }
            }

            painter.setPen(QPen(Qt::black));
        }

        if(m_drawingMode == drawingMode::rect &&m_boundingRectangle.x()>=0)
        {
            if(m_mouseStartPos.x()>=0 && m_mouseEndPos.x()>0)
            {
                if(m_hitObject == drawingMode::rect || (m_clickedRegionItem == drawingMode::rect && m_isPanning))
                    painter.setPen(Qt::green);
                else if(m_clickedRegionItem == drawingMode::rect)
                    painter.setPen(QPen(Qt::red));
                else
                    painter.setPen(QPen(Qt::black));

                if(m_isPanning && m_clickedRegionItem == drawingMode::rect)
                {
                    painter.drawRect(m_boundingRectangle.translated(m_drawingObjectOffset));
                }
                else
                    painter.drawRect(m_boundingRectangle);

                painter.setPen(QPen(Qt::black));
            }
        }

        if(m_drawingMode == drawingMode::circle && m_boundingEllipse.x()>=0)
        {
            if(m_mouseStartPos.x()>=0 && m_mouseEndPos.x()>0)
            {
                if(m_hitObject == drawingMode::circle || (m_clickedRegionItem == drawingMode::circle && m_isPanning))
                    painter.setPen(Qt::green);
                else if(m_clickedRegionItem == drawingMode::circle)
                    painter.setPen(QPen(Qt::red));
                else
                    painter.setPen(QPen(Qt::black));

                if(m_isPanning && m_clickedRegionItem == drawingMode::circle)
                {
                    painter.drawEllipse(m_boundingEllipse.translated(m_drawingObjectOffset));
                }
                else
                    painter.drawEllipse(m_boundingEllipse);

                painter.setPen(QPen(Qt::black));
            }
        }
    }
}

