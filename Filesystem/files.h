#pragma once

#include <QObject>
#include <QFile>

#include "Utils/networkrequest.h"
#include "Utils/filemanager.h"

class Files : public QObject
{
    Q_OBJECT
public:
    explicit Files(QString baseUrl, QObject *parent = nullptr);

    void setToken(const QString &token);

    /*!
     * \brief fileDownload - download file to the '/home/nemo/Downloads' folder
     * \param path
     */
    void fileDownload(const QString &path);

    /*!
     * \brief fileUpload - upload  file to a server
     * \param path
     * \param fileName
     */
    void fileUpload(const QString &path, const QString &fileName);

    /*!
     * \brief fileRename - rename file
     * \param path
     * \param fileName
     */
    void fileRename(const QString &path, const QString &fileName);

    /*!
     * \brief fileDelete - delete file from a server
     * \param path
     */
    void fileDelete(const QString &path);

    enum class FileError
    {
        NoError = 0,
        PathIsEmpty,
        FileNameIsEmpty
    };

signals:
    void fileDownloadDone(int errorCode, QJsonDocument data);
    void fileUploadDone(int errorCode, QJsonDocument data);
    void fileRenameDone(int errorCode, QJsonDocument data);
    void fileDeleteDone(int errorCode, QJsonDocument data);
    void fileRequestError(Files::FileError errorCode);

public slots:

private:
    QString m_baseUrl;
    NetworkRequest *m_request;
    FileManager *m_fileManager;
    QFile *file;
    QString m_token;
};

// FILES_H
