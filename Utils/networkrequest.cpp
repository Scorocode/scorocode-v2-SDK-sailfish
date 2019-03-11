#include "networkrequest.h"
#include <QHttpPart>
#include <QFile>
#include <QMimeDatabase>
#include <QMimeType>
#include <QDebug>

NetworkRequest::NetworkRequest(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished,
            this, &NetworkRequest::requestDone);
}

NetworkRequest::~NetworkRequest()
{
    delete manager;
}

void NetworkRequest::getRequest(const QUrl url, const QString &token)
{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("accept", "application/json");
    if (!token.isNull())
    {
        QString t = "Bearer ";
        t += token;
        request.setRawHeader("Authorization", t.toUtf8());
    }
    manager->get(request);
}

void NetworkRequest::postRequest(const QUrl url, const QByteArray body, const QString &token)
{
    qDebug() << url << "body" << body;
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("accept", "application/json");
    if (!token.isNull())
    {
        QString t = "Bearer ";
        t += token;
        request.setRawHeader("Authorization", t.toUtf8());
    }
    qDebug() << "Headers" << request.rawHeaderList().toVector();
    manager->post(request, body);
}

void NetworkRequest::putRequest(const QUrl url, const QByteArray data, const QString &token)
{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("accept", "application/json");

    if (!token.isNull())
    {
        QString t = "Bearer ";
        t += token;
        request.setRawHeader("Authorization", t.toUtf8());
    }
    manager->put(request, data);
}

void NetworkRequest::deleteRequest(const QUrl url, const QString &token)
{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("accept", "application/json");

    if (!token.isNull())
    {
        QString t = "Bearer ";
        t += token;
        request.setRawHeader("Authorization", t.toUtf8());
    }
    manager->deleteResource(request);
}

void NetworkRequest::requestDone(QNetworkReply *reply)
{
    QString str(reply->readAll());
    QJsonDocument jsonDoc = QJsonDocument::fromJson(str.toUtf8());

    qDebug().noquote() << "error code" << reply->error() << reply->errorString() \
             << "Message" << str;

    if (reply->error() == QNetworkReply::NoError)
    {
        switch (reply->operation()) {
        case QNetworkAccessManager::GetOperation:
            emit replyGet(reply->error(), jsonDoc);
            break;
        case QNetworkAccessManager::PutOperation:
            emit replyPut(reply->error(), jsonDoc);
            break;
        case QNetworkAccessManager::PostOperation:
            emit replyPost(reply->error(), jsonDoc);
//            qDebug().noquote() << "json replyPost" << jsonDoc.toJson();
            break;
        case QNetworkAccessManager::DeleteOperation:
            emit replyDelete(reply->error(), jsonDoc);
            break;
        default:
            break;
        }

    }
    else
    {
        emit error(reply->error());
    }
    reply->deleteLater();
}
