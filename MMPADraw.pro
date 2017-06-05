#-------------------------------------------------
#
# Project created by QtCreator 2017-04-11T14:01:16
#
#-------------------------------------------------
# This is a github test

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += static
CONFIG += static-runtime
CONFIG += c++14

TARGET = MMPADraw
TEMPLATE = app

LIBS += -lboost_system -lboost_iostreams


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    viewparam.cpp \
    graph1.cpp \
    pixhist.cpp \
    endview.cpp \
    helpexplanations.cpp \
    threshexport.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    viewparam.h \
    graph1.h \
    pixhist.h \
    endview.h \
    helpexplanations.h \
    threshexport.h

FORMS    += mainwindow.ui \
    viewparam.ui \
    graph1.ui \
    pixhist.ui \
    endview.ui \
    helpexplanations.ui \
    threshexport.ui
