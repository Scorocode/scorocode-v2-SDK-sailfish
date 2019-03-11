#pragma once

#include <QObject>

#include "../Utils/networkrequest.h"

class Folders : public QObject
{
    Q_OBJECT
public:
    explicit Folders(QString baseUrl, QObject *parent = nullptr);

    void setToken(const QString &token);

    /*!
     * \brief folderRead
     * \param path
     */
    void folderRead(const QString &path);

    /*!
     * \brief folderCreate
     * \param path
     * \param token
     */
    void folderCreate(const QString &path);

    /*!
     * \brief folderRename
     * \param path
     * \param payload
     */
    void folderRename(const QString &path, const QString &newFolderName);

    /*!
     * \brief folderDelete
     * \param path
     */
    void folderDelete(const QString &path);

    enum class FolderError
    {
        NoError = 0,
        PathIsEmpty,
        FolderNameIsEmpty
    };

signals:
    void folderReadDone(int errorCode, QJsonDocument data);
    void folderCreateDone(int errorCode, QJsonDocument data);
    void folderRenameDone(int errorCode, QJsonDocument data);
    void folderDeleteDone(int errorCode, QJsonDocument data);
    void folderRequestError(Folders::FolderError errorCode);

private:
    QString m_baseUrl;
    NetworkRequest *m_request;

    QString m_token;
};

// FOLDERS_H
