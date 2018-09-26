#ifndef DRAWINGOBJECTS_H
#define DRAWINGOBJECTS_H

#include <QObject>
#include <QPainter>
#include "globals.h"

#define _POINT_OBJECT_SIZE 7

class PaintQLabel;

class drawingObject {
public:
	drawingObject();
	drawingObject(PaintQLabel* parent);
	drawingObject(const drawingObject &other):
		m_pRect(other.m_pRect),
		m_bHighLight(other.m_bHighLight),
		m_pParent(other.m_pParent),
		m_fillColour(other.m_fillColour),
		m_type(other.m_type),
		m_bClickedItem(other.m_bClickedItem),
		m_bHoveredOver(other.m_bHoveredOver),
		m_bSelected(other.m_bSelected),
		m_bDragging(other.m_bDragging),
		ID(other.ID),
		name(other.name),
		desc(other.desc),
		regionType(other.regionType),
		m_ImageIndex(other.m_ImageIndex){ }
	~drawingObject();

	virtual void moveObject(QPoint offset);

	virtual void draw(QPainter* painter) = 0;
	virtual bool hitTest(QPoint pt, bool bMouseDown = false) = 0;

	virtual const QPoint getCenter() { return m_pRect->center(); }

	//QBrush getFillBrush() {};

	void getPenBrush(QPainter* painter);

	void setHighlight(bool bHighlight) {
		m_bHighLight = bHighlight;
	}

	// variables
	QSharedPointer<QRect> m_pRect;

	bool m_bHighLight;

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

	// annotation information
	QString ID;
	QString name;
	QString desc;
	shapeAnnotationType::Type regionType;

	// which image does object belong to
	int m_ImageIndex;

protected:
};

class pointObject : public drawingObject {
public:
	pointObject() { m_objectSize = QSize(_POINT_OBJECT_SIZE, _POINT_OBJECT_SIZE); m_pRect->setWidth(1); m_pRect->setHeight(1); };
	pointObject(PaintQLabel* parent) : drawingObject(parent) {m_objectSize = QSize(_POINT_OBJECT_SIZE, _POINT_OBJECT_SIZE);};
	pointObject(const pointObject &other) : drawingObject(other), m_objectSize(other.m_objectSize), m_pointCenter(other.m_pointCenter) {};
	const QPoint getCenter() { return m_pRect->center(); }
	const QSize getSize() { return m_objectSize; }
protected:
	QSize m_objectSize;
private:
	QPoint m_pointCenter;
};

class rectObject : public drawingObject {
public:
	rectObject() {};
	rectObject(const rectObject &other) : drawingObject(other) {};
	rectObject(PaintQLabel* parent) : drawingObject(parent) {};
	void drawRect(QPainter* painter);
};

class drawingRect : public rectObject
{
public:
	drawingRect(){};
	drawingRect(PaintQLabel* parent) : rectObject(parent) {};
	drawingRect(const drawingRect &other) : rectObject(other){};
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
	drawingPoly(PaintQLabel* parent) : rectObject(parent) { m_pPoly = QSharedPointer<QPolygon>(new QPolygon); };
	drawingPoly() : rectObject() { m_pPoly = QSharedPointer<QPolygon>(new QPolygon); }

	drawingPoly(const drawingPoly &other) : rectObject(other) {
		drawingPoly& poly = (drawingPoly)other;

		for (int i = 0; i < poly.m_pPoly->length(); i++)
			m_pPoly->append(poly.m_pPoly->at(i));
	};

	~drawingPoly() { m_pPoly->empty(); }

	void moveObject(QPoint offset);
	void draw(QPainter* painter);
	bool hitTest(QPoint pt, bool bMouseDown = false);
	void addPoint(QPoint pt) { m_pPoly->append(pt); };

	QSharedPointer<QPolygon> getPoly() { return m_pPoly; };
protected:
	QSharedPointer<QPolygon> m_pPoly;

};

class drawingSampling : public drawingPoly
{
public:
	drawingSampling(PaintQLabel* parent) : drawingPoly(parent) {};
	drawingSampling() : drawingPoly() {};
	void draw(QPainter* painter);
	bool hitTest(QPoint pt, bool bMouseDown = false);
	void addPoint(QPoint pt) { 
		if(m_pPoly->length()>2)
			m_pPoly->remove(0);	// keep only three points in list
		m_pPoly->append(pt); 
	};
};

class drawingFiducial : public pointObject
{
public:
	drawingFiducial(PaintQLabel* parent) : pointObject(parent) { m_position = FIDUCIAL::topleft_overview; };
	drawingFiducial(const drawingFiducial &other) : pointObject(other) {};
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
	drawingMoveObjective(const drawingMoveObjective &other) : pointObject(other) {};
	void draw(QPainter* painter);
	bool hitTest(QPoint pt, bool bMouseDown = false);
protected:
};

class drawingCross : public pointObject
{
public:
	drawingCross(PaintQLabel* parent) : pointObject(parent) {};
	drawingCross(const drawingCross &other) : pointObject(other) {};
	void draw(QPainter* painter);

	bool hitTest(QPoint pt, bool bMouseDown = false);
protected:

};

#endif