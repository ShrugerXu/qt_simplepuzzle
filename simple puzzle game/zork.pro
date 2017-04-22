#-------------------------------------------------
#
# Project created by QtCreator 2015-11-02T23:08:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zork
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    room.cpp \
    item.cpp \
    inventory.cpp \
    stage.cpp \
    clickqlabel.cpp

HEADERS  += mainwindow.h \
    room.h \
    item.h \
    inventory.h \
    stage.h \
    clickqlabel.h

FORMS    += mainwindow.ui

RESOURCES += \
    recipe.qrc
