#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QJsonDocument>

class QFile;

class FileManager : public QObject
{
    Q_OBJECT
public:
    explicit FileManager(QObject *parent = nullptr, const QString defaultFilePath = "/home/nemo/Downloads/");

    void fileUpload(const QUrl url, const QString &fileName, const QString &token = nullptr);
    void fileDownload(const QUrl url, const QString &token = nullptr);

signals:
    void updateBytesReceived(qint64 bytesReceived, qint64 bytesTotal);
    void updateBytesSend(qint64 bytessend, qint64 bytesTotal);

    void downloadError(const QString errorMessage);

public slots:

private slots:
    void onDownloadFinished(QNetworkReply *reply);

private:
    QString createFilePath(const QUrl &url);

private:
    QString m_downloads; // = "/home/nemo/Downloads/";
    QNetworkAccessManager *m_manager;
    QNetworkReply*  m_currentReply {nullptr};
    QFile*          m_file         {nullptr};
    QVector<QNetworkReply *> m_currentDownloads;
};

// FILEMANAGER_H
