#ifndef DRAWINGOBJECTS_H
#define DRAWINGOBJECTS_H

#include <QObject>
#include <QPainter>
#include "globals.h"

#define _POINT_OBJECT_SIZE 7

class PaintQLabel;

class drawingObject : public QObject {
	Q_OBJECT
public:
	drawingObject();
	drawingObject(PaintQLabel* parent);
	~drawingObject();

	virtual void moveObject(QPoint offset);

	virtual void draw(QPainter* painter) = 0;
	virtual bool hitTest(QPoint pt, bool bMouseDown = false) = 0;

	virtual const QPoint getCenter() { return m_pRect->center(); }

	QBrush getFillBrush();

	void getPenBrush(QPainter* painter);

	// variables
	QRect* m_pRect;

	// image scale parameters
	PaintQLabel* m_pParent;

	// drawing parameters
	drawingColour::colour m_fillColour;
	drawingMode::drawingMode m_type;

	// state parameters
	bool m_bClickedItem;
	bool m_bHoveredOver;
	bool m_bSelected;
	bool m_bDragging;

	// which image does object belong to
	int m_ImageIndex;

protected:
};


class pointObject : public drawingObject {
	Q_OBJECT
public:
	pointObject() { m_objectSize = QSize(_POINT_OBJECT_SIZE, _POINT_OBJECT_SIZE); m_pRect->setWidth(1); m_pRect->setHeight(1); };
	pointObject(PaintQLabel* parent) : drawingObject(parent) {m_objectSize = QSize(_POINT_OBJECT_SIZE, _POINT_OBJECT_SIZE);};
	const QPoint getCenter() { return m_pRect->center(); }
	const QSize getSize() { return m_objectSize; }
protected:
	QSize m_objectSize;
private:
	QPoint m_pointCenter;
};

class rectObject : public drawingObject {
	Q_OBJECT
public:
	rectObject() {};
	rectObject(PaintQLabel* parent) : drawingObject(parent) {};
	void drawRect(QPainter* painter);
};

class drawingRect : public rectObject
{
public:
	drawingRect(){};
	drawingRect(PaintQLabel* parent) : rectObject(parent) {};

	void draw(QPainter* painter) { rectObject::drawRect(painter); };
	bool hitTest(QPoint pt, bool bMouseDown = false);

protected:
	
};

class drawingEllipse : public rectObject
{
public:
	drawingEllipse(PaintQLabel* parent) : rectObject(parent) {};

	void draw(QPainter* painter);
	bool hitTest(QPoint pt, bool bMouseDown = false);

protected:
};

class drawingPoly : public rectObject
{
public:
	drawingPoly(PaintQLabel* parent) : rectObject(parent) {};

	void draw(QPainter* painter);
	bool hitTest(QPoint pt, bool bMouseDown = false);

	drawingPoly() { m_pPoly = nullptr; }
	void moveObject(QPoint offset);

	~drawingPoly() {
		if (m_pPoly)
			delete m_pPoly;
	}

	QPolygon* m_pPoly;
protected:

};

class drawingFiducial : public pointObject
{
public:
	drawingFiducial(PaintQLabel* parent) : pointObject(parent) { m_position = FIDUCIAL::topleft_overview; };
	void setPosition(FIDUCIAL::position position) { m_position = position; };
	FIDUCIAL::position getPosition() { return m_position; };
	void draw(QPainter* painter);
	bool hitTest(QPoint pt, bool bMouseDown = false);
protected:
	FIDUCIAL::position m_position;
};

class drawingMoveObjective : public pointObject
{
public:
	drawingMoveObjective(PaintQLabel* parent) : pointObject(parent) {};

	void draw(QPainter* painter);
	bool hitTest(QPoint pt, bool bMouseDown = false);
protected:
};

class drawingCross : public pointObject
{
public:
	drawingCross(PaintQLabel* parent) : pointObject(parent) {};

	void draw(QPainter* painter);

	bool hitTest(QPoint pt, bool bMouseDown = false);
protected:

};

#endif