# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

QT += network
QT += websockets

# The name of your application
TARGET = ScorocodeTestApp

CONFIG += sailfishapp

SOURCES += src/ScorocodeTestApp.cpp \
    src/proxysdk.cpp


PROJECT_ROOT_PATH = $${_PRO_FILE_PWD_}/../

include(../ScorocodeSDK.pri)

DISTFILES += qml/ScorocodeTestApp.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    rpm/ScorocodeTestApp.changes.in \
    rpm/ScorocodeTestApp.changes.run.in \
    rpm/ScorocodeTestApp.spec \
    rpm/ScorocodeTestApp.yaml \
    translations/*.ts \
    ScorocodeTestApp.desktop \
    qml/pages/DatabaseCheck.qml \
    qml/pages/WebSocket.qml \
    qml/pages/Files.qml

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

ScorocodeTestApp.depends = ScorocodeSDK

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/ScorocodeTestApp-de.ts

unix:!macx: LIBS += -L$$PROJECT_ROOT_PATH/lib/

HEADERS += \
    src/proxysdk.h

