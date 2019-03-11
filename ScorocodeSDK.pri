
message($$PROJECT_ROOT_PATH)

HEADERS += \
    $$PROJECT_ROOT_PATH/scorocodesdk.h \
    $$PROJECT_ROOT_PATH/Auth/auth.h \
    $$PROJECT_ROOT_PATH/DataModels/accountuserpublicdata.h \
    $$PROJECT_ROOT_PATH/DB/database.h \
    $$PROJECT_ROOT_PATH/Filesystem/files.h \
    $$PROJECT_ROOT_PATH/Filesystem/folders.h \
    $$PROJECT_ROOT_PATH/Utils/networkrequest.h \
    $$PROJECT_ROOT_PATH/Utils/websocket.h \
    $$PROJECT_ROOT_PATH/Utils/logger.h \
    $$PROJECT_ROOT_PATH/Utils/filemanager.h

SOURCES += \
    $$PROJECT_ROOT_PATH/scorocodesdk.cpp \
    $$PROJECT_ROOT_PATH/Auth/auth.cpp \
    $$PROJECT_ROOT_PATH/DataModels/accountuserpublicdata.cpp \
    $$PROJECT_ROOT_PATH/DB/database.cpp \
    $$PROJECT_ROOT_PATH/Filesystem/files.cpp \
    $$PROJECT_ROOT_PATH/Filesystem/folders.cpp \
    $$PROJECT_ROOT_PATH/Utils/networkrequest.cpp \
    $$PROJECT_ROOT_PATH/Utils/websocket.cpp \
    $$PROJECT_ROOT_PATH/Utils/logger.cpp \
    $$PROJECT_ROOT_PATH/Utils/filemanager.cpp

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
INCLUDEPATH += $$PROJECT_ROOT_PATH
DEPENDPATH += $$PROJECT_ROOT_PATH
