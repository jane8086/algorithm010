QT += core
QT -= gui

TARGET = Phase_Shifting
CONFIG += console
CONFIG -= app_bundle

CONFIG += c++11

INCLUDEPATH += /opt/ros/kinetic/include/opencv-3.3.1-dev/
INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/src

LIBS += -L/opt/ros/kinetic/lib/x86_64-linux-gnu -lopencv_core3 -lopencv_imgcodecs3 -lopencv_highgui3 -lopencv_imgproc3 -lopencv_calib3d3 #-lopencv_structured_light3

INCLUDEPATH += /usr/include/flycapture
LIBS += -lflycapture

TEMPLATE = app

SOURCES += src/main.cpp \
    src/calibration.cpp \
    src/camera.cpp \
    src/lines_rectification.cpp \
    src/monitor.cpp \
    src/patterns.cpp \
    src/phases.cpp \
    src/point_correspondences.cpp \
    src/point_selection.cpp \
    src/preprocessing.cpp \
    src/tools.cpp \
    src/extract_zerophase_point.cpp

HEADERS += \
    include/monitor.h \
    include/calibration.h \
    include/camera.h \
    include/lines_rectification.h \
    include/patterns.h \
    include/phases.h \
    include/point_correspondeces.hpp \
    include/point_selection.h \
    include/preprocessing.h \
    include/tools.h \
    include/extract_zerophase_point.h

