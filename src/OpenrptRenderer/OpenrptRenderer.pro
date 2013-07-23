#-------------------------------------------------
#
# Project created by QtCreator 2013-07-22T16:24:11
#
#-------------------------------------------------

QT       += widgets sql xml xmlpatterns

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TARGET = OpenrptRenderer
TEMPLATE = lib
CONFIG += staticlib

SOURCES += openrptrenderer.cpp

HEADERS += openrptrenderer.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

unix {
    DESTDIR = ../../bin/lin
    MOC_DIR = build_tmp_lin
    UI_DIR = build_tmp_lin
    OBJECTS_DIR = build_tmp_lin
    RCC_DIR = build_tmp_lin
}
win32 {
    DESTDIR = ../../bin/win32
    MOC_DIR = build_tmp_win
    UI_DIR = build_tmp_win
    OBJECTS_DIR = build_tmp_win
    RCC_DIR = build_tmp_win
}

###################################### OpenRPT #############################################33
include( ../openrpt/global.pri )

DESTDIR = lib


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
