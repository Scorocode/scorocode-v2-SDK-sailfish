#pragma once

#include <QObject>
#include <QJsonDocument>

#include "../Utils/networkrequest.h"

class Auth : public QObject
{
    Q_OBJECT
public:
    explicit Auth(QString baseUrl, QObject *parent = nullptr);

    /*!
     * \brief signin
     * \param email
     * \param password
     */
    void signin(const QString &email, const QString &password);

    /*!
     * \brief signup
     * \param email
     * \param password
     */
    void signup(const QString &email, const QString &password);

    /*!
     * \brief signout
     * \param token
     */
    void signout(const QString &token);

    /*!
     * \brief refreshSession
     * \param token
     */
    void refreshSession(const QString &token);

    /*!
     * \brief getUser
     * \param token
     */
    void getUser(const QString &token);

    /*!
     * \brief confirmEmail
     * \param verificationCode
     */
    void confirmEmail(const QString &verificationCode);

signals:
    void signinDone(int errorCode, QJsonDocument data);
    void signupDone(int errorCode, QJsonDocument data);
    void signoutDone(int errorCode, QJsonDocument data);
    void refreshSessionDone(int errorCode, QJsonDocument data);
    void getUserDone(int errorCode, QJsonDocument data);
    void confirmEmailDone(int errorCode, QJsonDocument data);
    void networkError(int errorCode);

public slots:

private:
    QString m_baseUrl;
    NetworkRequest *m_request;
};

// AUTH_H
