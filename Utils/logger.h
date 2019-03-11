#pragma once

#include <QObject>
#include <QMessageLogger>

namespace logger {

const QString defaultLogFolder = "/home/nemo/";

bool initLogging();
void myMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString& msg);
}

// LOGGER_H
