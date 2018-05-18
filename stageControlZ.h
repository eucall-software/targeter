#ifndef STAGECONTROLZ_H
#define STAGECONTROLZ_H

#include <QString>
#include <QVector>

#include "globals.h"

class NewportController;

class StageControlZ : public QObject
{
	Q_OBJECT

public:
	StageControlZ();
	~StageControlZ();
	
	void showMessage(QString str, CONSOLECOLOURS::colour col = CONSOLECOLOURS::Information) {
		emit LOGCONSOLE(str, col);
	};

private:
	QString m_COMPort;

	NewportController* m_pNewport;

public slots:
	void updatePosition(double z);
	void updatePosition(bool bFiducial);

	void assignPort(QVector<QString> AvailablePorts, QString excludePort);
	void moveAbsolute(double z, ACTIONS::action act);
	void MoveRelative(double z, ACTIONS::action act);
	void stopMotion(ACTIONS::action act);
	void SendCommand(QString cmd);
	void SetVelocity(double velo);
	void SetKeypad(bool on);
	void Calibrate();
	void MeasureRange();
	bool Connect();
	void Disconnect();
	void Abort();
	void go(double fz);
signals:
	void ACTIONCOMPLETED(QString msg);
	void CONNECTEDTOPORT(QString port);
	void LOGCONSOLE(QString strText, CONSOLECOLOURS::colour col);
	void UPDATEPOSITION(bool bFid, double z);
	void STAGECONNECTED(bool isXY, QString);
	void StageMovementCompleted(QString strMessage);
	void finished();
	void STAGEMOVED(double z, ACTIONS::action act);
};

#endif


