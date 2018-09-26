#include "drawingObjects.h"

// Targeter - target identification software for EUCALL workpackage 6
// Licensed under the GPL License. See LICENSE file in the project root for full license information.
// Copyright(C) 2017  David Watts 

#include "paintqlabel.h"
#include "globals.h"

using namespace std;

double sqr(double x) { return x*x; };

double dist2(QPoint v, QPoint w) { return sqr(v.x() - w.x()) + sqr(v.y() - w.y()); };

double distToSegmentSquared(QPoint p, QPoint v, QPoint w)
{
	double l2 = dist2(v, w);
	if (l2 == 0)
		return dist2(p, v);

	double t = ((p.x() - v.x()) * (w.x() - v.x()) + (p.y() - v.y()) * (w.y() - v.y())) / l2;

	t = MAX(0, MIN(1, t));

	return dist2(p, QPoint(v.x() + t * (w.x() - v.x()), v.y() + t * (w.y() - v.y())));
};

double distToSegment(QPoint p, QPoint v, QPoint w) { return sqrt(distToSegmentSquared(p, v, w)); }

drawingObject::drawingObject()
{
	m_fillColour = drawingColour::none;

	m_bHighLight = false;
	m_bClickedItem = false;
	m_bSelected = false;
	m_bDragging = false;
	m_type = drawingMode::none;


	m_pParent = nullptr;

	m_ImageIndex = -1;
}

drawingObject::drawingObject(PaintQLabel* parent) : drawingObject()
{
	m_pParent = parent;
}

drawingObject::~drawingObject() 
{

}

void rectObject::drawRect(QPainter* painter)
{
	drawingObject::getPenBrush(painter);

	QRect r = PaintQLabel::GetDisplayRectPosition(*m_pRect, &m_pParent->m_imageRect, &m_pParent->m_displayRect);

	if (m_fillColour == drawingColour::mask_black)
		painter->fillRect(r, painter->brush().color());
	else
		painter->drawRect(r);

	painter->setPen(QPen(Qt::black));
	painter->setBrush(Qt::NoBrush);
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
bool drawingRect::hitTest(QPoint p, bool bMouseDown)
{
#ifdef DEBUGPRINT
#ifdef ONMOUSEPAINTDEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
#endif
	bool inObject = false;

	QPoint topleft = PaintQLabel::GetDisplayPosition(m_pRect->topLeft(), &m_pParent->m_imageRect, &m_pParent->m_displayRect);
	QPoint bottomright = PaintQLabel::GetDisplayPosition(m_pRect->bottomRight(), &m_pParent->m_imageRect, &m_pParent->m_displayRect);

	if (p.x() >= topleft.x() && p.x() <= bottomright.x() && p.y() >= topleft.y() && p.y() <= bottomright.y())
		inObject = true;

	if (bMouseDown)
		m_bClickedItem = inObject;
	m_bHoveredOver = inObject;

	return inObject;
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
bool drawingEllipse::hitTest(QPoint p, bool bMouseDown)
{
#ifdef DEBUGPRINT
#ifdef ONMOUSEPAINTDEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
#endif

	double scaleW = ((double)m_pParent->m_displayRect.width()) / ((double)m_pParent->m_imageRect.width());
	double scaleH = ((double)m_pParent->m_displayRect.height()) / ((double)m_pParent->m_imageRect.height());

	double w2 = m_pRect->width() >> 1;
	double h2 = m_pRect->height() >> 1;

	w2 *= scaleW;
	h2 *= scaleH;

	QPoint origin = PaintQLabel::GetDisplayPosition(m_pRect->center(), &m_pParent->m_imageRect, &m_pParent->m_displayRect);

	double dx = (double)abs(p.x() - origin.x());
	double dy = (double)abs(p.y() - origin.y());

	bool inObject = false;

	if (w2 <= 0.0)
	{
		if (dx == 0 && dy <= h2)
			inObject = true;
	}
	else if (h2 <= 0.0)
	{
		if (dy == 0 && dx <= w2)
			inObject = true;
	}
	else
	{
		double val = ((dx*dx) / (w2*w2)) + ((dy*dy) / (h2*h2));

		if (val <= 1.0)
			inObject = true;
	}

	if (bMouseDown)
		m_bClickedItem = inObject;
	m_bHoveredOver = inObject;

	return inObject;
}

bool drawingFiducial::hitTest(QPoint p, bool bMouseDown)
{
#ifdef DEBUGPRINT
#ifdef ONMOUSEPAINTDEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
#endif
	double scaleW = ((double)m_pParent->m_displayRect.width()) / ((double)m_pParent->m_imageRect.width());
	double scaleH = ((double)m_pParent->m_displayRect.height()) / ((double)m_pParent->m_imageRect.height());

	double w2 = m_pRect->width() >> 1;
	double h2 = m_pRect->height() >> 1;

	w2 *= scaleW;
	h2 *= scaleH;

	QPoint origin = PaintQLabel::GetDisplayPosition(getCenter(), &m_pParent->m_imageRect, &m_pParent->m_displayRect);

	int dx = p.x() - origin.x();
	int dy = p.y() - origin.y();

	bool inObject = false;

	if (abs(dy) <= m_objectSize.height() && abs(dx) <= m_objectSize.width())
		inObject = true;
	
	if (bMouseDown)
		m_bClickedItem = inObject;
	m_bHoveredOver = inObject;

	return inObject;
}

bool drawingCross::hitTest(QPoint p, bool bMouseDown)
{
	bool inObject = false;

	QPoint pos = PaintQLabel::GetDisplayPosition(getCenter(), &m_pParent->m_imageRect, &m_pParent->m_displayRect);

	QRect r = QRect(pos - QPoint(m_objectSize.width(), m_objectSize.height()), QSize(m_objectSize.width() * 2.0, m_objectSize.height() * 2.0));

	if (r.contains(p))
		inObject = true;

	if (bMouseDown)
		m_bClickedItem = inObject;
	m_bHoveredOver = inObject;

	return inObject;
}

bool drawingMoveObjective::hitTest(QPoint p, bool bMouseDown)
{
	bool inObject = false;

	QPoint pos = PaintQLabel::GetDisplayPosition(getCenter(), &m_pParent->m_imageRect, &m_pParent->m_displayRect);

	QRect r = QRect(pos - QPoint(m_objectSize.width(), m_objectSize.height()), QSize(m_objectSize.width() * 2.0, m_objectSize.height() * 2.0));

	if (r.contains(p))
		inObject = true;

	if (bMouseDown)
		m_bClickedItem = inObject;
	m_bHoveredOver = inObject;

	return inObject;
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
bool drawingPoly::hitTest(QPoint p, bool bMouseDown)
{
	int i, j;
	bool inObject = false;

	if (this->m_pPoly != nullptr)
	{
		for (i = 0, j = this->m_pPoly->length() - 1; i < this->m_pPoly->length(); j = i++)
		{
			QPoint px = this->m_pPoly->at(i);
			QPoint py = this->m_pPoly->at(j);

			px = PaintQLabel::GetDisplayPosition(px, &m_pParent->m_imageRect, &m_pParent->m_displayRect);
			py = PaintQLabel::GetDisplayPosition(py, &m_pParent->m_imageRect, &m_pParent->m_displayRect);

			if (((px.y() > p.y()) != (py.y() > p.y())) &&
				(p.x() < (py.x() - px.x()) * (p.y() - px.y()) / (py.y() - px.y()) + px.x()))
				inObject = !inObject;
		}
	}

	if (bMouseDown)
		m_bClickedItem = inObject;
	m_bHoveredOver = inObject;

	return inObject;
}


bool drawingSampling::hitTest(QPoint p, bool bMouseDown)
{
	int i, j;
	int minDist = 3;
	bool inObject = false;

	if (this->m_pPoly != nullptr)
	{
		for (i = 0, j = this->m_pPoly->length() - 1; i < this->m_pPoly->length(); j = i++)
		{
			QPoint px = this->m_pPoly->at(i);
			QPoint py = this->m_pPoly->at(j);

			px = PaintQLabel::GetDisplayPosition(px, &m_pParent->m_imageRect, &m_pParent->m_displayRect);
			py = PaintQLabel::GetDisplayPosition(py, &m_pParent->m_imageRect, &m_pParent->m_displayRect);

			if (distToSegment(px, py, p) < minDist)
				inObject = true;
		}
	}

	if (bMouseDown)
		m_bClickedItem = inObject;
	m_bHoveredOver = inObject;

	return inObject;
}


void drawingObject::moveObject(QPoint offset)
{
	QPoint imageOffset = PaintQLabel::GetImagePosition(offset, &m_pParent->m_imageRect, &m_pParent->m_displayRect);

	//QPoint distanceToMove = offset - m_pRect->topLeft();

	m_pRect->moveTopLeft(imageOffset);
}

void drawingPoly::moveObject(QPoint offset)
{
	QPoint imageOffset = PaintQLabel::GetImagePosition(offset, &m_pParent->m_imageRect, &m_pParent->m_displayRect);

	QPoint distanceToMove = imageOffset - m_pRect->topLeft();

	m_pRect->moveTopLeft(imageOffset);

	if (m_type == drawingMode::poly)
		m_pPoly->translate(distanceToMove.x(), distanceToMove.y());
}

void drawingEllipse::draw(QPainter* painter)
{
	drawingObject::getPenBrush(painter);

	QRect r = PaintQLabel::GetDisplayRectPosition(*m_pRect, &m_pParent->m_imageRect, &m_pParent->m_displayRect);

	painter->drawEllipse(r);

	painter->setPen(QPen(Qt::black));
	painter->setBrush(Qt::NoBrush);
}

void drawingFiducial::draw(QPainter* painter)
{
	drawingObject::getPenBrush(painter);

	QPoint pt = PaintQLabel::GetDisplayPosition(getCenter(), &m_pParent->m_imageRect, &m_pParent->m_displayRect);

	QRect rect(pt - QPoint(m_objectSize.width(), m_objectSize.height()), m_objectSize*2);

	painter->drawEllipse(rect);

	int space = 3;
	int line_sizeX = 3 * m_objectSize.width() / 2;
	int line_sizeY = 3 * m_objectSize.height() / 2;

	painter->drawLine(pt - QPoint(line_sizeX, 0), pt - QPoint(space, 0));
	painter->drawLine(pt + QPoint(0, space), pt + QPoint(0, line_sizeY));
	painter->drawLine(pt - QPoint(0, line_sizeY), pt - QPoint(0, space));
	painter->drawLine(pt + QPoint(space, 0), pt + QPoint(line_sizeX, 0));

	painter->drawText(rect.translated(-rect.width(), -rect.height()), Qt::TextDontClip, FIDUCIAL_POSITION_STRINGS_SHORT(m_position));

	painter->setPen(QPen(Qt::black));
	painter->setBrush(Qt::NoBrush);
}

void drawingMoveObjective::draw(QPainter* painter)
{
	drawingObject::getPenBrush(painter);

	QPoint pt = PaintQLabel::GetDisplayPosition(getCenter(), &m_pParent->m_imageRect, &m_pParent->m_displayRect);

	QPoint topLeft = pt - QPoint(m_objectSize.width(), m_objectSize.height());

	QRect rect;

	QSize circle_size = m_objectSize * 2.0;

	rect.setTopLeft(topLeft);
	rect.setSize(circle_size);

	painter->drawRect(rect);

	painter->drawLine(rect.topLeft(), rect.bottomRight());
	painter->drawLine(rect.bottomLeft(), rect.topRight());

	painter->setPen(QPen(Qt::black));
	painter->setBrush(Qt::NoBrush);
}

void drawingCross::draw(QPainter* painter)
{
	drawingObject::getPenBrush(painter);

	QPoint pt = PaintQLabel::GetDisplayPosition(getCenter(), &m_pParent->m_imageRect, &m_pParent->m_displayRect);

	painter->drawLine(pt - QPoint(m_objectSize.width(), 0), pt - QPoint(1, 0));
	painter->drawLine(pt + QPoint(0, 1), pt + QPoint(0, m_objectSize.height()));
	painter->drawLine(pt - QPoint(0, m_objectSize.height()), pt - QPoint(0, 1));
	painter->drawLine(pt + QPoint(1, 0), pt + QPoint(m_objectSize.width(), 0));

	painter->setPen(QPen(Qt::black));
	painter->setBrush(Qt::NoBrush);
}

void drawingSampling::draw(QPainter* painter)
{
	if (m_pPoly == nullptr || m_pPoly->length() < 1)
		return;

	drawingObject::getPenBrush(painter);

	painter->setPen(QPen(Qt::green));

	// first polygon point
	QPainterPath path;

	QPoint pt = PaintQLabel::GetDisplayPosition(m_pPoly->at(0), &m_pParent->m_imageRect, &m_pParent->m_displayRect);

	path.moveTo(pt.x(), pt.y());

	painter->drawEllipse(pt.x() - 5, pt.y() - 5, 10, 10);

	// lines
	for (int i = 0; i < m_pPoly->length(); i++)
	{
		QPoint pt = PaintQLabel::GetDisplayPosition(m_pPoly->at(i), &m_pParent->m_imageRect, &m_pParent->m_displayRect);

		painter->drawEllipse(pt.x() - 5, pt.y() - 5, 10, 10);

		// line
		path.lineTo(pt.x(), pt.y());
	}

	painter->strokePath(path, QPen(Qt::green));

	painter->setPen(QPen(Qt::black));
	painter->setBrush(Qt::NoBrush);
}

void drawingPoly::draw(QPainter* painter)
{
	if (m_pPoly == nullptr || m_pPoly->length() < 1)
		return;

	drawingObject::getPenBrush(painter);

	// first draw bounding polygon
	rectObject::drawRect(painter);

	painter->setPen(QPen(Qt::green));

	// first polygon point
	QPainterPath path;

	QPoint pt = PaintQLabel::GetDisplayPosition(m_pPoly->at(0), &m_pParent->m_imageRect, &m_pParent->m_displayRect);

	path.moveTo(pt.x(), pt.y());

	painter->drawRect(pt.x() - 5, pt.y() - 5, 10, 10);

	// lines
	for (int i = 1; i < m_pPoly->length(); i++)
	{
		QPoint pt = PaintQLabel::GetDisplayPosition(m_pPoly->at(i), &m_pParent->m_imageRect, &m_pParent->m_displayRect);

		// handle
		painter->drawRect(pt.x() - 5, pt.y() - 5, 10, 10);

		// line
		path.lineTo(pt.x(), pt.y());
	}

	// polygon closure

	pt = PaintQLabel::GetDisplayPosition(m_pPoly->at(m_pPoly->length() - 1), &m_pParent->m_imageRect, &m_pParent->m_displayRect);

	path.lineTo(pt.x(), pt.y());

	if (m_fillColour != drawingColour::none)
	{
		if (m_fillColour == drawingColour::white)
			painter->fillPath(path, QBrush(QColor("white")));
		else
			painter->fillPath(path, QBrush(QColor("black")));
	}

	painter->strokePath(path, QPen(Qt::green));

	painter->setPen(QPen(Qt::black));
	painter->setBrush(Qt::NoBrush);
}

void drawingObject::getPenBrush(QPainter* painter)
{
	PaintQLabel::getPenBrush(painter, m_bHoveredOver, m_bSelected, false, (m_fillColour == drawingColour::mask_white || m_fillColour == drawingColour::mask_black), 
		m_bHighLight, m_fillColour);
}