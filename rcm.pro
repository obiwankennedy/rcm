#-------------------------------------------------
#
# Project created by QtCreator 2014-05-20T10:29:47
#
#-------------------------------------------------

QT       += core gui xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets qml quick

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
    scenarioitemdelegate.cpp \
    scenarioeditordialog.cpp \
    localisation/localisationview.cpp \
    localisation/tableswizard.cpp \
    localisation/table.cpp \
    localisation/roommodel.cpp \
    localisation/tablemodel.cpp \
    localisation/tableitem.cpp \
    localisation/roomitem.cpp \
    leveldelegateitem.cpp


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
    scenarioitemdelegate.h \
    scenarioeditordialog.h \
    localisation/localisationview.h \
    localisation/tableswizard.h \
    localisation/table.h \
    localisation/roommodel.h \
    localisation/tablemodel.h \
    localisation/tableitem.h \
    localisation/roomitem.h \
    leveldelegateitem.h

FORMS    += mainwindow.ui \
    gamemasterdialog.ui \
    gamedialog.ui \
    customerview.ui \
    scenarioeditordialog.ui \
    localisation/tableswizard.ui

OTHER_FILES += \
    listView.qml

RESOURCES += \
    resources.qrc

## Translation
TRANSLATIONS =  rcm_fr.ts



CODECFORTR = UTF-8

isEmpty(QMAKE_LRELEASE) {
    win32:QMAKE_LRELEASE = $$[QT_INSTALL_BINS]/lrelease.exe
    else:QMAKE_LRELEASE = $$[QT_INSTALL_BINS]/lrelease



}
#isEmpty(QMAKE_LUPDATE) {
#    win32:QMAKE_LRELEASE = $$[QT_INSTALL_BINS]\lupdate.exe
#    else:QMAKE_LRELEASE = $$[QT_INSTALL_BINS]/lupdate
#}
#updateTrans.input = rolisteam.pro
#updateTrans.output= ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}.ts


updateqm.input = TRANSLATIONS
updateqm.output = ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}.qm
updateqm.commands = $$QMAKE_LRELEASE ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}.qm
updateqm.CONFIG += no_link
QMAKE_EXTRA_COMPILERS += updateqm
PRE_TARGETDEPS += compiler_updateqm_make_all
## End of Translation


greaterThan(QT_MAJOR_VERSION, 4) {
message("qt5")
    SOURCES+=customerview.cpp \
    gameimageprovider.cpp

    HEADERS+=customerview.h \
    gameimageprovider.h

DEFINES+=__QT_QUICK_2_
}
