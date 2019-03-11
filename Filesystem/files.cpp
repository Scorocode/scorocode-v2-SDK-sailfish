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
    m_fileManager = new FileManager();
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
    if (path.isEmpty())
    {
        emit fileRequestError(Files::FileError::PathIsEmpty);
        return;
    }
    if (fileName.isEmpty())
    {
        emit fileRequestError(Files::FileError::FileNameIsEmpty);
        return;
    }

    if (!m_token.isNull())
    {
        QUrl url = m_baseUrl + fileName;

        qDebug() << "Upload url" << url << "File" << fileName;

        m_fileManager->fileUpload(url,path, m_token);
//        m_request->fileUpload(url, path/*payload.toJson()*/, m_token);
//        connect(m_request, &NetworkRequest::replyPost, this, &Files::fileUploadDone);
    }
}

void Files::fileRename(const QString &path, const QString &fileName)
{
    if (path.isEmpty())
    {
        emit fileRequestError(Files::FileError::PathIsEmpty);
        return;
    }
    if (fileName.isEmpty())
    {
        emit fileRequestError(Files::FileError::FileNameIsEmpty);
        return;
    }
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
    if (path.isEmpty())
    {
        emit fileRequestError(Files::FileError::PathIsEmpty);
        return;
    }
    if (!m_token.isNull())
    {
        QUrl url = m_baseUrl + path;
        m_fileManager->fileDownload(url, m_token);
        connect(m_fileManager, &FileManager::updateBytesReceived, this, [](qint64 bytesReceived, qint64 bytesTotal){
            qDebug() << "Received" << bytesReceived << "from" << bytesTotal;
        });
    }
}

void Files::fileDelete(const QString &path)
{
    if (path.isEmpty())
    {
        emit fileRequestError(Files::FileError::PathIsEmpty);
        return;
    }

    if (!m_token.isNull())
    {
        QUrl url = m_baseUrl + path;
        m_request->deleteRequest(url, m_token);
        connect(m_request, &NetworkRequest::replyDelete, this, &Files::fileDeleteDone);
    }
}
