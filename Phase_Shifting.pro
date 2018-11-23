QT += core
QT += gui

TARGET = Phase_Shifting

CONFIG += c++11
CONFIG += console
#CONFIG -= app_bundle

INCLUDEPATH += /opt/ros/kinetic/include/opencv-3.3.1-dev/
INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/src

LIBS += -L/opt/ros/kinetic/lib/x86_64-linux-gnu -lopencv_core3 -lopencv_imgcodecs3 -lopencv_highgui3 -lopencv_imgproc3 -lopencv_calib3d3 -lopencv_structured_light3


INCLUDEPATH += /usr/include/flycapture
LIBS += -lflycapture

TEMPLATE = app

SOURCES += src/main.cpp \
    src/camera.cpp \
    src/imagedisplaywindow.cpp \
    src/openglwindow.cpp \
    src/patterns.cpp \

HEADERS += \
    include/camera.h \
    include/imagedisplaywindow.h \
    include/openglwindow.h \
    include/param_config.h \
    include/patterns.h

