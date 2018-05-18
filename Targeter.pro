#-------------------------------------------------
#
# Project created by QtCreator 2016-08-23T13:49:42
#
#-------------------------------------------------

QT += core concurrent gui webenginewidgets 

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets 

TARGET = Targeter
TEMPLATE = app


#-IC:/opencv-msvc/install/include/opencv -IC:/opencv-msvc/install/include -LC:/opencv-msvc/install/x64/vc14/lib -lopencv_shape310 -lopencv_stitching310 -lopencv_objdetect310 -lopencv_superres310 -lopencv_videostab310 -lippicvmt -lopencv_calib3d310 -lopencv_features2d310 -lopencv_highgui310 -lopencv_videoio310 -lopencv_imgcodecs310 -lopencv_video310 -lopencv_photo310 -lopencv_ml310 -lopencv_imgproc310 -lopencv_flann310 -lopencv_core310
# remember to set path to dll's in windows system!

#INCLUDEPATH += C:/opencv-msvc/install/include
INCLUDEPATH += C:/opencv/build/include # C:/opencv-latest\opencv\include
INCLUDEPATH += "C:/Program Files/Basler/pylon 5/Development/include"
INCLUDEPATH += "C:/Program Files/Basler/pylon 5/Development/Samples/C++/include"
#INCLUDEPATH += "C:/Program Files (x86)/Visual Leak Detector/include"

LIBS += -L"C:/Program Files/Basler/pylon 5/Development/lib/x64"
#LIBS += -L"C:/Program Files (x86)/Visual Leak Detector/lib/Win64"
#LIBS += -LC:/opencv-msvc/install/x64/vc14/lib


debug {
LIBS += -LC:/opencv-build/lib/Debug
LIBS += -LC:/opencv-build/bin/Debug
} release {
LIBS += -LC:/opencv-build/lib/Release
LIBS += -LC:/opencv-build/bin/Release
}

debug {
#LIBS += -lopencv_world320d
LIBS += -lopencv_shape320d -lopencv_stitching320d -lopencv_objdetect320d -lopencv_superres320d -lopencv_videostab320d -lopencv_calib3d320d -lopencv_features2d320d
LIBS += -lopencv_highgui320d -lopencv_videoio320d -lopencv_imgcodecs320d -lopencv_video320d -lopencv_photo320d -lopencv_ml320d -lopencv_imgproc320d -lopencv_flann320d -lopencv_core320d
} release {
#LIBS += -lopencv_world320
LIBS += -lopencv_shape320 -lopencv_stitching320 -lopencv_objdetect320 -lopencv_superres320 -lopencv_videostab320 -lopencv_calib3d320 -lopencv_features2d320
LIBS += -lopencv_highgui320 -lopencv_videoio320  -lopencv_video320 -lopencv_photo320 -lopencv_ml320 -lopencv_imgproc320 -lopencv_flann320 -lopencv_core320
}

QMAKE_CXXFLAGS_RELEASE += -g
QMAKE_CFLAGS_RELEASE += -g


SOURCES += main.cpp\
        mainwindow.cpp \
    opencvtoqt.cpp \
    openCVtrilateralFilter.cpp \
    paintqlabel.cpp \
    FocusStack.cpp \
    findtargets.cpp \
    findtargetssettingsdialog.cpp \
    HelperFunctions.cpp \
    mergesettingsdialog.cpp

HEADERS  += mainwindow.h \
    opencvtoqt.h \
    haar.hpp \
    openCVtrilateralFilter.h \
    paintqlabel.h \
    globals.h \
    FocusStack.h \
    findtargets.h \
    findtargetssettingsdialog.h \
    HelperFunctions.h \
    mergesettingsdialog.h

FORMS    += mainwindow.ui \
    settingsdialog.ui

RESOURCES = icons.qrc
