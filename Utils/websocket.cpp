#include "websocket.h"

QT_USE_NAMESPACE

WebSocket::WebSocket(const QUrl &url, QObject *parent):
    QObject(parent),
    m_url(url)
{
    connect(&m_webSocket, &QWebSocket::connected, this, &WebSocket::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &WebSocket::closed);

    connect(&m_webSocket, &QWebSocket::stateChanged, [](QAbstractSocket::SocketState state){
        qDebug() << "Websocket stateChanged" << state;
    });
    connect(&m_webSocket, &QWebSocket::disconnected, [](){
        qDebug() << "Websocket disconnected";
    });
    connect(&m_webSocket, &QWebSocket::pong, [](quint64 elapsedTime, const QByteArray &payload){
        qDebug() << "Websocket pong" << elapsedTime << "data" << payload;
    });

    m_webSocket.open(url);
}

WebSocket::~WebSocket()
{
    m_webSocket.close();
}

void WebSocket::on(const QString &eventName)
{
    if (!m_eventsList.contains(eventName))
    {
        qDebug() << "Add command" << eventName;
        m_eventsList.insert(eventName);
        m_webSocket.sendTextMessage(eventName);
    }
}

void WebSocket::off(const QString &eventName)
{
    if (m_eventsList.contains(eventName))
    {
        qDebug() << "Remove command" << eventName;
        m_eventsList.remove(eventName);
    }
}

void WebSocket::once(const QString &eventName)
{
    if (!m_onceEventsList.contains(eventName))
    {
        qDebug() << "Send once command" << eventName;
        m_onceEventsList.insert(eventName);
        m_webSocket.sendTextMessage(eventName);
    }
}

void WebSocket::onConnected()
{
    qDebug() << "WS connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &WebSocket::onTextMessageReceived);
//    m_webSocket.sendTextMessage(QStringLiteral("Hello, world!"));
}

void WebSocket::onTextMessageReceived(QString message)
{
    qDebug() << "WS" << message;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());

    if(!jsonDoc.isEmpty() && jsonDoc.isObject())
    {
        QJsonObject jsonObj = jsonDoc.object();
        QJsonValue jsonValue = jsonObj.value("command");
        if (jsonValue.isString())
        {
            QString command = jsonValue.toString();
            if ("hello" == command)
            {
                emit socketConnected(jsonDoc);
            }
            else
            {
                if (m_onceEventsList.contains(command))
                {
                    m_onceEventsList.remove(command);
                    emit messageReceived(jsonDoc);
                }

                if (m_eventsList.contains(command))
                {
                    emit messageReceived(jsonDoc);
                }
            }
        }
    }
}
