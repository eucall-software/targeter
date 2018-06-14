#ifndef STAGECONTROLXY_H
#define STAGECONTROLXY_H

#include <QString>
#include <QList>
#include <iterator>

#include "globals.h"

class MarzController;

template<typename T>
class StageState
{
public:
	StageState() { currentPosition = placeToMove.begin(); };
	~StageState() { placeToMove.clear(); };
	void removeAll() { placeToMove.clear(); resetPosition(); }
	void resetPosition() { currentPosition = placeToMove.begin(); };
	void moveNext() { currentPosition++; };
	T moveGetValue() { moveNext(); if (okToMove()) return getValue(); else throw "no more positions in list"; };

	bool isEmpty() { return placeToMove.isEmpty(); };
	bool okToMove() { return (currentPosition != placeToMove.end()); };

	T getValue() { return *currentPosition; };
	void addValue(T val) { placeToMove.append(val); };
private:
	QList<T> placeToMove;
	typename QList<T>::iterator currentPosition;
};

class StageControlXY : public QObject
{
	Q_OBJECT

public:
	StageControlXY();
	~StageControlXY();
	
	
	void showMessage(QString str, CONSOLECOLOURS::colour col = CONSOLECOLOURS::Information) {
		emit LOGCONSOLE(str, col);
	};

private:
	QString m_COMPort;
	MarzController* m_pMarz;
public slots:
	void updatePositions(double x, double y);
	void updatePositions(bool bFiducial);

	void assignPort(QVector<QString> AvailablePorts, QString excludePort);
	void MoveAbsolute(double x, double y, ACTIONS::action act);
	void MoveRelative(double x, double y, ACTIONS::action act);
	void go(double fx, double fy);

	void SendCommand(QString cmd);
	void SetVelocity(double velo);
	void SetJoystick(bool on);

	bool Connect();
	void Disconnect();
	void Abort();

	void Calibrate();
	void MeasureRange();
signals:
	void ACTIONCOMPLETED(QString msg);
	void CONNECTEDTOPORT(QString port);
	void LOGCONSOLE(QString strText, CONSOLECOLOURS::colour col);
	void UPDATEPOSITIONS(bool isFid, double x, double y);
	void STAGECONNECTED(bool isXY, QString);
	void reportCOMPORTS(QVector<QString> str);
	void StageMovementCompleted(QString strMessage);
	void finished();
	void STAGEMOVED(double x, double y, ACTIONS::action act);
};

#endif


