#pragma once

#include <QObject>
#include <QFile>

#include "../Utils/networkrequest.h"

class Files : public QObject
{
    Q_OBJECT
public:
    explicit Files(QString baseUrl, QObject *parent = nullptr);

    void setToken(const QString &token);

    /*!
     * \brief fileDownload
     * \param path
     */
    void fileDownload(const QString &path);

    /*!
     * \brief fileUpload
     * \param path
     * \param payload
     */
    void fileUpload(const QString &path, const QString &fileName);

    /*!
     * \brief fileRename
     * \param path
     * \param payload
     */
    void fileRename(const QString &path, const QString &fileName);

    /*!
     * \brief fileDelete
     * \param path
     */
    void fileDelete(const QString &path);

signals:
    void fileDownloadDone(int errorCode, QJsonDocument data);
    void fileUploadDone(int errorCode, QJsonDocument data);
    void fileRenameDone(int errorCode, QJsonDocument data);
    void fileDeleteDone(int errorCode, QJsonDocument data);

public slots:

private:
    QString m_baseUrl;
    NetworkRequest *m_request;
    QFile *file;
    QString m_token;
};

// FILES_H
