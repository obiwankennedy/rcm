#-------------------------------------------------
#
# Project created by QtCreator 2014-05-20T10:29:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rcm
TEMPLATE = app
include(preferences/preferences.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    gamemaster.cpp \
    game.cpp \
    gamemodel.cpp \
    gamemasterdialog.cpp \
    gamedialog.cpp \
    gamemastermodel.cpp \
    scenario.cpp \
    scenariomodel.cpp \
    gameeditordelegate.cpp \
    scenariomanager.cpp \
    customerview.cpp

HEADERS  += mainwindow.h \
    gamemaster.h \
    game.h \
    serializable.h \
    gamemodel.h \
    gamemasterdialog.h \
    gamedialog.h \
    gamemastermodel.h \
    scenario.h \
    scenariomodel.h \
    gameeditordelegate.h \
    scenariomanager.h \
    customerview.h

FORMS    += mainwindow.ui \
    gamemasterdialog.ui \
    gamedialog.ui \
    customerview.ui
