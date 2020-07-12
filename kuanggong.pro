#-------------------------------------------------
#
# Project created by QtCreator 2020-07-05T09:57:30
#
#-------------------------------------------------

QT       += core gui multimedia
QT       += core gui
QT += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kuanggong
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainscene.cpp \
    mybutton.cpp \
    secondscene.cpp \
    item.cpp \
    mianer.cpp \
    map.cpp \
    playscene.cpp

HEADERS += \
        mainscene.h \
    mybutton.h \
    secondscene.h \
    item.h \
    mianer.h \
    map.h \
    playscene.h

FORMS += \
        mainscene.ui \
    playscene.ui

RESOURCES += \
    res.qrc
CONFIG+=resources_big

DISTFILES+=\
music/bgm.mp3\

RC_ICONS += myico.ico
