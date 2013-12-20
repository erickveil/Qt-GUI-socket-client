#-------------------------------------------------
#
# Project created by QtCreator 2013-12-16T13:23:50
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_socket_client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    socketthreadbase.cpp \
    echoclient.cpp

HEADERS  += mainwindow.h \
    socketthreadbase.h \
    echoclient.h

FORMS    += mainwindow.ui
