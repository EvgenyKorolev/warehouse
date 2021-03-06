#-------------------------------------------------
#
# Project created by QtCreator 2018-11-12T17:53:41
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = warehouse
TEMPLATE = app
MOC_DIR = moc
OBJECTS_DIR = obj
UI_DIR = ui
RCC_DIR = rcc
DESTDIR = out

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/persisted_object.cpp \
    src/lst_model.cpp \
    src/lst_view.cpp \
    src/settings.cpp \
    src/proxy_data.cpp \
    src/functions.cpp \
    src/editor_object.cpp \
    src/editor_hollydays.cpp \
    src/filtr.cpp \
    src/yes_no.cpp \
    src/delegats.cpp \
    src/server.cpp

HEADERS += \
    src/mainwindow.h \
    src/persisted_object.h \
    src/lst_model.h \
    src/lst_view.h \
    src/settings.h \
    src/proxy_data.h \
    src/functions.h \
    src/editor_object.h \
    src/editor_hollydays.h \
    src/filtr.h \
    src/yes_no.h \
    src/delegats.h \
    src/server.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

win32:{
    RC_ICONS = $$PWD/images/warehouse.ico
    VERSION = 0.9.97
    QMAKE_TARGET_PRODUCT = warehouse
    QMAKE_TARGET_DESCRIPTION = Program werehouse
    QMAKE_TARGET_COPYRIGHT = Evgeny Korolev E-mail: root@kyrych.ru
}
