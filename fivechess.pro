#-------------------------------------------------
#
# Project created by QtCreator 2016-08-30T15:18:28
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fivechess
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    chessboard.cpp \
    chesslogic.cpp \
    netserver.cpp \
    netclient.cpp \
    hostdia.cpp \
    client_dia.cpp \
    ipgetter.cpp

HEADERS  += mainwindow.h \
    chessboard.h \
    chesslogic.h \
    netserver.h \
    netclient.h \
    hostdia.h \
    client_dia.h \
    ipgetter.h

FORMS    += mainwindow.ui \
    hostdia.ui \
    client_dia.ui

RESOURCES += \
    src.qrc
