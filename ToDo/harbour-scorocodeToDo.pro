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

# The name of your application
TARGET = harbour-scorocodetodo

CONFIG += sailfishapp
QT += websockets

SOURCES += src/harbour-scorocodeToDo.cpp \
src/proxysdk.cpp

HEADERS += src/proxysdk.h

PROJECT_ROOT_PATH = $${_PRO_FILE_PWD_}/../

include(../ScorocodeSDK.pri)

DISTFILES += qml/harbour-scorocodetodo.qml \
    qml/cover/CoverPage.qml \
    rpm/harbour-scorocodeToDo.changes.in \
    rpm/harbour-scorocodeToDo.changes.run.in \
    rpm/harbour-scorocodeToDo.spec \
    rpm/harbour-scorocodeToDo.yaml \
    translations/*.ts \
    qml/pages/RegisterPage.qml \
    qml/pages/TasksListPage.qml \
    qml/pages/AddTaskPage.qml \
    qml/pages/StartPage.qml \
    harbour-scorocodetodo.desktop

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/harbour-scorocodeToDo-ru.ts

STATECHARTS += \
    ApplicationStates.scxml
