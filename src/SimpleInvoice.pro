#-------------------------------------------------
#
# Project created by QtCreator 2013-07-12T15:26:20
#
#-------------------------------------------------

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = SimpleInvoice
TEMPLATE = app

include( OpenRPT/global.pri )

INCLUDEPATH += OpenRPT/OpenRPT/common \
OpenRPT/OpenRPT/Dmtx_Library \
OpenRPT/OpenRPT/renderer \
OpenRPT/OpenRPT/renderapp


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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/OpenRPT/lib/release/ -lcommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/OpenRPT/lib/debug/ -lcommon
else:unix: LIBS += -L$$PWD/OpenRPT/lib/ -lcommon

INCLUDEPATH += $$PWD/OpenRPT
DEPENDPATH += $$PWD/OpenRPT

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/OpenRPT/lib/release/common.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/OpenRPT/lib/debug/common.lib
else:unix: PRE_TARGETDEPS += $$PWD/OpenRPT/lib/libcommon.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/OpenRPT/lib/release/ -lDmtx_Library
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/OpenRPT/lib/debug/ -lDmtx_Library
else:unix: LIBS += -L$$PWD/OpenRPT/lib/ -lDmtx_Library

INCLUDEPATH += $$PWD/OpenRPT
DEPENDPATH += $$PWD/OpenRPT

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/OpenRPT/lib/release/Dmtx_Library.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/OpenRPT/lib/debug/Dmtx_Library.lib
else:unix: PRE_TARGETDEPS += $$PWD/OpenRPT/lib/libDmtx_Library.a


