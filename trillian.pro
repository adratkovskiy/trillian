#-------------------------------------------------
#
# Project created by QtCreator 2018-04-28T12:43:53
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = trillian
TEMPLATE = app


SOURCES += \
        main.cpp \
        dialog.cpp \
    trilliantits.cpp

HEADERS += \
        dialog.h \
    trilliantits.h

FORMS += \
        dialog.ui

LIBS += -lSDL
