#-------------------------------------------------
#
# Project created by QtCreator 2013-07-12T15:26:20
#
#-------------------------------------------------

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

!android {
    greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
    SOURCES += openrptrenderer.cpp
    HEADERS  += openrptrenderer.h
}

TARGET = SimpleInvoice
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    dialogabout.cpp \
    dialognew.cpp \
    dialogsettings.cpp \

HEADERS  += mainwindow.h \
    dialogabout.h \
    queries.h \
    dialognew.h \
    dialogsettings.h

FORMS    += mainwindow.ui \
    dialogabout.ui \
    dialognew.ui \
    dialogsettings.ui

linux {
    !android:DESTDIR = ../../bin/lin
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
###### static build ######
    QMAKE_LFLAGS += -static -static-libgcc -static-libstdc++ -lpthread
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


###################################### OpenRPT #############################################

!android {
    include( ../openrpt/global.pri )
    LIBS += -L../openrpt/lib -lrenderer -lcommon -lDmtx_Library
    win32-msvc* {
      PRE_TARGETDEPS += ../openrpt/lib/common.lib   \
                        ../openrpt/lib/renderer.lib
    } else {
      PRE_TARGETDEPS += ../openrpt/lib/libcommon.a   \
                        ../openrpt/lib/librenderer.a
    }
}
