
message($$PROJECT_ROOT_PATH)
#BUILD_PATH = $${PROJECT_ROOT_PATH}/build/$${TARGET}/

HEADERS += \
    $$PROJECT_ROOT_PATH/scorocodesdk.h \
    $$PROJECT_ROOT_PATH/Auth/auth.h \
    $$PROJECT_ROOT_PATH/DB/database.h \
    $$PROJECT_ROOT_PATH/Filesystem/files.h \
    $$PROJECT_ROOT_PATH/Filesystem/folders.h \
    $$PROJECT_ROOT_PATH/Utils/networkrequest.h \
    $$PROJECT_ROOT_PATH/Utils/websocket.h \
    $$PWD/Utils/logger.h

SOURCES += \
    $$PROJECT_ROOT_PATH/scorocodesdk.cpp \
    $$PROJECT_ROOT_PATH/Auth/auth.cpp \
    $$PROJECT_ROOT_PATH/DB/database.cpp \
    $$PROJECT_ROOT_PATH/Filesystem/files.cpp \
    $$PROJECT_ROOT_PATH/Filesystem/folders.cpp \
    $$PROJECT_ROOT_PATH/Utils/networkrequest.cpp \
    $$PROJECT_ROOT_PATH/Utils/websocket.cpp \
    $$PWD/Utils/logger.cpp

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
INCLUDEPATH += $$PROJECT_ROOT_PATH
DEPENDPATH += $$PROJECT_ROOT_PATH
