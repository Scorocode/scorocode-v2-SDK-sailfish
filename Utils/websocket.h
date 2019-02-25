#pragma once

#include <QObject>
#include <QtWebSockets/QWebSocket>

class WebSocket : public QObject
{
    Q_OBJECT
public:
    explicit WebSocket(const QUrl &url, QObject *parent = nullptr);

    void on(const QString &eventName);
    void off(const QString &eventName);
    void once(const QString &eventName);

Q_SIGNALS:
    void closed();

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
