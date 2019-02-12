#-------------------------------------------------
#
# Project created by QtCreator 2014-05-20T10:29:47
#
#-------------------------------------------------

QT       += core gui xml network widgets qml quick

TARGET = rcm
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
UI_DIR = build/ui
RCC_DIR = build/qrc
TEMPLATE = app
include(preferences/preferences.pri)

INCLUDEPATH+=utils\
            model\
            data\
            widget\
            widget/delegate\
            controller

SOURCES += main.cpp\
        mainwindow.cpp \
    data/gamemaster.cpp \
    data/game.cpp \
    model/gamemodel.cpp \
    widget/gamemasterdialog.cpp \
    widget/gamedialog.cpp \
    model/gamemastermodel.cpp \
    data/scenario.cpp \
    model/scenariomodel.cpp \
    widget/delegate/gameeditordelegate.cpp \
    controller/scenariomanager.cpp \
    widget/delegate/scenarioitemdelegate.cpp \
    widget/scenarioeditordialog.cpp \
    localisation/localisationview.cpp \
    localisation/tableswizard.cpp \
    localisation/table.cpp \
    localisation/roommodel.cpp \
    localisation/tablemodel.cpp \
    localisation/tableitem.cpp \
    localisation/roomitem.cpp \
    widget/delegate/leveldelegateitem.cpp \
    widget/playersinformationdialog.cpp \
    widget/playerinformationformdialog.cpp \
    export/abstractexport.cpp \
    export/exportcsv.cpp \
    localisation/rcmmimedata.cpp \
    localisation/scenariolistview.cpp \
    localisation/scenarioitem.cpp \
    utils/idtranslator.cpp


HEADERS  += mainwindow.h \
    data/gamemaster.h \
    data/game.h \
    utils/serializable.h \
    model/gamemodel.h \
    widget/gamemasterdialog.h \
    widget/gamedialog.h \
    model/gamemastermodel.h \
    data/scenario.h \
    model/scenariomodel.h \
    widget/delegate/gameeditordelegate.h \
    controller/scenariomanager.h \
    widget/delegate/scenarioitemdelegate.h \
    widget/scenarioeditordialog.h \
    localisation/localisationview.h \
    localisation/tableswizard.h \
    localisation/table.h \
    localisation/roommodel.h \
    localisation/tablemodel.h \
    localisation/tableitem.h \
    localisation/roomitem.h \
    widget/delegate/leveldelegateitem.h \
    widget/playersinformationdialog.h \
    widget/playerinformationformdialog.h \
    export/abstractexport.h \
    export/exportcsv.h \
    localisation/rcmmimedata.h \
    localisation/scenariolistview.h \
    localisation/scenarioitem.h \
    utils/idtranslator.h \
    utils/definesize.h

FORMS    += mainwindow.ui \
    widget/gamemasterdialog.ui \
    widget/gamedialog.ui \
    widget/customerview.ui \
    widget/scenarioeditordialog.ui \
    localisation/tableswizard.ui \
    widget/playersinformationdialog.ui \
    widget/playerinformationformdialog.ui \
    localisation/eventproperties.ui

OTHER_FILES += \
    resources/qml/listView.qml

RESOURCES += \
    resources.qrc

## Translation
TRANSLATIONS =  translation/rcm_fr.ts

CONFIG += c++11

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



SOURCES+=widget/customerview.cpp \
    utils/gameimageprovider.cpp

HEADERS+=widget/customerview.h \
    utils/gameimageprovider.h

