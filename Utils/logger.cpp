#include "logger.h"

#include <QFile>
#include <QDir>
#include <QMutex>
#include <QMutexLocker>
#include <QTextStream>
#include <QtGlobal>
#include <QDebug>

namespace logger {

static QString logFileName = "scorocode.log";

bool initLogging()
{
    // Create folder for logfiles if not exists
    if (!QDir(defaultLogFolder).exists())
    {
        QDir().mkdir(defaultLogFolder);
    }

    QString logFile = defaultLogFolder + logFileName;

    if (QFile(logFile).exists())
    {
        qDebug() << "Rename old log file";
        QFile::rename(logFile, defaultLogFolder + "prev_" +logFileName);
    }

    qDebug() << "Check log file" << logFile;
    QFile outFile(logFile);
    if(outFile.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        outFile.close();
        qDebug() << "Change qInstallMessageHandler";
        qInstallMessageHandler(myMessageHandler);
        return true;
    }
    else
    {
        return false;
    }
}

void myMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    QMutexLocker lock(&mutex);
    static QString logFile = defaultLogFolder + logFileName;
    //    QFile log(logFile);
    //    qDebug() << "Open log file" << logFile << log.open(QIODevice::WriteOnly | QIODevice::Append);
    //    static QTextStream logFileStream(&log);
    static QTextStream logFileStream(&logFile, QIODevice::WriteOnly | QIODevice::Append);
    logFileStream << qFormatLogMessage(type, context, msg) << endl;
}

}
