#pragma once

#include <QObject>
#include <QMessageLogger>

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QObject *parent = nullptr);

    Logger(const Logger&) = delete;
    Logger operator =(const Logger&) = delete;

signals:

public slots:
};

// LOGGER_H
