// Targeter - target identification software for EUCALL workpackage 6
// Licensed under the GPL License. See LICENSE file in the project root for full license information.
// Copyright(C) 2017  David Watts 

#include "mainwindow.h"
#include "TargeterApplication.h"
#ifdef _HAVE_IMAGEMAGICK
#include <Magick++.h> 
#endif
#include <exception>

/*
void customHandler(QtMsgType type, const char* msg) {
	fprintf(stderr, msg);
	fflush(stderr);
}
*/

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
    TargeterApplication a(argc, argv);
#ifdef _HAVE_IMAGEMAGICK
	Magick::InitializeMagick(*argv);
#endif
    a.setOrganizationName("European XFEL");
	a.setOrganizationDomain("xfel.eu");
    a.setApplicationName("Targeter");

    MainWindow w;

	a.setMainWindow(&w);
    w.show();

    return a.exec();
}



