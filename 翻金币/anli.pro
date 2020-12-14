#-------------------------------------------------
#
# Project created by QtCreator 2020-10-24T09:45:45
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = anli
TEMPLATE = app


SOURCES += main.cpp\
        mainscene.cpp \
    mypushbutton.cpp \
    chooselevelscene.cpp \
    playscene.cpp \
    myicon.cpp \
    dataconfig.cpp

HEADERS  += mainscene.h \
    mypushbutton.h \
    chooselevelscene.h \
    playscene.h \
    myicon.h \
    dataconfig.h

FORMS    += mainscene.ui

RESOURCES += \
    ziyuan.qrc

CONFIG +=c++11
