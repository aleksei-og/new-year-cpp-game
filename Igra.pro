#-------------------------------------------------
#
# Project created by QtCreator 2015-09-26T21:07:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TargetMotion
TEMPLATE = app


SOURCES += main.cpp\
    menu.cpp \
        widget.cpp \
    triangle.cpp \
    customscene.cpp \
    bullet.cpp \
    target.cpp \
    sprite.cpp

HEADERS  += widget.h \
    menu.h \
    triangle.h \
    customscene.h \
    bullet.h \
    target.h \
    sprite.h

FORMS    += widget.ui

RESOURCES += \
    resources/cursor.qrc \
    resources/sprites.qrc
