#include "NewportController.h"
#include "SystemStringQString.h"
#include "stageControlZ.h"

using namespace System;

QString NewportController::getErrorState(QString errCode)
{
	QString	errorMessage = "";

	if (errCode == "0000")
		return "No errors";
	else
	{
		QByteArray ba = errCode.toLocal8Bit();

		if((ba[1] & 2) & 2)
			errorMessage += "80W output power exceeded ";
		if ((ba[1] & 1) & 1)
			errorMessage += "DC Voltage too low ";
		if ((ba[2] & 4) & 4)
			errorMessage += "Wrong ESP stage ";
		if ((ba[2] & 3) & 3)
			errorMessage += "Homing time out ";
		if ((ba[2] & 2) & 2)
			errorMessage += "Following error ";
		if ((ba[2] & 1) & 1)
			errorMessage += "Short circuit detection ";
		if ((ba[3] & 4) & 4)
			errorMessage += "Wrong ESP stage ";
		if ((ba[3] & 3) & 3)
			errorMessage += "Homing time out ";
		if ((ba[3] & 2) & 2)
			errorMessage += "Following error ";
		if ((ba[3] & 1) & 1)
			errorMessage += "Short circuit detection ";
		if ((ba[4] & 4) & 4)
			errorMessage += "RMS current limit ";
		if ((ba[4] & 3) & 3)
			errorMessage += "Peak current limit ";
		if ((ba[4] & 2) & 2)
			errorMessage += "Positive end of run ";
		if ((ba[4] & 1) & 1)
			errorMessage += "Negative end of run ";
	}

	return errorMessage;
}


NewportController::NewportController(StageControlZ* pTSM) 
{ 
	m_pTSM = pTSM;

	m_COMPortZ = "";

	m_pSMC = gcnew CommandInterfaceSMC100::SMC100();
}

NewportController::NewportController() 
{
	m_pTSM = NULL;
	m_COMPortZ = "";

	m_pSMC = gcnew CommandInterfaceSMC100::SMC100();
}

NewportController::~NewportController()
{
	disconnect();
}

void NewportController::disconnect()
{
	System::String^ errString;

	setKeypad(true);							// enable keypad

	changeState(NEWPORT_STATUS::status::disable);

	m_pSMC->CloseInstrument();
}

void NewportController::setKeypad(bool on)
{
	System::String^ errString;

	int result = m_pSMC->JM_Set(1, on?1:0, errString);	// enable keypad

	reportResult(result, "Keypad on " + QString::number(on), errString);
}

bool NewportController::connectToPort(System::String^ port)
{
	int result;
	double pos = -1;
	System::String^ errString;
	System::String^ outText;

	// first check for z axis stage
	result = m_pSMC->OpenInstrument(port);

	// report stage software version
	result = m_pSMC->VE(1, outText, errString);

	if (result == 0)
	{
		if(m_pTSM != NULL) m_pTSM->showMessage(ss2q("Newport Z axis stage connected to port " + port));
		if(m_pTSM != NULL) m_pTSM->showMessage(ss2q("Software Version= " + outText + "\n"));

		// change stage state to ready
		changeState(NEWPORT_STATUS::status::ready);

		setKeypad(false);

		reportPosition(Q_FUNC_INFO);

		return true;
	}
	else
	{
		m_pSMC->CloseInstrument();
	}

	return false;
}

NEWPORT_STATUS::status NewportController::GetStatusFromString(System::String^ status)
{
	if (status == "0A" || status == "0B" || status == "0C" ||
		status == "0D" || status == "0E" || status == "0F" ||
		status == "10" || status == "11")
		return  NEWPORT_STATUS::status::notref;
	if (status == "32" || status == "33" || status == "34" || status == "35")
		return NEWPORT_STATUS::status::ready;
	if (status == "3C" || status == "3D" || status == "3E" || status == "46")
		return NEWPORT_STATUS::status::disable;
	if (status == "1E" || status == "1F")
		return  NEWPORT_STATUS::status::homing;
	if (status == "14")
		return NEWPORT_STATUS::status::config;
	if (status == "28")
		return NEWPORT_STATUS::status::moving;
	if (status == "35")
		return NEWPORT_STATUS::status::jogging;

	return NEWPORT_STATUS::status::null;
}


QString NewportController::GetStatusString(System::String^ status)
{
	return NEWPORT_STATUS_STRINGS(GetStatusFromString(status));
}

QString NewportController::GetStatusString(QString status)
{
	return GetStatusString(q2ss(status));
}

bool NewportController::checkStatusEqual(NEWPORT_STATUS::status status)
{
	System::String^ errString;
	System::String^ outText;
	System::String^ errCode;

	// recheck status
	int result = m_pSMC->TS(1, errCode, outText, errString);

	if (GetStatusFromString(outText) == status)
		return true;

	return false;
}

bool NewportController::changeState(NEWPORT_STATUS::status requiredStatus)
{
	System::String^ errString;
	System::String^ outText;
	System::String^ errCode;
	int result;

	for(int i=0;i<3;i++) // if it loops more than 2 times (3 to be safe) then something more serious is wrong 
	{
		// check state
		result = m_pSMC->TS(1, errCode, outText, errString);
	
		NEWPORT_STATUS::status currentStatus = GetStatusFromString(outText);
		
		// if not right state then change state
		if (currentStatus != requiredStatus)
		{
			// if we are moving then we should wait and recheck status
			if (currentStatus == NEWPORT_STATUS::status::homing || currentStatus == NEWPORT_STATUS::status::moving)
			{
				// need to wait a bit for movement to complete
				_sleep(1200);

				// recheck status
				result = m_pSMC->TS(1, errCode, outText, errString);

				currentStatus = GetStatusFromString(outText);

				if (currentStatus == requiredStatus)
					return true;
			}

			// leave jogging state - should not be in jogging state in the program leave it and disable keypad
			if (currentStatus == NEWPORT_STATUS::status::jogging)
			{
				result = m_pSMC->JD(1, errString);			// leave jogging state
				result = m_pSMC->JM_Set(1, 0, errString);	// disable keypad

				// recheck status
				int result = m_pSMC->TS(1, errCode, outText, errString);

				currentStatus = GetStatusFromString(outText);

				if (currentStatus == requiredStatus)
					return true;
			}

			// leave config state
			if (currentStatus == NEWPORT_STATUS::status::config)
			{
				result = m_pSMC->PW_Set(1, 0, errString);

				// recheck status
				result = m_pSMC->TS(1, errCode, outText, errString);

				currentStatus = GetStatusFromString(outText);

				if (currentStatus == requiredStatus)
					return true;
			}

			if ((requiredStatus == NEWPORT_STATUS::status::notref || 
				requiredStatus == NEWPORT_STATUS::status::config) &&
				(currentStatus == NEWPORT_STATUS::status::ready ||
				currentStatus == NEWPORT_STATUS::status::disable)
				)
			{
				// reset command
				result = m_pSMC->RS(1, errString);

				// recheck status
				result = m_pSMC->TS(1, errCode, outText, errString);

				currentStatus = GetStatusFromString(outText);

				if (currentStatus == requiredStatus)
					return true;
			}

			if (requiredStatus == NEWPORT_STATUS::status::config &&
				currentStatus == NEWPORT_STATUS::status::notref)
			{
				result = m_pSMC->PW_Set(1, 1, errString);

				// recheck status
				result = m_pSMC->TS(1, errCode, outText, errString);

				currentStatus = GetStatusFromString(outText);

				if (currentStatus == requiredStatus)
					return true;
			}

			// leave disable state
			if (requiredStatus == NEWPORT_STATUS::status::ready &&
				currentStatus == NEWPORT_STATUS::status::disable)
			{
				result = m_pSMC->MM_Set(1, 1, errString);

				// recheck status
				int result = m_pSMC->TS(1, errCode, outText, errString);

				currentStatus = GetStatusFromString(outText);

				if (currentStatus == requiredStatus)
					return true;
			}

			if (currentStatus == NEWPORT_STATUS::status::notref &&  requiredStatus == NEWPORT_STATUS::status::ready)
			{
				// Get home position
				result = m_pSMC->OR(1, errString);

				_sleep(1200);

				// recheck status
				int result = m_pSMC->TS(1, errCode, outText, errString);

				currentStatus = GetStatusFromString(outText);

				if (currentStatus == requiredStatus)
					return true;
			}
			// none of the above work, try rebooting and repeat
		} 
		else
		{
			// we are in the state we want to be
			return true;
		}	
	}
	return false;
}

void NewportController::getPosition(double& z)
{
	int result;
	System::String^ errString;

	// Get position
	if (!m_pSMC->TP(1, z, errString))
	{
		if (m_pTSM != NULL)
			m_pTSM->showMessage(ss2q(errString));
	}
}



void NewportController::SendSomeCommands()
{
	int result;
	double pos = -1;
	System::String^ errString;
	System::String^ outText;
	System::String^ errCode;

	// get in ready state
	changeState(NEWPORT_STATUS::status::ready);

	// now we can move
	// move relative
	result = m_pSMC->PR_Set(1, 10.0, errString);

	double time;
	result = m_pSMC->PT_Set(1, 10.0, errString);
	result = m_pSMC->PT_Get(1, time, errString);

	if(m_pTSM != NULL) m_pTSM->showMessage("time to move 10mm = " + QString::number(time));

	_sleep(time);

	reportResult(result, "Moved stage up 10 mm", errString);

	// Get position
	result = m_pSMC->TP(1, pos, errString);

	reportResult(result, "Stage position = " + QString::number(pos), errString);
}

void NewportController::getStatus()
{
	int result;
	System::String^ errString;
	System::String^ outText;
	System::String^ errCode;

	// send some commands
	result = m_pSMC->TS(1, errCode, outText, errString);

	if (System::String::IsNullOrEmpty(errCode))
	{
		reportResult(result, "Stage controller State= " + GetStatusString(ss2q(outText)) + "\n", errString);
	}
	else
	{
		reportResult(result, "Stage Status: error code= " + ss2q(errCode) + " controller State= " + GetStatusString(ss2q(outText)) + "\n", errString);
	}
}

void NewportController::reportResult(int result, QString s, System::String^ err)
{
	if (result == 0)
	{
		if (m_pTSM != NULL) 
			m_pTSM->showMessage(s);
	}
	else
	{
		if (m_pTSM != NULL) 
			m_pTSM->showMessage(ss2q(err));
	}
}

void NewportController::getInfo()
{
	int result;
	double pos = -1;
	System::String^ errString;
	System::String^ outText;
	System::String^ errCode;

	if (m_COMPortZ != "")
	{
		double RightLimit, LeftLimit, CurrentPosition;
		System::String^ errString;
		System::String^ version;

		// send some commands

		// all these commands can be performed from ready state so ...

		// get in ready state
		changeState(NEWPORT_STATUS::status::ready);

		// Get positive software limit
		int result = m_pSMC->SR_Get(1, RightLimit, errString);

		if (result == 0)
			if(m_pTSM != NULL) m_pTSM->showMessage(ss2q("Right Limit= " + RightLimit.ToString() + "\n"));
		else
			if(m_pTSM != NULL) m_pTSM->showMessage(ss2q(errString));

		// Get negative software limit
		result = m_pSMC->SL_Get(1, LeftLimit, errString);

		if (result == 0)
			if(m_pTSM != NULL) m_pTSM->showMessage(ss2q("Left Limit= " + LeftLimit.ToString() + "\n"));
		else
			if(m_pTSM != NULL) m_pTSM->showMessage(ss2q(errString));

		// Get controller revision information 
		result = m_pSMC->VE(1, version, errString);

		if (result == 0)
			if(m_pTSM != NULL) m_pTSM->showMessage(ss2q("Version= " + version + "\n"));
		else
			if(m_pTSM != NULL) m_pTSM->showMessage(ss2q(errString));

		
		// move relative
		result = m_pSMC->PR_Set(1, 10.0, errString);

		double time;
		result = m_pSMC->PT_Set(1, 10.0, errString);
		result = m_pSMC->PT_Get(1, time, errString);

		if(m_pTSM != NULL) m_pTSM->showMessage("time to move 10mm = " + QString::number(time));

		_sleep(time);

		reportResult(result, "Moved stage up 10 mm", errString);

		// Get position
		result = m_pSMC->TP(1, pos, errString);

		reportResult(result, "Stage position = " + QString::number(pos), errString);
		
		getStatus();
	}
}

void NewportController::moveAbsolute(double z, bool async)
{
	int result;
	System::String^ errString;

	double time;

	double z1;

	getPosition(z1);

	if(z != z1)
	{
		/*
		// difference in distances
		result = m_pSMC->PT_Set(1, z-z1, errString);
		result = m_pSMC->PT_Get(1, time, errString);

		if (m_pTSM != NULL) m_pTSM->showMessage("time to move 10mm (in ms)= " + QString::number(time * 1000));
		*/

		// move absolute
		result = m_pSMC->PA_Set(1, z, errString);

		/*
		// while thread sleeps
		_sleep(time * 1000);

		double pos;
		getPosition(pos);

		while (z < pos)
		{
			if (m_pTSM != NULL) m_pTSM->showMessage(ss2q("Movement needs more time, current position = ") + QString::number(pos) + "\n");
			_sleep(100);
		}
		*/

		if(!async)
		{
			bool bError = false;

			while (checkIfMoving(bError))
			{
				if (bError)
					return;
			}
		}
	

		reportPosition(Q_FUNC_INFO);
	}
	else
	{
		if (m_pTSM != NULL) 
			m_pTSM->showMessage("you are already at this position \n");
		reportPosition(Q_FUNC_INFO);
	}
}

bool NewportController::checkIfMoving(bool& bError)
{
	bError = false;

	System::String^ errString;
	System::String^ errCode;
	System::String^ state;

	int result = m_pSMC->TS(1, errCode, state, errString);

	// takes about 10 ms to get a response
	_sleep(10);

	if(errCode != "0000")
		if (m_pTSM != NULL) m_pTSM->showMessage(getErrorState(ss2q(errCode)), CONSOLECOLOURS::Critical);

	if (state == "28" || state == "1E" || state == "1F")
		return true;
	else
		return false;
}

void NewportController::moveRelative(double z, bool async)
{
	System::String^ errString;
	int result;
	
	double time;

	if (z != 0)
	{
		// move relative
		result = m_pSMC->PR_Set(1, z, errString);

		if(!async)
		{
			bool bError;

			while (checkIfMoving(bError))
			{
				if (bError)
					return;
			}
		}
	
		reportResult(result, "Moved stage (relative)", errString);
	}
	else
	{
		if (m_pTSM != NULL)
			m_pTSM->showMessage("there's no point moving a relative distance of 0!\n");
		reportPosition(Q_FUNC_INFO);
	}
}

void NewportController::stopMotion()
{
	System::String^ errString;
	int result;

	// move relative
	result = m_pSMC->ST(1, errString);

	reportResult(result, "Motion stopped", errString);

	reportPosition(Q_FUNC_INFO);
}


void NewportController::reportPosition(QString functionCall)
{
	double z;

	getPosition(z);
#ifdef DEBUGPRINT
	QString str = functionCall.mid(functionCall.lastIndexOf(':') + 1, functionCall.lastIndexOf('(') - functionCall.lastIndexOf(':') - 1) + ", ";
#else
	QString str = "";
#endif

	QString s = str + "current position ->z: " + QString::number(z);

	if (m_pTSM != NULL)
	{
		m_pTSM->updatePosition(z);
		m_pTSM->showMessage(s.toLocal8Bit().data());
	}
}

void NewportController::sendCommand(QString cmd)
{
	System::String^ outText;

	int result = m_pSMC->WriteToInstrument(q2ss(cmd), outText, 1);

	if (m_pTSM != NULL) m_pTSM->showMessage("command response = " +  ss2q(outText) + "\n");
}

std::wstring NewportController::MarshalString(System::String^ s)
{
	using namespace System::Runtime::InteropServices;
	std::wstring ret;
	System::IntPtr p = Marshal::StringToHGlobalUni(s);
	if (p.ToPointer())
	{
		ret.assign((wchar_t const*)p.ToPointer());
		Marshal::FreeHGlobal(p);
	}
	return ret;
}

System::String^ NewportController::q2ss(const QString &qstring)
{
	return gcnew System::String((const wchar_t *)qstring.utf16());
}

QString NewportController::ss2q(System::String^ str)
{
	/* or ...
	using namespace msclr::interop;
	return QString::fromStdWString(marshal_as<std::wstring>(str));
	*/

	return QString::fromStdWString(MarshalString(str));
}