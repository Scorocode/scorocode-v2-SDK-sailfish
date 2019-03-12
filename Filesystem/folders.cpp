#include "folders.h"
#include <QJsonObject>

Folders::Folders(QString baseUrl, QObject *parent) :
    QObject(parent)
{
    m_baseUrl = baseUrl + "sc/fs/api/v2/folders/";
    m_request = new NetworkRequest();
    connect(m_request, &NetworkRequest::replyGet, this, &Folders::folderReadDone);
    connect(m_request, &NetworkRequest::replyPut, this, &Folders::folderReadDone);
    connect(m_request, &NetworkRequest::replyDelete, this, &Folders::folderDeleteDone);
    connect(m_request, &NetworkRequest::replyPost, this, &Folders::folderCreateDone);
}

void Folders::setToken(const QString &token)
{
    if (!token.isEmpty() && !token.isNull())
    {
        m_token = token;
    }
}

void Folders::folderCreate(const QString &path)
{
    if (path.isEmpty())
    {
        emit folderRequestError(Folders::FolderError::PathIsEmpty);
        return;
    }

    QUrl url = m_baseUrl + path;
    QByteArray body;
    if (!m_token.isNull())
    {
        m_request->postRequest(url, body, m_token);
    }
}

void Folders::folderRead(const QString &path)
{
    if (path.isEmpty())
    {
        emit folderRequestError(Folders::FolderError::PathIsEmpty);
        return;
    }

    QUrl url = m_baseUrl + path;

    if (!m_token.isNull())
    {
        m_request->getRequest(url, m_token);
    }
}

void Folders::folderRename(const QString &path, const QString &newFolderName)
{
    if (path.isEmpty())
    {
        emit folderRequestError(Folders::FolderError::PathIsEmpty);
        return;
    }
    if (newFolderName.isEmpty())
    {
        emit folderRequestError(Folders::FolderError::FolderNameIsEmpty);
        return;
    }

    QUrl url = m_baseUrl + path;

    if (!m_token.isNull())
    {
        QJsonObject tmp;
        tmp.insert("newPath", newFolderName);
        QJsonDocument payload(tmp);
        qDebug() << "Rename folder" << url << newFolderName;
        m_request->putRequest(url, payload.toJson(), m_token);
    }

}

void Folders::folderDelete(const QString &path)
{
    if (path.isEmpty())
    {
        emit folderRequestError(Folders::FolderError::PathIsEmpty);
        return;
    }

    QUrl url = m_baseUrl + path;

    if (!m_token.isNull())
    {
        m_request->deleteRequest(url, m_token);
    }
}
