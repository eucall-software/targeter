#include "MarzController.h"
#include "stageControlXY.h"
#include "globals.h"

#include "TANGO DLL C++ Header Files\Tango.h"

void MarzController::setUpErrorStrings()
{
	for(int i =0;i<4114;i++)
		tango_error_strings[i] = "-";
	
	// all these error messages start at 4000 so deduct 4000 from error code

	tango_error_strings[4001] = "internal error";
	tango_error_strings[4002] = "internal error";
	tango_error_strings[4003] = "undefined error";
	tango_error_strings[4004] = "Unknown interface type (problem with connecting?)";
	tango_error_strings[4005] = "Error while initialising interface";
	tango_error_strings[4006] = "no connection with controller";
	tango_error_strings[4007] = "Timeout while reading from interface";
	tango_error_strings[4008] = "Error during command transmission to Tango controller";
	tango_error_strings[4009] = "Command aborted";
	tango_error_strings[4010] = "Command is not supported by Tango controller";
	tango_error_strings[4011] = "Manual Joystick mode switched on";
	tango_error_strings[4012] = "No move command possible because manual joystick enabled";
	tango_error_strings[4013] = "Closed loop controller timeout - could not settle within target window";
	tango_error_strings[4014] = "limit switch activated in travel direction";
	tango_error_strings[4015] = "-";
	tango_error_strings[4016] = "Closed loop controller - Repeated vector start!";
	tango_error_strings[4017] = "Error while calibrating - limit switch not correctly released";

	tango_error_strings[4101] = "No valid axis name";
	tango_error_strings[4102] = "No executable instruction";
	tango_error_strings[4103] = "Too many characters in command line";
	tango_error_strings[4104] = "Invalid instruction";
	tango_error_strings[4105] = "Number is not inside allowed range";
	tango_error_strings[4106] = "Wrong number of parameters";
	tango_error_strings[4107] = "Either !or ? is missing";
	tango_error_strings[4108] = "No TVR possible, while axis active";
	tango_error_strings[4109] = "-";
	tango_error_strings[4110] = "Function not configured";
	tango_error_strings[4111] = "-";
	tango_error_strings[4112] = "Limit switch active";
	tango_error_strings[4113] = "Function not executable, because encoder detected";

	tango_error_strings[0] = "ok";
	tango_error_strings[1] = "no valid axis name";
	tango_error_strings[2] = "no executable instruction";
	tango_error_strings[3] = "too many characters in command line";
	tango_error_strings[4] = "invalid instruction";
	tango_error_strings[5] = "number is not inside allowed range";
	tango_error_strings[6] = "wrong number of parameters";
	tango_error_strings[7] = "either !or ? is missing";
	tango_error_strings[8] = "no TVR possible, while axis active";
	tango_error_strings[9] = "no ON or OFF of axis possible, while TVR active";
	tango_error_strings[10] = "function not configured";
	tango_error_strings[11] = "no move instruction possible, while joystick enabled";
	tango_error_strings[12] = "limit switch active";
	tango_error_strings[13] = "function not executable, because encoder detected";
	tango_error_strings[14] = "Error while calibrating(limit switch could not be released)";
	tango_error_strings[21] = "multiple axis moves are forbidden(e.g.during initialization)";
	tango_error_strings[22] = "automatic or manual move is not allowed(e.g.door open or initialization)";
	tango_error_strings[27] = "emergency STOP is active";
	tango_error_strings[29] = "servo amplifiers are disabled(switched OFF)";
	tango_error_strings[30] = "safety circuit out of order";
	tango_error_strings[50] = "one argument only expected";
	tango_error_strings[51] = "argument is not a number";
	tango_error_strings[52] = "keyword BEGIN or EOF missing";
	tango_error_strings[53] = "unexpected geo type";
	tango_error_strings[58] = "unexpected sequence";
	tango_error_strings[59] = "alpha and beta must not be equal";
	tango_error_strings[70] = "wrong CPLD data";
	tango_error_strings[71] = "ETS error";
	tango_error_strings[72] = "parameter is write protected (check lock bits)";
	tango_error_strings[73] = "internal error, e.g.eeprom data corruption";
	tango_error_strings[74] = "closed loop switched off due to parameter change";
	tango_error_strings[75] = "could not enable axis correction, or axis correction was disabled";
	tango_error_strings[76] = "io extension error(output overload on IO1 or Multi - IO connector)";
	tango_error_strings[77] = "io extension internal communication error(internal bus error)";
	tango_error_strings[78] = "HDI input device error";
	tango_error_strings[79] = "xPos module error";
	tango_error_strings[80] = "internal error: HDI ISR not running";
	tango_error_strings[81] = "internal error : Encoder ISR not running";
	tango_error_strings[82] = "overload on motor connector + 5V";
	tango_error_strings[83] = "overload on AUX I / O + 5V supply";
	tango_error_strings[84] = "overload on encoder + 5V supply";
	tango_error_strings[85] = "overload on AUX I / O + 24V supply";
	tango_error_strings[86] = "low brake output voltage";
}

const char* MarzController::getDLLError(int err)
{
	if (err >= 0 && err <= 4113)
	{
		if(tango_error_strings[err] != "-")
			return (const char*)tango_error_strings[err];
		else
		{
			QString s = "unspecifed error number " + QString::number(err);
			return s.toLocal8Bit().constData();
		}
	}
	else
	{ 
		QString s = "error number " + QString::number(err) + " out of error message range [0:4113]!";
		return s.toLocal8Bit().constData();
	}
}

MarzController::MarzController(StageControlXY* pTSM)
{
	m_pTSM = pTSM;
	m_flag = false;

	m_COMPortXY = "";

	setUpErrorStrings();

	m_pTango = new CTango();

	checkForDLL();
}

MarzController::MarzController()
{
	m_pTSM = nullptr;
	m_flag = false;

	m_COMPortXY = "";

	setUpErrorStrings();

	m_pTango = new CTango();

	checkForDLL();
}

MarzController::~MarzController()
{
	// XY axis stage
	if (m_pTango)
	{
		setJoystick(true);

		if(int err = m_pTango->Disconnect()>0)
			m_pTSM->showMessage(getDLLError(err));
/*
		if(m_pTSM != nullptr) 
			m_pTSM->showMessage("Disconnecting XY Axis Stage");
*/
		delete m_pTango;
	}
}

int MarzController::checkForDLL()
{
	// check if Tango DLL is loaded correctly

	// special function that has its own error values!!!
	int result = m_pTango->GetDLLLoadResult();

	if(result == -1)
	{
		if(m_pTSM != nullptr) 
			m_pTSM->showMessage("Error: DLL not found.\n\nCheck the .dll file name or copy the .dll file into this directory!");
	}
	else if (result == -2)
	{
		if(m_pTSM != nullptr) 
			m_pTSM->showMessage("Warning: Not all DLL functions present.");
	}

	return result;
}

bool MarzController::connectToPort(QString port)
{
	if(m_pTSM != nullptr) 
		m_pTSM->showMessage(port.toLocal8Bit().data());

	// connect to Tango controller
	// could also be 1200, 2400, 4800, 9600, 19200, 38400, 57600 or 115200
	int result = m_pTango->ConnectSimple(1, port.toLocal8Bit().data(), atoi("57600"), false);

	if(result == 0)
	{
		m_COMPortXY = port;

		QString s = "Tango XY stage connected to port " + port;

		if(m_pTSM != nullptr) 
			m_pTSM->showMessage(s.toLocal8Bit().data());

		char version[64];

		if (int err = m_pTango->EnableCommandRetry(false))
			m_pTSM->showMessage(getDLLError(err));

		if (int err = m_pTango->GetDLLVersionString(version, 64) > 0)
			m_pTSM->showMessage(getDLLError(err));

		s = "Tango firmware version=";
		QString s1(version);

		s += s1;

		if(m_pTSM != nullptr) 
			m_pTSM->showMessage(s.toLocal8Bit().data());

		setJoystick(false);

		char msg[20];

		if (int err = m_pTango->GetStatusAxis(msg, 20) > 0)
			m_pTSM->showMessage(getDLLError(err));

		if (m_pTSM != nullptr)
			m_pTSM->showMessage(msg);

		m_pTango->FlushBuffer(0);

		reportPosition(Q_FUNC_INFO);

		return true;
	}
	else
	{
		m_pTSM->showMessage(getDLLError(result));

		m_pTango->FlushBuffer(0);
		m_pTango->Disconnect();
	}

	return false;
}

void MarzController::disconnect()
{
	if(m_pTango != nullptr)
		m_pTango->Disconnect();
}

void MarzController::setJoystick(bool on)
{
	int err=-1;

	if (on)
		err = m_pTango->SetJoystickOn(true, true);
	else
		err = m_pTango->SetJoystickOff();

	if(err)
		m_pTSM->showMessage(getDLLError(err));
}

void MarzController::setVelocity(double velo)
{
	if(velo>0.0)
		m_pTango->SetVel(velo, velo, 0, 0);
}

void MarzController::calibrateZ()
{
	char answer[20];
	char argz[] = "!cal z\r";

	m_pTango->SendString(argz, answer, sizeof(answer), true, 30000);

	m_pTango->FlushBuffer(0);

	reportPosition(Q_FUNC_INFO);
}

void MarzController::measureRangeZ()
{
	char answer[20];
	char argz[] = "!rm z\r";

	m_pTango->SendString(argz, answer, sizeof(answer), true, 30000);

	m_pTango->FlushBuffer(0);

	reportPosition(Q_FUNC_INFO);
}

void MarzController::sendCommand(QString cmd)
{
	char answer[256];
	
	cmd += "\r";

	m_pTango->SendString(cmd.toLocal8Bit().data(), answer, sizeof(answer), TRUE, 1000);

	reportPosition(Q_FUNC_INFO);

	if (m_pTSM != nullptr)
		m_pTSM->showMessage(answer);

	m_pTango->FlushBuffer(0);
}

void MarzController::reportPosition(QString functionCall)
{
	double x, y;

	getPosition(x, y);
#ifdef DEBUGPRINT
	QString str = functionCall.mid(functionCall.lastIndexOf(':') + 1, functionCall.lastIndexOf('(') - functionCall.lastIndexOf(':') - 1) + ", ";
#else
	QString str = "";
#endif

	QString s = str + "current position -> x:" + QString::number(x) + ", y:" + QString::number(y);


	if (m_pTSM != nullptr)
	{
		m_pTSM->updatePositions(x, y);
		m_pTSM->showMessage(s.toLocal8Bit().data());
	}

	m_pTango->FlushBuffer(0);
}

void MarzController::getPosition(double& fx, double& fy)
{
	char x[20], y[20], z[20], a[20];

	double Pos[4];

	// read position from controller
	m_pTango->GetPosSingleAxis(1, &Pos[0]);
	m_pTango->GetPosSingleAxis(2, &Pos[1]);
	//m_pTango->GetPosSingleAxis(3, &Pos[2]);
	//m_pTango->GetPosSingleAxis(4, &Pos[3]);

	// strings
	sprintf(x, "%lf", Pos[0]);
	sprintf(y, "%lf", Pos[1]);
	//sprintf(z, "%lf", Pos[2]);
	//sprintf(a, "%lf", Pos[3]);

	fx = atof(x);
	fy = atof(y);

	m_pTango->FlushBuffer(0);
}

void MarzController::mouseMove(double x, double y)
{
	m_flag = false;

	m_pTango->Go(x, y, 0, 0);

	reportPosition(Q_FUNC_INFO);
}

void MarzController::MoveRelative(double x, double y)
{
	m_flag = false;

	m_pTango->MoveRel(x, y, 0, 0, true);

	//m_pTango->WaitForAxisStop(3, 0, &m_flag);

	reportPosition(Q_FUNC_INFO);
}

void MarzController::moveAbsoluteSingleAxis(int axis, double distance)
{
	m_flag = false;

	char x[20], y[20], z[20], a[20];

	if(axis > 0 && axis < 3)
		m_pTango->MoveAbsSingleAxis(axis, distance, false);

	Sleep(111);

	m_pTango->WaitForAxisStop(3, 0, &m_flag);

	reportPosition(Q_FUNC_INFO);
}

void MarzController::moveAsolute(double x, double y)
{
	m_flag = false;

	m_pTango->MoveAbs(x, y, 0, 0, true);

	//m_pTango->WaitForAxisStop(3, 0, &m_flag);

	reportPosition(Q_FUNC_INFO);
}

void MarzController::calibrateXY()
{
	m_flag = false;

	m_pTango->Calibrate();

	m_pTango->WaitForAxisStop(3, 0, &m_flag);

	reportPosition(Q_FUNC_INFO);
}

void MarzController::measureRangeXY()
{
	m_pTango->RMeasure();

	reportPosition(Q_FUNC_INFO);
}
void MarzController::abortXY()
{
	m_pTango->SetAbortFlag();

	reportPosition(Q_FUNC_INFO);
}
