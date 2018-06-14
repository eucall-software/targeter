//#using <mscorlib.dll>
//#include <vcclr.h>

#include <QString>
#include "globals.h"
#include "NewportController.h"
#include "stageControlZ.h"


StageControlZ::StageControlZ()
{
	m_COMPort = "not available";

	m_pNewport = new NewportController(this);
}

StageControlZ::~StageControlZ()
{
	if (m_pNewport != nullptr)
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

	connectToPort(m_COMPort);

	emit ACTIONCOMPLETED("stage connected");
}

bool StageControlZ::connectToPort(QString port)
{
	if (port != "")
	{
		if (m_pNewport->connectToPort(port))
		{
			m_COMPort = port;
			return true;
		}
	}
	return false;
}

void StageControlZ::Disconnect()
{
	m_pNewport->disconnect();
	emit STAGECONNECTED(false, "?");
	emit ACTIONCOMPLETED("Z stage disconnected");
}
