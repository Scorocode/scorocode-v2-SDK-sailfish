#include "filemanager.h"
#include <QFileInfo>
#include <QMimeDatabase>

FileManager::FileManager(QObject *parent) : QObject(parent)
{
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, &QNetworkAccessManager::finished, this, &FileManager::onDownloadFinished);
}

void FileManager::fileUpload(const QUrl url, const QString &fileName, const QString &token)
{
    qDebug() << url;
    QNetworkRequest request(url);
    request.setRawHeader("accept", "application/json");
    if (!token.isNull())
    {
        QString t = "Bearer ";
        t += token;
        request.setRawHeader("Authorization", t.toUtf8());
    }

    QMimeDatabase db;
    QMimeType type = db.mimeTypeForFile(fileName);
    qDebug() << "Mime type:" << type.name();
    m_file = new QFile(fileName);
    qDebug() << "Open file" << m_file->open(QIODevice::ReadOnly);
    qDebug() << "file size:" << m_file->size();

    QByteArray postData;
    //create a header that the server can recognize
    postData.insert(0,"--AaB03x\r\nContent-Disposition: form-data; name=\"file\"; filename=\"test.txt\"\r\nContent-Type: text/x-log\r\n\r\n");
    postData.append(m_file->readAll());
    postData.append("\r\n--AaB03x--\r\n");

    request.setHeader(QNetworkRequest::ContentTypeHeader,"multipart/form-data; boundary=AaB03x");
    QVariant l=postData.length();
    request.setHeader(QNetworkRequest::ContentLengthHeader,l.toString());
    m_file->close();
    //free up memory
    delete(m_file);

    QNetworkReply* reply = m_manager->post(request, postData);

    connect(reply, &QNetworkReply::uploadProgress, this, [this](qint64 bytesSend, qint64 totalCount) {
        qDebug() << "bytes send" <<  bytesSend << " total" << totalCount;
        emit updateBytesSend(bytesSend, totalCount);
    });
}

void FileManager::fileDownload(const QUrl url, const QString &token)
{
    qDebug() << url;
    QNetworkRequest request(url);
    request.setRawHeader("accept", "application/json");
    if (!token.isNull())
    {
        QString t = "Bearer ";
        t += token;
        request.setRawHeader("Authorization", t.toUtf8());
    }


    QNetworkReply* reply = m_manager->get(request);

    connect(reply, &QNetworkReply::downloadProgress, this, &FileManager::updateBytesReceived);

    m_currentDownloads.append(reply);
}

void FileManager::onDownloadFinished(QNetworkReply *reply)
{
    QUrl url = reply->url();
    if (m_currentDownloads.contains(reply))
    {
        if (reply->error())
        {
            emit downloadError(reply->errorString());
        }
        else
        {
            QString filename = createFilePath(url);

            QFile file(filename);
            qDebug() << "Write file" << file.open(QIODevice::WriteOnly);

            file.write(reply->readAll());
            file.close();
        }
    }

    m_currentDownloads.removeAll(reply);
    reply->deleteLater();

}

QString FileManager::createFilePath(const QUrl &url)
{
    QString path = url.path();
    QString basename = QFileInfo(path).fileName();

    if (basename.isEmpty())
    {
        basename = "scorocode.tmp";
    }

    return m_downloads + basename;
}
