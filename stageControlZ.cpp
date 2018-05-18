//#using <mscorlib.dll>
//#include <vcclr.h>

#include <QString>
#include "globals.h"
#include "MarzController.h"
#include "NewportController.h"
#include "stageControlZ.h"
/*
#using <System.dll>

using namespace System;
using namespace System::ComponentModel;
using namespace System::IO::Ports;
using namespace System::Runtime::InteropServices;
*/

StageControlZ::StageControlZ()
{
	m_COMPort = "";

	m_pNewport = new NewportController(this);
}

StageControlZ::~StageControlZ()
{
	if (m_pNewport != NULL)
		delete m_pNewport;
}


void StageControlZ::updatePosition(double z) {
	emit UPDATEPOSITION(false, z);
};


void StageControlZ::updatePosition(bool bFiducial)
{
	double z;

	m_pNewport->getPosition(z);

	emit UPDATEPOSITION(bFiducial, z);

	emit ACTIONCOMPLETED("Z get position");
}

void StageControlZ::assignPort(QVector<QString> AvailablePorts, QString excludePort)
{
	m_COMPort = "not available";

	for (int i = 0; i < AvailablePorts.length(); i++)
	{
		if (AvailablePorts[i] == excludePort)
			continue;

		if (m_pNewport->connectToPort(NewportController::q2ss(AvailablePorts[i])))
		{
			m_COMPort = AvailablePorts[i];
			break;
		}
	}
	emit CONNECTEDTOPORT(m_COMPort);
}

void StageControlZ::moveAbsolute(double z, ACTIONS::action act)
{
	m_pNewport->moveAbsolute(z, act == ACTIONS::jog);

	if (act != ACTIONS::jog)
	{
		if (act == ACTIONS::nothing)
			emit ACTIONCOMPLETED("move absolute Z complete");
		else
			emit STAGEMOVED(z, act);
	}
}

void StageControlZ::MoveRelative(double z, ACTIONS::action act)
{
	m_pNewport->moveRelative(z, act == ACTIONS::jog);

	if (act == ACTIONS::nothing)
		emit ACTIONCOMPLETED("move relative complete");
	else
		emit STAGEMOVED(z, act);
}

void StageControlZ::stopMotion(ACTIONS::action act)
{
	m_pNewport->stopMotion();

	if (act != ACTIONS::jog)
		emit ACTIONCOMPLETED("stop motion complete");

}


void StageControlZ::go(double fz)
{
	//m_pMarz->mouseMove(fx, fy);

	emit ACTIONCOMPLETED("go to " + QString::number(fz));
}

void StageControlZ::SendCommand(QString cmd)
{
	m_pNewport->sendCommand(cmd);

	emit ACTIONCOMPLETED("command " + cmd + " completed");
}

void StageControlZ::SetVelocity(double velo)
{
	//m_pMarz->setVelocity(velo);

	emit ACTIONCOMPLETED("set velocity complete");
}

void StageControlZ::SetKeypad(bool on)
{
	m_pNewport->setKeypad(on);

	QString state = (on ? "on" : "off");

	emit ACTIONCOMPLETED("set joystick " + state +" complete");
}

void StageControlZ::Calibrate()
{
	//m_pMarz->calibrateXY();


	emit ACTIONCOMPLETED("calibration complete");
}
void StageControlZ::MeasureRange()
{
	//m_pMarz->measureRangeXY();

	emit ACTIONCOMPLETED("range measurement complete");
}
void StageControlZ::Abort()
{
	//m_pMarz->abortXY();

	emit ACTIONCOMPLETED("XY stage command aborted");
}

bool StageControlZ::Connect()
{
	if (m_COMPort == "")
		return false;

	if (m_COMPort != "")
		m_pNewport->connectToPort(NewportController::q2ss(m_COMPort));

	emit ACTIONCOMPLETED("stage connected");
}

void StageControlZ::Disconnect()
{
	m_pNewport->disconnect();
	emit STAGECONNECTED(false, "?");
	emit ACTIONCOMPLETED("Z stage disconnected");
}
