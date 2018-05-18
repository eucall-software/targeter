#pragma once

#include <QApplication>
#include "mainwindow.h"

class TargeterApplication : public QApplication
{
public:
	TargeterApplication(int& argc, char** argv);
	~TargeterApplication();

	
	bool notify(QObject* receiver, QEvent* event);

	void setMainWindow(MainWindow* m);


private:
	MainWindow* pMain;
};
