#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QJsonDocument>

class NetworkRequest : public QObject
{
    Q_OBJECT
public:
    explicit NetworkRequest(QObject *parent = nullptr);

    virtual ~NetworkRequest();

    void getRequest(const QUrl url, const QString &token = nullptr);
    void postRequest(const QUrl url, const QByteArray body, const QString &token = nullptr);
    void putRequest(const QUrl url, const QByteArray data, const QString &token = nullptr);
    void deleteRequest(const QUrl url, const QString &token = nullptr);

signals:
    void replyGet(int errorCode, QJsonDocument data);
    void replyPost(int errorCode, QJsonDocument data);
    void replyPut(int errorCode, QJsonDocument data);
    void replyDelete(int errorCode, QJsonDocument data);

    void error(int errorCode);

private slots:
    void requestDone(QNetworkReply* reply);


private:
    QNetworkAccessManager *manager;
};

// NETWORKREQUEST_H
