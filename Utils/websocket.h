#pragma once

#include <QObject>
#include <QtWebSockets/QWebSocket>
#include <QAbstractSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

class WebSocket : public QObject
{
    Q_OBJECT
public:
    explicit WebSocket(const QUrl &url, QObject *parent = nullptr);

    void on(const QString &eventName);
    void off(const QString &eventName);
    void once(const QString &eventName);

    ~WebSocket();

Q_SIGNALS:
    void closed();
    void socketConnected(QJsonDocument message);
    void messageReceived(QJsonDocument message);

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);

private:
    QWebSocket m_webSocket;
    QUrl m_url;
    QSet<QString> m_eventsList;
    QSet<QString> m_onceEventsList;
};

// WEBSOCKET_H
