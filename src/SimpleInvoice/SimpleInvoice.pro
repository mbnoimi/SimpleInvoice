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



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../OpenrptRenderer/lib/release/ -lOpenrptRenderer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OpenrptRenderer/lib/debug/ -lOpenrptRenderer
else:unix: LIBS += -L$$PWD/../OpenrptRenderer/lib/ -lOpenrptRenderer

INCLUDEPATH += $$PWD/../OpenrptRenderer
DEPENDPATH += $$PWD/../OpenrptRenderer

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../OpenrptRenderer/lib/release/OpenrptRenderer.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../OpenrptRenderer/lib/debug/OpenrptRenderer.lib
else:unix: PRE_TARGETDEPS += $$PWD/../OpenrptRenderer/lib/libOpenrptRenderer.a
