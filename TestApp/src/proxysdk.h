#ifndef PROXYSDK_H
#define PROXYSDK_H

#include <QObject>
#include <scorocodesdk.h>

class ProxySDK : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool singing READ singing NOTIFY singingChanged)
    Q_PROPERTY(QString tocken READ getToken NOTIFY tokenChanged)
    Q_PROPERTY(QString directoryPath READ directoryPath WRITE setDirectoryPath NOTIFY directoryPathChanged)
    Q_PROPERTY(QString websocketMessage READ websocketMessage NOTIFY websocketMessageChanged)

public:
    explicit ProxySDK(QObject *parent = nullptr);
    ~ProxySDK();

    Q_INVOKABLE void singin();
    Q_INVOKABLE void singup();
    Q_INVOKABLE void singout();
    Q_INVOKABLE void getUserInfo();

    Q_INVOKABLE void uploadFile(const QString filePath, const QString fileName);
    Q_INVOKABLE void downloadFile(const QString fileName);
    Q_INVOKABLE void renameFile(const QString fileName, const QString newFileName);
    Q_INVOKABLE void deleteFile(const QString fileName);


    Q_INVOKABLE void setDirectoryPath(const QString folderName);
    Q_INVOKABLE void getFolderInfo(const QString folderName = ".");
    Q_INVOKABLE void renameDirectoryPath(const QString folderName, const QString newFolderName);
    Q_INVOKABLE void deleteDirectory(const QString folderName = ".");


    Q_INVOKABLE void getRecordList(const QString &type, const QString &db_name, const QString &schema, const QString &table/*, QVariantMap<QString, QString> additional = nullptr*/);
    Q_INVOKABLE void getRecordById(const QString &type, const QString &db_name, const QString &schema, const QString &table, const QString &record_id);
    Q_INVOKABLE void insertRecord(const QString &type, const QString &db_name, const QString &schema, const QString &table, const QString &payload);
    Q_INVOKABLE void updateRecord(const QString &type, const QString &db_name, const QString &schema, const QString &table, const QString &record_id, const QString &payload);
    Q_INVOKABLE void deleteRecord(const QString &type, const QString &db_name, const QString &schema, const QString &table, const QString &record_id);

    Q_INVOKABLE void on(const QString &command);
    Q_INVOKABLE void off(const QString &command);
    Q_INVOKABLE void once(const QString &command);



    bool singing() { return m_singing; }
    QString getToken() { return m_token; }
//    QString filePath() { return m_filePath; }
    QString directoryPath() { return m_directoryPath; }
    QString websocketMessage() { return m_websocketMessage; }

signals:
//    void singinDone(int errorCode, QString data);
    void singingChanged(bool singing);
    void tokenChanged(QString data);
    void directoryPathChanged(QString data);
    void websocketMessageChanged(QString data);

private slots:
    void singinDone(int errorCode, QJsonDocument data);
//    void foldersList(int errorCode, QJsonDocument data);

private:
    void init();

private:
    ScorocodeSDK *sdk;
    QSslConfiguration m_sslConfig;

    Auth *auth;
    Database *database;
    Files *files;
    Folders *folders;
    WebSocket *websocket;

    QString m_token;
//    QString m_filePath;
    QString m_directoryPath;
    QString m_websocketMessage;

    bool m_singing = false;
};

#endif // PROXYSDK_H
