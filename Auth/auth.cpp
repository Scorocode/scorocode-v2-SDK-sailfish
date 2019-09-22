#include "auth.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QUrl>
#include <QRegExp>

#include <QDebug>

Auth::Auth(QString baseUrl, QObject *parent) :
    QObject(parent)
{
    m_baseUrl = baseUrl + "sc/auth/api/v2/";
    m_request = new NetworkRequest();
    connect(m_request, &NetworkRequest::error, this, &Auth::networkError);
}

void Auth::signin(const QString &email, const QString &password)
{
    if (email.isEmpty())
    {
        emit authError(Auth::AuthError::EmailIsEmpty);
        return;
    }
    if (password.isEmpty())
    {
        emit authError(Auth::AuthError::PasswordIsEmpty);
        return;
    }
    qDebug() << "email" << email;

    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);

    if (!mailREX.exactMatch(email))
    {
        emit authError(Auth::AuthError::EmailFormatError);
        return;
    }

    QUrl url = m_baseUrl + "signin";

    qDebug() << "url" << url;

    QJsonObject tmp;
    tmp.insert("email", email);
    tmp.insert("password", password);
    QJsonDocument body(tmp);

    qDebug() << "json" << body;
    m_request->postRequest(url, body.toJson());

    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::signupDone);
    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::signoutDone);
    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::confirmEmailDone);
    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::getUserDone);
    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::refreshSessionDone);
    connect(m_request, &NetworkRequest::replyPost, this, &Auth::signinDone);
}

void Auth::signup(const QString &email, const QString &password)
{
    if (email.isEmpty())
    {
        emit authError(Auth::AuthError::EmailIsEmpty);
        return;
    }
    if (password.isEmpty())
    {
        emit authError(Auth::AuthError::PasswordIsEmpty);
        return;
    }
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);

    if (!mailREX.exactMatch(email))
    {
        emit authError(Auth::AuthError::EmailFormatError);
        return;
    }
    QUrl url = m_baseUrl + "signup";

    QJsonObject tmp;
    tmp.insert("email", email);
    tmp.insert("password", password);
    QJsonDocument body(tmp);

    m_request->postRequest(url, body.toJson());
    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::signoutDone);
    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::confirmEmailDone);
    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::getUserDone);
    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::refreshSessionDone);
    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::signinDone);
    connect(m_request, &NetworkRequest::replyPost, this, &Auth::signupDone);
}

void Auth::signout(const QString &token)
{
    if (token.isEmpty())
    {
        emit authError(Auth::AuthError::TokenIsEmpty);
        return;
    }

    QUrl url = m_baseUrl + "signout";
    QJsonObject tmp;
    tmp.insert("token", token);
    QJsonDocument body(tmp);
    m_request->postRequest(url, body.toJson());

    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::signinDone);
    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::signupDone);
    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::refreshSessionDone);
    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::confirmEmailDone);
    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::getUserDone);
    connect(m_request, &NetworkRequest::replyPost, this, &Auth::signoutDone);
}

void Auth::refreshSession(const QString &token)
{
    if (token.isEmpty())
    {
        emit authError(Auth::AuthError::TokenIsEmpty);
        return;
    }

    QUrl url = m_baseUrl + "refresh";
    QJsonObject tmp;
    tmp.insert("token", token);
    QJsonDocument body(tmp);
    m_request->postRequest(url, body.toJson());

    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::signinDone);
    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::signupDone);
    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::signoutDone);
    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::confirmEmailDone);
    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::getUserDone);
    connect(m_request, &NetworkRequest::replyPost, this, &Auth::refreshSessionDone);
}

void Auth::getUser(const QString &token)
{
    if (token.isEmpty())
    {
        emit authError(Auth::AuthError::TokenIsEmpty);
        return;
    }

    QUrl url = m_baseUrl + "userinfo";
    QJsonObject tmp;
    tmp.insert("token", token);
    QJsonDocument body(tmp);
    m_request->postRequest(url, body.toJson());

    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::signinDone);
    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::signupDone);
    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::signoutDone);
    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::refreshSessionDone);
    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::confirmEmailDone);
    connect(m_request, &NetworkRequest::replyPost, this, &Auth::getUserDone);
}

void Auth::confirmEmail(const QString &verificationCode)
{
    if (verificationCode.isEmpty())
    {
        emit authError(Auth::AuthError::VerificationcodeIsEmpty);
        return;
    }

    QUrl url = m_baseUrl + "verify";
    QJsonObject tmp;
    tmp.insert("token", verificationCode);
    QJsonDocument body(tmp);
    m_request->postRequest(url, body.toJson());

    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::signinDone);
    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::signupDone);
    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::signoutDone);
    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::refreshSessionDone);
    disconnect(m_request, &NetworkRequest::replyPost, this, &Auth::getUserDone);
    connect(m_request, &NetworkRequest::replyPost, this, &Auth::confirmEmailDone);
}
