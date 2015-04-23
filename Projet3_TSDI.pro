#-------------------------------------------------
#
# Project created by QtCreator 2015-03-25T15:19:05
#
#-------------------------------------------------
QT += widgets sql webkitwidgets


TARGET = projet3_trading

TEMPLATE = app
CONFIG += qt release windows

SOURCES += main.cpp \
    principal.cpp \
    coupledevise.cpp \
    dialogchoixdevises.cpp \
    dialogueoptions.cpp \
    dialogueintervalletemps.cpp \
    dialoguesimulationtransactions.cpp \
    dialoguetransactionautomatique.cpp

HEADERS += \
    principal.h \
    coupledevise.h \
    dialogchoixdevises.h \
    dialogueoptions.h \
    dialogueintervalletemps.h \
    dialoguesimulationtransactions.h \
    dialoguetransactionautomatique.h \
    cssstylesheet.h \
    xmlstream.h

RESOURCES += \
    ressources.qrc
