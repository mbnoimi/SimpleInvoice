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
        mainwindow.cpp \
    dialogabout.cpp \
    dialognew.cpp \
    dialogsettings.cpp

HEADERS  += mainwindow.h \
    dialogabout.h \
    queries.h \
    dialognew.h \
    dialogsettings.h

FORMS    += mainwindow.ui \
    dialogabout.ui \
    dialognew.ui \
    dialogsettings.ui

unix {
    DESTDIR = ../bin/lin
    MOC_DIR = build_tmp_lin
    UI_DIR = build_tmp_lin
    OBJECTS_DIR = build_tmp_lin
    RCC_DIR = build_tmp_lin
}
win32 {
    DESTDIR = ../bin/win32
    MOC_DIR = build_tmp_win
    UI_DIR = build_tmp_win
    OBJECTS_DIR = build_tmp_win
    RCC_DIR = build_tmp_win
}

RESOURCES += \
    res.qrc

OTHER_FILES += \
    ../tmp/Selection_002.jpg \
    ../tmp/Selection_003.jpg \
    ../tmp/Selection_001.jpg \
    queries.sql \
    langs/en.ts \
    langs/ar.ts

TRANSLATIONS += ./langs/ar.ts \
                ./langs/en.ts
