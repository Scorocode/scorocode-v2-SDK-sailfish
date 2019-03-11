#include "proxysdk.h"

#include <QJsonObject>
#include <QDebug>

ProxySDK::ProxySDK(QObject *parent) : QObject(parent)
{
// Set AppId
    sdk = ScorocodeSDK::initApp("AppId", m_sslConfig);
    if (sdk)
    {
        init();
    }
}

ProxySDK::~ProxySDK()
{
    if (!m_token.isNull())
    {
        auth->signout(m_token);
    }
}

void ProxySDK::singin()
{
    QString user = "email@email.com";
    QString pass = "password";
    auth->signin(user, pass);
    m_singing = true;
    emit singingChanged(m_singing);
    connect(auth, &Auth::signinDone, this, &ProxySDK::singinDone);
}

void ProxySDK::singup()
{
    QString user = "email@email.com";
    QString pass = "password";
    auth->signup(user, pass);
    m_singing = true;
    emit singingChanged(m_singing);
    connect(auth, &Auth::signupDone, this, &ProxySDK::singinDone);
}

void ProxySDK::singout()
{
    qDebug() << "Singout" << m_token;
    if (!m_token.isNull())
    {
        auth->signout(m_token);
        m_token = nullptr;
    }
}

void ProxySDK::getUserInfo()
{
    if (!m_token.isNull())
    {
        qDebug() << "Get user info" << m_token;
        auth->getUser(m_token);
        connect(auth, &Auth::getUserDone, this, [this](int errorCode, QJsonDocument data){
            qDebug().noquote() << "error code" << errorCode << data.toJson();
        });
    }
}

void ProxySDK::uploadFile(const QString filePath, const QString fileName)
{
    qDebug() << "Upload file" << fileName;
    if (!m_token.isNull())
    {
        files->fileUpload(filePath, fileName);
        connect(files, &Files::fileUploadDone, this, [this](int errorCode, QJsonDocument data){
            qDebug().noquote() << "error code" << errorCode << data.toJson();
        });
    }
}

void ProxySDK::downloadFile(const QString fileName)
{
    qDebug() << "Download file" << fileName;
    if (!m_token.isNull())
    {
        files->fileDownload(fileName);
        connect(files, &Files::fileDownloadDone, this, [this](int errorCode, QJsonDocument data){
            qDebug().noquote() << "error code" << errorCode << data.toJson();
        });
    }
}

void ProxySDK::renameFile(const QString fileName, const QString newFileName)
{
    qDebug() << "Rename file" << fileName;
    if (!m_token.isNull())
    {
        files->fileRename(fileName, newFileName);
        connect(files, &Files::fileRenameDone, this, [this](int errorCode, QJsonDocument data){
            qDebug().noquote() << "error code" << errorCode << data.toJson();
        });
    }
}

void ProxySDK::deleteFile(const QString fileName)
{
    qDebug() << "Delete file" << fileName;
    if (!m_token.isNull())
    {
        files->fileDelete(fileName);
        connect(files, &Files::fileDeleteDone, this, [this](int errorCode, QJsonDocument data){
            qDebug().noquote() << "error code" << errorCode << data.toJson();
        });
    }
}

void ProxySDK::setDirectoryPath(const QString folderName)
{
    qDebug() << "Create folder" << folderName << "token" << m_token;
    if (!m_token.isNull())
    {
        qDebug() << folderName;
        folders->folderCreate(folderName);
        connect(folders, &Folders::folderCreateDone, this, [this](int errorCode, QJsonDocument data){
            qDebug().noquote() << "error code" << errorCode << data.toJson();
        });
    }
}

void ProxySDK::getFolderInfo(const QString folderName)
{
    qDebug() << "folders" << folderName << "token" << m_token;
    if (!m_token.isNull())
    {
        qDebug() << folderName;
        folders->folderRead(folderName);
        connect(folders, &Folders::folderReadDone, this, [this](int errorCode, QJsonDocument data){
            qDebug().noquote() << "error code" << errorCode << data.toJson();
        });
    }
}

void ProxySDK::renameDirectoryPath(const QString folderName, const QString newFolderName)
{
    qDebug() << "Rename folder" << folderName << "to" << newFolderName;
    if (!m_token.isNull())
    {
        qDebug() << "newPath" << folderName;

        folders->folderRename(folderName, newFolderName);
        connect(folders, &Folders::folderRenameDone, this, [this](int errorCode, QJsonDocument data){
            qDebug().noquote() << "error code" << errorCode << data.toJson();
        });
    }
}

void ProxySDK::deleteDirectory(const QString folderName)
{
    qDebug() << "Delete folder" << folderName << "token" << m_token;
    if (!m_token.isNull())
    {
        qDebug() << folderName;
        folders->folderDelete(folderName);
        connect(folders, &Folders::folderDeleteDone, this, [this](int errorCode, QJsonDocument data){
            qDebug().noquote() << "error code" << errorCode << data.toJson();
        });
    }
}

void ProxySDK::getRecordList(const QString &type, const QString &db_name, const QString &schema, const QString &table/*, QVariantMap<QString, QString> additional*/)
{
    qDebug() << "get record: db type" << type << "name" << db_name << "schema name" << schema << "table name" << table;
    if (!m_token.isNull())
    {
//        if(additional)
//        {
//            database->getRecordList(type, db_name, schema, table, additional);
//        }
//        else
//        {
            database->getRecordList(type, db_name, schema, table);
//        }
        connect(database, &Database::getRecordListDone, this, [this](int errorCode, QJsonDocument data){
            qDebug().noquote() << "error code" << errorCode << data.toJson();
        });
    }
}

void ProxySDK::getRecordById(const QString &type, const QString &db_name, const QString &schema, const QString &table, const QString &record_id)
{
    qDebug() << "get record: db type" << type << "name" << db_name << "schema name" << schema << "table name" << table << "record_id" << record_id;
    if (!m_token.isNull())
    {
        database->getRecordById(type, db_name, schema, table, record_id);
        connect(database, &Database::getRecordByIdDone, this, [this](int errorCode, QJsonDocument data){
            qDebug().noquote() << "error code" << errorCode << data.toJson();
        });
    }
}

void ProxySDK::insertRecord(const QString &type, const QString &db_name, const QString &schema, const QString &table, const QString & payload)
{
    qDebug() << "insert record: db type" << type << "name" << db_name << "schema name" << schema << "table name" << table << "payload" << payload;
    if (!m_token.isNull())
    {
        database->insertRecord(type, db_name, schema, table, payload);
        connect(database, &Database::insertRecordDone, this, [this](int errorCode, QJsonDocument data){
            qDebug().noquote() << "error code" << errorCode << data.toJson();
        });
    }
}

void ProxySDK::updateRecord(const QString &type, const QString &db_name, const QString &schema, const QString &table, const QString &record_id, const QString &payload)
{
    qDebug() << "update record: db type" << type << "name" << db_name << "schema name" << schema << "table name" << table << "record_id" << record_id << "payload" << payload;
    if (!m_token.isNull())
    {
        database->updateRecord(type, db_name, schema, table, record_id, payload);
        connect(database, &Database::updateRecordDone, this, [this](int errorCode, QJsonDocument data){
            qDebug().noquote() << "error code" << errorCode << data.toJson();
        });
    }
}

void ProxySDK::deleteRecord(const QString &type, const QString &db_name, const QString &schema, const QString &table, const QString &record_id)
{
    qDebug() << "delete record: db type" << type << "name" << db_name << "schema name" << schema << "table name" << table;
    if (!m_token.isNull())
    {
        database->deleteRecord(type, db_name, schema, table, record_id);
        connect(database, &Database::deleteRecordDone, this, [this](int errorCode, QJsonDocument data){
            qDebug().noquote() << "error code" << errorCode << data.toJson();
        });
    }
}

void ProxySDK::on(const QString &command)
{
    websocket->on(command);
}

void ProxySDK::off(const QString &command)
{
    websocket->off(command);
}

void ProxySDK::once(const QString &command)
{
    websocket->once(command);
}

void ProxySDK::singinDone(int errorCode, QJsonDocument data)
{
    qDebug().noquote() << errorCode << data.toJson();
    if (0 == errorCode)
    {
        QJsonObject object = data.object();
        qDebug().noquote() << object.keys();
        m_token = object.value("token").toString();
        qDebug() << "got token" << m_token;
        m_singing = false;
        folders->setToken(m_token);
        files->setToken(m_token);
        database->setToken(m_token);
        emit singingChanged(m_singing);
        emit tokenChanged(data.toJson());
    }
}

void ProxySDK::init()
{
    auth = sdk->auth();
    database = sdk->database();
    files = sdk->files();
    folders = sdk->folders();
    websocket = sdk->websocket();

    connect(sdk, &ScorocodeSDK::networkError, this, [this](int errorCode){
        qDebug() << "error code" << errorCode;
        m_singing = false;
        emit singingChanged(m_singing);
    });

    connect(websocket, &WebSocket::messageReceived, this, [this](QJsonDocument message){
        QString data = message.toJson();
        m_websocketMessage = data;
        emit websocketMessageChanged(data);
    });
    connect(websocket, &WebSocket::socketConnected, this, [this](QJsonDocument message){
        QString data = message.toJson();
        m_websocketMessage = data;
        emit websocketMessageChanged(data);
    });
}
