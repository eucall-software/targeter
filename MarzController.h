#ifndef MARZCONTROLLER_H
#define MARZCONTROLLER_H

#include <QString>

#include "TANGO DLL C++ Header Files\Tango.h"

class StageControlXY;

class MarzController
{
public:
	MarzController(StageControlXY* pTSM);
	MarzController();
	~MarzController();

	int checkForDLL();
	bool connectToPort(QString port);
	void disconnect();

	void getPosition(double& x, double& y);
	void reportPosition(QString functionCall);

	void MoveRelative(double x, double y);
	void moveAbsoluteSingleAxis(int axis, double distance);
	void moveAsolute(double x, double y);
	void mouseMove(double x, double y);
	void setVelocity(double velo);

	void setJoystick(bool on);
	
	void calibrateXY();
	void measureRangeXY();
	void abortXY();

	void sendCommand(QString cmd);

	void setUpErrorStrings();
	const char* getDLLError(int err);

	void calibrateZ();
	void measureRangeZ();

private: 
	CTango* m_pTango;
	QString m_COMPortXY;
	StageControlXY* m_pTSM;

	// port identifier
	int m_portXY;
	BOOL m_flag;

	const char* tango_error_strings[4114];
};

#endif

