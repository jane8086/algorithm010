QT += core
QT -= gui

TARGET = Phase_Shifting
CONFIG += console
CONFIG -= app_bundle

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_calib3d -lopencv_structured_light
CONFIG += c++11

INCLUDEPATH += /usr/include/flycapture
LIBS += -lflycapture

TEMPLATE = app

SOURCES += src/main.cpp \
    src/camera.cpp \
    src/patterns.cpp

HEADERS += \
    include/camera.h \
    include/patterns.h

