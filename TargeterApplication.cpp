#include "TargeterApplication.h"
#include <exception>

TargeterApplication::TargeterApplication(int& argc, char** argv) :
	QApplication(argc, argv) {
	pMain = nullptr;
}


TargeterApplication::~TargeterApplication()
{
}

void TargeterApplication::setMainWindow(MainWindow* m) { 
	pMain = m; 
}

bool TargeterApplication::notify(QObject* receiver, QEvent* event) {
	bool done = true;
	try {
		done = QApplication::notify(receiver, event);
	}
	catch (const std::exception& ex) {
		if (pMain)
			pMain->shutDownInstruments();
	}
	catch (...) {
		if (pMain)
			pMain->shutDownInstruments();
	}
	return done;
}
