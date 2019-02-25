#-------------------------------------------------
#
# Project created by anenash
#
#-------------------------------------------------

QT -= gui
QT += network
QT += websockets

VERSION = 0.1.0
QMAKE_TARGET_COPYRIGHT = (c) Scorocode

TARGET = ScorocodeSDK
TEMPLATE = lib
CONFIG += staticlib

PROJECT_ROOT_PATH = $${_PRO_FILE_PWD_}/

include(ScorocodeSDK.pri)

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


unix {
    target.path = /usr/lib
    INSTALLS += target
}
