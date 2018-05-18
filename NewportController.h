#ifndef NEWPORTCONTROLLER_H
#define NEWPORTCONTROLLER_H

#include "globals.h"
#include <QString>
#include <vcclr.h>

class StageControlZ;

class NewportController
{
public:
	NewportController();
	NewportController(StageControlZ* pTSM);
	~NewportController();
	bool connectToPort(System::String^ port);
	void disconnect();

	void moveAbsolute(double z, bool async = false);
	void moveRelative(double z, bool async = false);

	void getPosition(double& z);
	void reportPosition(QString functionCall);
	void stopMotion();
	bool checkIfMoving(bool& bError);

	QString getErrorState(QString errCode);

	void setKeypad(bool on);

	NEWPORT_STATUS::status GetStatusFromString(System::String^ status);
	QString GetStatusString(System::String^ status);
	bool checkStatusEqual(NEWPORT_STATUS::status status);
	void sendCommand(QString command);
	bool changeState(NEWPORT_STATUS::status status);
	void SendSomeCommands();

	QString GetStatusString(QString status);
	void getStatus();
	void reportResult(int result, QString s, System::String^ err);

	static std::wstring MarshalString(System::String^ s);
	static System::String^ q2ss(const QString &qstring);
	static QString ss2q(System::String^ str);

	void getInfo();

private:
	QString m_COMPortZ;
	StageControlZ* m_pTSM;
	gcroot<CommandInterfaceSMC100::SMC100^> m_pSMC;

	// port identifier
	int m_portZ;
};

#endif
