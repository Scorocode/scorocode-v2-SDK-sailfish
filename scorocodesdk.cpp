#include "scorocodesdk.h"
#include "Utils/logger.h"

#include <QSslConfiguration>
#include <QJsonObject>
#include <QJsonValue>

ScorocodeSDK *ScorocodeSDK::m_instance = nullptr;

ScorocodeSDK *ScorocodeSDK::initApp(const QString &appId, const QSslConfiguration &configuration, const QString address)
{
    if (!m_instance)
    {
//        qDebug() << "Logger instanace";
//        logger::initLogging();
        m_instance = new ScorocodeSDK(appId, configuration, address);
    }

    return m_instance;
}

ScorocodeSDK::ScorocodeSDK(const QString appId, const QSslConfiguration &configuration) :
    m_appId(appId)
{
    // Needed to enable logging to syslog or journald.
    qputenv("QT_LOGGING_TO_CONSOLE", QByteArray("0"));

    m_sslConfiguration = new QSslConfiguration(configuration);

    m_baseUrl += m_appId + ".v2.scorocode.ru/";
    if (!m_socket)
    {
        QUrl url = "wss://ws-" + m_appId + ".v2.scorocode.ru";
        m_socket = new WebSocket(url);
    }
}

ScorocodeSDK::ScorocodeSDK(const QString appId, const QSslConfiguration &configuration, const QString address):
    m_appId(appId)
{
    // Needed to enable logging to syslog or journald.
    qputenv("QT_LOGGING_TO_CONSOLE", QByteArray("0"));

    m_sslConfiguration = new QSslConfiguration(configuration);

    m_baseUrl += m_appId + address + "/";
    if (!m_socket)
    {
        QUrl url = "wss://ws-" + m_appId + address;
        m_socket = new WebSocket(url);
    }
}

Auth *ScorocodeSDK::auth()
{
    if (!m_auth)
    {
        m_auth = new Auth(m_baseUrl);

        connect(m_auth, &Auth::signinDone, this, &ScorocodeSDK::tokenTimer);
        connect(m_auth, &Auth::networkError, this, &ScorocodeSDK::networkError);
    }
    return m_auth;
}

Database *ScorocodeSDK::database()
{
    if (!m_database)
    {
        m_database = new Database(m_baseUrl);
    }

    return m_database;
}

Files *ScorocodeSDK::files()
{
    if (!m_files)
    {
        m_files = new Files(m_baseUrl);
    }

    return m_files;
}

Folders *ScorocodeSDK::folders()
{
    if (!m_folders)
    {
        m_folders = new Folders(m_baseUrl);
    }

    return m_folders;
}

WebSocket *ScorocodeSDK::websocket()
{
    return m_socket;
}

void ScorocodeSDK::tokenTimer(int errorCode, QJsonDocument data)
{
    if (0 == errorCode)
    {
        QJsonObject object = data.object();
        if (object.contains("token"))
        {
            QJsonValue value = object.value("token");
            m_token = value.toString();
            m_timer.start(900000, this);
        }
    }
}

void ScorocodeSDK::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_timer.timerId())
    {
        m_timer.stop();
        emit tokenExpaired();
    }
}
