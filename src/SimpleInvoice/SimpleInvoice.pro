#-------------------------------------------------
#
# Project created by QtCreator 2013-07-12T15:26:20
#
#-------------------------------------------------

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

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
    DESTDIR = ../../../bin/lin
    MOC_DIR = build_tmp_lin
    UI_DIR = build_tmp_lin
    OBJECTS_DIR = build_tmp_lin
    RCC_DIR = build_tmp_lin
}
win32 {
    DESTDIR = ../../../bin/win32
    MOC_DIR = build_tmp_win
    UI_DIR = build_tmp_win
    OBJECTS_DIR = build_tmp_win
    RCC_DIR = build_tmp_win
}

RESOURCES += \
    res.qrc

OTHER_FILES += \
    ../../tmp/Selection_002.jpg \
    ../../tmp/Selection_003.jpg \
    ../../tmp/Selection_001.jpg \
    queries.sql

# TODO: Split translation in case of need
TRANSLATIONS += langs/ar.ts \
                langs/en.ts

include( ../openrpt/global.pri )

INCLUDEPATH += ../openrpt/OpenRPT/renderapp
DEPENDPATH += ../openrpt/OpenRPT/renderapp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../openrpt/lib/release/ -lcommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../openrpt/lib/debug/ -lcommon
else:unix: LIBS += -L$$PWD/../openrpt/lib/ -lcommon

INCLUDEPATH += $$PWD/../openrpt/common
DEPENDPATH += $$PWD/../openrpt/common

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../openrpt/lib/release/common.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../openrpt/lib/debug/common.lib
else:unix: PRE_TARGETDEPS += $$PWD/../openrpt/lib/libcommon.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../openrpt/lib/release/ -lDmtx_Library
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../openrpt/lib/debug/ -lDmtx_Library
else:unix: LIBS += -L$$PWD/../openrpt/lib/ -lDmtx_Library

INCLUDEPATH += $$PWD/../openrpt/OpenRPT/Dmtx_Library
DEPENDPATH += $$PWD/../openrpt/OpenRPT/Dmtx_Library

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../openrpt/lib/release/Dmtx_Library.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../openrpt/lib/debug/Dmtx_Library.lib
else:unix: PRE_TARGETDEPS += $$PWD/../openrpt/lib/libDmtx_Library.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../openrpt/lib/release/ -lrenderer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../openrpt/lib/debug/ -lrenderer
else:unix: LIBS += -L$$PWD/../openrpt/lib/ -lrenderer

INCLUDEPATH += $$PWD/../openrpt/OpenRPT/renderer
DEPENDPATH += $$PWD/../openrpt/OpenRPT/renderer

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../openrpt/lib/release/renderer.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../openrpt/lib/debug/renderer.lib
else:unix: PRE_TARGETDEPS += $$PWD/../openrpt/lib/librenderer.a
