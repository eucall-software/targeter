#ifndef PAINTQLABEL_H
#define PAINTQLABEL_H

#include <QLabel>
#include "globals.h"

/**
* class to manage display of images in Qlabel, manages scaling, panning, drawing objects etc.
*/
class PaintQLabel : public QLabel
{
    Q_OBJECT
protected:
	drawingMode::drawingMode m_drawingMode;
	drawingMode::drawingMode m_clickedRegionItem;
	drawingMode::drawingMode m_hitObject;
    bool m_panMode;
    bool m_isPanning;
    bool m_mouseDown;
    QPoint m_mouseStartPos;
    QPoint m_mouseEndPos;
    QPoint m_imageDragOffset;
    QPoint m_drawingObjectOffset;
public:
    int m_scale;
    QRect m_displayRect;
    QRect m_imageRect;
    double m_aspectRatio;
    QImage m_Image;
    QVector<QPoint> m_PolygonPoints;

    bool m_bLoopClosed;
    QRect m_boundingPolygon;
    QRect m_boundingRectangle;
    QRect m_boundingEllipse;

    int m_image_c_x;
    int m_image_c_y;

    explicit PaintQLabel(QWidget * parent = 0);
    ~PaintQLabel();

    void displayRect(QRect r);
    void getDisplayRect();

    void setImage(QImage im);
    void zoomToPoint(QPoint windowClick, int zoomAmount);
    void getPolygonRect();

    void setDrawingMode(drawingMode::drawingMode mode);
    void setPanMode(bool bChecked);
    bool checkForPolygonClose(QPoint mp);

    void startPanning(drawingMode::drawingMode mode, QPoint pos);

    bool inEllipse(QRect r, QPoint p);
    bool inRect(QRect r, QPoint p);
    bool inPoly(QVector<QPoint> verts, QPoint p);

    void deleteSelectedDrawingObject();
    void getTargetImage();
    void resetDrawingObjects();
signals:
    void disablePanButton();
    void setTargetArea(drawingShape shape);
    void unsetDrawingButtons();

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
