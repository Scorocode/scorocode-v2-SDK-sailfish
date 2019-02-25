#include "websocket.h"

QT_USE_NAMESPACE

WebSocket::WebSocket(const QUrl &url, QObject *parent):
    QObject(parent),
    m_url(url)
{
    connect(&m_webSocket, &QWebSocket::connected, this, &WebSocket::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &WebSocket::closed);
    m_webSocket.open(QUrl(url));
}

void WebSocket::on(const QString &eventName)
{
    if (!m_eventsList.contains(eventName))
    {
        m_eventsList.insert(eventName);
    }
}

void WebSocket::off(const QString &eventName)
{
    if (m_eventsList.contains(eventName))
    {
        m_eventsList.remove(eventName);
    }
}

void WebSocket::once(const QString &eventName)
{
    if (!m_onceEventsList.contains(eventName))
    {
        m_onceEventsList.insert(eventName);
    }
}

void WebSocket::onConnected()
{
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &WebSocket::onTextMessageReceived);
    m_webSocket.sendTextMessage(QStringLiteral("Hello, world!"));
}

void WebSocket::onTextMessageReceived(QString message)
{
    if (m_onceEventsList.contains(message))
    {
        m_onceEventsList.remove(message);
    }

    if (m_eventsList.contains(message))
    {
        // do something
    }
}
