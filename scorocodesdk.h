#pragma once

#include <QBasicTimer>
#include <QTimerEvent>
#include <QSslConfiguration>

#include "Auth/auth.h"
#include "DB/database.h"
#include "Filesystem/files.h"
#include "Filesystem/folders.h"
#include "Utils/websocket.h"

class ScorocodeSDK : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("Author", "Alexander Nenashev")
    Q_CLASSINFO("URL", "https://github.com/Scorocode/scorocode-v2-SDK-sailfish")

    Q_DISABLE_COPY(ScorocodeSDK)

private:
    static ScorocodeSDK *m_instance;

public:

    /*!
     * \brief initApp
     * \param appId
     * \param configuration
     * \param address
     * \return
     */
    static ScorocodeSDK* initApp(const QString &appId, const QSslConfiguration &configuration, const QString address = ".v2.scorocode.ru");

    /*!
     * \brief auth
     * \return
     */
    Auth* auth();

    /*!
     * \brief database
     * \return
     */
    Database* database();

    /*!
     * \brief files
     * \return
     */
    Files* files();

    /*!
     * \brief folders
     * \return
     */
    Folders* folders();

    /*!
     * \brief websocket
     * \return
     */
    WebSocket* websocket();

    /*!
     * \brief getToken
     * \return
     */
    QString getToken() const { return m_token; }

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    ScorocodeSDK();
    ScorocodeSDK(const QString appId, const QSslConfiguration &configuration);
    ScorocodeSDK(const QString appId, const QSslConfiguration &configuration, const QString address = ".v2.scorocode.ru");
    ScorocodeSDK(const ScorocodeSDK &&) = delete;
    ScorocodeSDK& operator =(ScorocodeSDK &) = delete;
    ScorocodeSDK& operator =(ScorocodeSDK &&) = delete;

signals:
    void tokenExpaired();
    void appError(int errorCode);
    void networkError(int errorCode);

private slots:
    void tokenTimer(int errorCode, QJsonDocument data);

private:
    QString m_appId;
    QString m_baseUrl = "https://";

    QString m_token;
    QBasicTimer m_timer;
    QSslConfiguration *m_sslConfiguration = nullptr;

    Auth *m_auth = nullptr;
    Database *m_database = nullptr;
    Files *m_files = nullptr;
    Folders *m_folders = nullptr;
    WebSocket *m_socket = nullptr;
};

// SCOROCODESDK_H
