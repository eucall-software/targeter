#ifndef MOUSEMOVELABEL_H
#define MOUSEMOVELABEL_H

#include <QLabel>

class MouseMoveLabel : public QLabel
{
	Q_OBJECT

public:
	MouseMoveLabel(QWidget * parent = 0);
	~MouseMoveLabel();

	QRect m_Rect;
	bool m_mouseDown;

signals:
	void  mouseDownPoint(double fx, double fy);

protected slots:
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
};

#endif // CLICKABLELABEL_H