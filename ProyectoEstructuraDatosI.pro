#-------------------------------------------------
#
# Project created by QtCreator 2017-02-25T21:19:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProyectoEstructuraDatosI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    lista.cpp \
    file.cpp \
    folder.cpp \
    textfile.cpp \
    filesystemutils.cpp

HEADERS  += mainwindow.h \
    lista.h \
    file.h \
    folder.h \
    textfile.h \
    filesystemutils.h

FORMS    += mainwindow.ui

RESOURCES += \
    folder.qrc
