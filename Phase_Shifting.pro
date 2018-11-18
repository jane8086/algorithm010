QT += core
QT -= gui

TARGET = Phase_Shifting
CONFIG += console
CONFIG -= app_bundle

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_calib3d -lopencv_structured_light
CONFIG += c++11

TEMPLATE = app

SOURCES += main.cpp \
    camera.cpp

HEADERS += \
    camera.h

