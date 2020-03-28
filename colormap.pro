#-------------------------------------------------
#
# Project created by QtCreator 2020-01-01T20:53:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = colormap
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


# for linux qt4
# follow https://stackoverflow.com/questions/16509932/using-qt-creator-c-11-nullptr-is-keyworded
QMAKE_CXXFLAGS += -std=c++0x


CONFIG += c++11

SOURCES += \
    main.cpp \
    widget.cpp

HEADERS += \
        widget.h \
    widget.h

FORMS += \
        widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += \
    C:\OpenCV345\opencv\build\include\opencv2 \
    C:\OpenCV345\opencv\build\include\opencv \
    C:\OpenCV345\opencv\build\include \



LIBS += \
     C:/OpenCV345/opencv/build/x64/vc15/lib/opencv_world345.lib \
     C:/OpenCV345/opencv/build/x64/vc15/lib/opencv_world345d.lib




RC_FILE=logo.rc


RESOURCES += \
    colormapScale/colormapscale.qrc
