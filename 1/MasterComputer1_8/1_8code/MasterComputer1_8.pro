#-------------------------------------------------
#
# Project created by QtCreator 2018-04-24T10:01:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MasterComputer1_8
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += MyWidget \
               qextserialport\

SOURCES += main.cpp\
        mainwindow.cpp \
    datahandle.cpp \
    transmitdata.cpp \
    MyWidget/comportwidget.cpp \
    MyWidget/controlwidget.cpp \
    MyWidget/powerwidget.cpp \
    MyWidget/promptmessage.cpp \
    MyWidget/runwidget.cpp \
    qextserialport/qextserialbase.cpp \
    qextserialport/qextserialport.cpp \
    qextserialport/win_qextserialport.cpp

HEADERS  += mainwindow.h \
    datahandle.h \
    transmitdata.h \
    MyWidget/comportwidget.h \
    MyWidget/controlwidget.h \
    MyWidget/powerwidget.h \
    MyWidget/promptmessage.h \
    MyWidget/runwidget.h \
    qextserialport/qextserialbase.h \
    qextserialport/qextserialport.h \
    qextserialport/win_qextserialport.h
