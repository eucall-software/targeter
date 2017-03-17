#include "mainwindow.h"
#include <QApplication>

void customHandler(QtMsgType type, const char* msg) {
	fprintf(stderr, msg);
	fflush(stderr);
}

/**
*
*  main entry function of targeter
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   main
* Qualifier 
* @param     int argc 
* @param     char * argv[] 
* @return    int
* Access     public 
*/
int main(int argc, char *argv[]) 
{
    QApplication a(argc, argv);

	std::cout << "hi" << std::endl;

	
    a.setOrganizationName("XFEL");
    a.setApplicationName("Targeter");
    MainWindow w;
    w.show();

    return a.exec();
}



