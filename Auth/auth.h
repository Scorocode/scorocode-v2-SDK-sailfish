#pragma once

#include <QObject>
#include <QJsonDocument>

#include "Utils/networkrequest.h"

class Auth : public QObject
{
    Q_OBJECT
public:
    explicit Auth(QString baseUrl, QObject *parent = nullptr);

    /*!
     * \brief signin - open new session
     * \param email
     * \param password
     */
    void signin(const QString &email, const QString &password);

    /*!
     * \brief signup - register new user
     * \param email
     * \param password
     */
    void signup(const QString &email, const QString &password);

    /*!
     * \brief signout - close current session
     * \param token
     */
    void signout(const QString &token);

    /*!
     * \brief refreshSession - refresh token of session
     * \param token
     */
    void refreshSession(const QString &token);

    /*!
     * \brief getUser - get user information
     * \param token
     */
    void getUser(const QString &token);

    /*!
     * \brief confirmEmail
     * \param verificationCode
     */
    void confirmEmail(const QString &verificationCode);

    enum class AuthError
    {
        NoError = 0,
        EmailIsEmpty,
        PasswordIsEmpty,
        EmailFormatError,
        TokenIsEmpty,
        VerificationcodeIsEmpty
    };

signals:
    void signinDone(int errorCode, QJsonDocument data);
    void signupDone(int errorCode, QJsonDocument data);
    void signoutDone(int errorCode, QJsonDocument data);
    void refreshSessionDone(int errorCode, QJsonDocument data);
    void getUserDone(int errorCode, QJsonDocument data);
    void confirmEmailDone(int errorCode, QJsonDocument data);
    void authError(Auth::AuthError errorCode);
    void networkError(int errorCode);

public slots:

private:
    QString m_baseUrl;
    NetworkRequest *m_request;
};

// AUTH_H
