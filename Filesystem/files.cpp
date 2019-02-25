#include "files.h"

#include <QBuffer>
#include <QFileInfo>
#include <QJsonObject>
#include <QJsonDocument>

Files::Files(QString baseUrl, QObject *parent) :
    QObject(parent)
{
    m_baseUrl = baseUrl + "sc/fs/api/v2/files/";
    m_request = new NetworkRequest();
}

void Files::setToken(const QString &token)
{
    if (!token.isEmpty() && !token.isNull())
    {
        m_token = token;
    }
}

void Files::fileUpload(const QString &path, const QString &fileName)
{
    Q_ASSERT(!path.isEmpty());

    if (!m_token.isNull())
    {
        file = new QFile(path);
        file->open(QIODevice::ReadOnly);
        QUrl url = m_baseUrl + fileName;


        QByteArray ba;
//        QBuffer buffer( &ba );
//        buffer.open(QBuffer::ReadWrite);
        ba.append(file->readAll());
        QJsonObject tmp;
        QString str = "test test test";
        tmp.insert("file", QJsonValue::fromVariant(str.toUtf8().toBase64()));
//        QJsonDocument payload(tmp);

        file->close();
        delete file;

        qDebug() << "Upload url" << url << "File" << fileName;

        m_request->postRequest(url, str.toUtf8().toBase64()/*payload.toJson()*/, m_token);
        connect(m_request, &NetworkRequest::replyPost, this, &Files::fileUploadDone);
//        connect(m_request, &NetworkRequest::replyPost, this, [this](int errorCode, QJsonDocument data){
//            Q_UNUSED(data);
//            qDebug() << "Delete tmp file" << errorCode;
//            if (0 == errorCode)
//            {
//                delete this->file;
//            }
//        });
//        connect(m_request, &NetworkRequest::error, this, [this](int errorCode){
//            qDebug() << "Delete tmp file" << errorCode;
//            delete this->file;
//        });
    }
}

void Files::fileRename(const QString &path, const QString &fileName)
{
    Q_ASSERT(!path.isEmpty());
    if (!m_token.isNull())
    {
        QUrl url = m_baseUrl + path;

        QJsonObject tmp;
        tmp.insert("newPath", fileName);
        QJsonDocument payload(tmp);

        m_request->putRequest(url, payload.toJson(), m_token);
        connect(m_request, &NetworkRequest::replyPut, this, &Files::fileRenameDone);
    }
}

void Files::fileDownload(const QString &path)
{
    Q_ASSERT(!path.isEmpty());
    if (!m_token.isNull())
    {
        QUrl url = m_baseUrl + path;
        m_request->getRequest(url, m_token);
        connect(m_request, &NetworkRequest::replyGet, this, &Files::fileDownloadDone);
    }
}

void Files::fileDelete(const QString &path)
{
    Q_ASSERT(!path.isEmpty());

    if (!m_token.isNull())
    {
        QUrl url = m_baseUrl + path;
        m_request->deleteRequest(url, m_token);
        connect(m_request, &NetworkRequest::replyDelete, this, &Files::fileDeleteDone);
    }
}
