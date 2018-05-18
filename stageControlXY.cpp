//#using <mscorlib.dll>
//#include <vcclr.h>

#include <QString>
#include "globals.h"
#include "MarzController.h"
#include "NewportController.h"
#include "StageControlXY.h"
/*
#using <System.dll>

using namespace System;
using namespace System::ComponentModel;
using namespace System::IO::Ports;
using namespace System::Runtime::InteropServices;
*/

StageControlXY::StageControlXY()
{
	m_COMPort = "";

	m_pMarz = new MarzController(this);
}

StageControlXY::~StageControlXY()
{
	if (m_pMarz != NULL)
		delete m_pMarz;
}

bool StageControlXY::Connect()
{
	if (m_COMPort == "")
		return false;

	if (m_COMPort != "")
		if (m_pMarz->connectToPort(m_COMPort))
			emit STAGECONNECTED(true, m_COMPort);

	emit ACTIONCOMPLETED("XY stage connected");
}

void StageControlXY::Disconnect()
{
	m_pMarz->disconnect();
	emit STAGECONNECTED(true, "?");	
	emit ACTIONCOMPLETED("XY stage disconnected");
}

// detect the COM port and connect Stage to it
void StageControlXY::assignPort(QVector<QString> AvailablePorts, QString excludePort)
{
	for (int i = 0; i < AvailablePorts.length(); i++)
	{
		if (AvailablePorts[i] == excludePort)
			continue;

		if (m_pMarz->connectToPort(AvailablePorts[i]))
		{
			m_COMPort = AvailablePorts[i];
			break;
		}
	}
	
	emit CONNECTEDTOPORT(m_COMPort);
}

void StageControlXY::MoveAbsolute(double x, double y, ACTIONS::action act)
{
	m_pMarz->moveAsolute(x, y);

	if (act == ACTIONS::nothing)
		emit ACTIONCOMPLETED("move absolute XY completed");
	else
		emit STAGEMOVED(x, y, act);
}

void StageControlXY::MoveRelative(double x, double y, ACTIONS::action act)
{
	m_pMarz->MoveRelative(x, y);

	if (act == ACTIONS::nothing)
		emit ACTIONCOMPLETED("move relative complete");
	else
		emit STAGEMOVED(x, y, act);
}

void StageControlXY::go(double fx, double fy)
{
	m_pMarz->mouseMove(fx, fy);

	emit ACTIONCOMPLETED("go to " + QString::number(fx) + " " + QString::number(fy));
}

void StageControlXY::SendCommand(QString cmd)
{
	m_pMarz->sendCommand(cmd);

	emit ACTIONCOMPLETED("command " + cmd + " completed");
}
void StageControlXY::SetVelocity(double velo)
{
	m_pMarz->setVelocity(velo);

	emit ACTIONCOMPLETED("set velocity complete");
}
void StageControlXY::SetJoystick(bool on)
{
	m_pMarz->setJoystick(on);

	QString state = (on ? "on" : "off");

	emit ACTIONCOMPLETED("set joystick " + state +" complete");
}

void StageControlXY::Calibrate()
{
	m_pMarz->calibrateXY();

	emit ACTIONCOMPLETED("calibration complete");
}
void StageControlXY::MeasureRange()
{
	m_pMarz->measureRangeXY();

	emit ACTIONCOMPLETED("range measurement complete");
}
void StageControlXY::Abort()
{
	m_pMarz->abortXY();

	emit ACTIONCOMPLETED("XY stage command aborted");
}

void StageControlXY::updatePositions(bool bFiducial)
{
	double x, y;

	m_pMarz->getPosition(x, y);

	emit UPDATEPOSITIONS(bFiducial, x, y);
	
	emit ACTIONCOMPLETED("XY get position");
}

void StageControlXY::updatePositions(double x, double y) 
{ 
	emit UPDATEPOSITIONS(false, x, y); 
}


