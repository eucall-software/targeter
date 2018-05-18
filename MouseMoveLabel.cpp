#include <QMouseEvent>

#include "MouseMoveLabel.h"

MouseMoveLabel::MouseMoveLabel(QWidget * parent) : QLabel(parent)
{
	m_mouseDown = false;
}

MouseMoveLabel::~MouseMoveLabel()
{
}

void MouseMoveLabel::mousePressEvent(QMouseEvent* event)
{
	m_mouseDown = true;

	event->accept();
}

void MouseMoveLabel::mouseMoveEvent(QMouseEvent* event)
{
	double fx = event->pos().x();
	double fy = event->pos().y();

	fx /= double(this->width());
	fy /= double(this->height());

	if (fx < 0 || fx>1 || fy < 0 || fy >1)
		return;

	if(m_mouseDown)
		emit mouseDownPoint(fx, fy);
}

void MouseMoveLabel::mouseReleaseEvent(QMouseEvent* event)
{
	m_mouseDown = false;
}
