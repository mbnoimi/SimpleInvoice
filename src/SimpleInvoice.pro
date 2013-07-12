#-------------------------------------------------
#
# Project created by QtCreator 2013-07-12T15:26:20
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleInvoice
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

DESTDIR = ../bin

MOC_DIR = build_tmp
UI_DIR = build_tmp
OBJECTS_DIR = build_tmp
