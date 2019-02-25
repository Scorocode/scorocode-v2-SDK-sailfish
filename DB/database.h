#pragma once

#include <QObject>

#include "../Utils/networkrequest.h"

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QString baseUrl, QObject *parent = nullptr);

    void setToken(const QString &token);

    /*!
     * \brief getRecordList
     * \param type
     * \param db_name
     * \param schema
     * \param table
     */
    void getRecordList(const QString &type, const QString &db_name, const QString &schema, const QString &table);

    /*!
     * \brief getRecordById
     * \param type
     * \param db_name
     * \param schema
     * \param table
     * \param record_id
     */
    void getRecordById(const QString &type, const QString &db_name, const QString &schema, const QString &table, const QString &record_id);

    /*!
     * \brief insertRecord
     * \param type
     * \param db_name
     * \param schema
     * \param table
     * \param payload
     */
    void insertRecord(const QString &type, const QString &db_name, const QString &schema, const QString &table, QJsonDocument payload);

    /*!
     * \brief updateRecord
     * \param type
     * \param db_name
     * \param schema
     * \param table
     * \param record_id
     * \param payload
     */
    void updateRecord(const QString &type, const QString &db_name, const QString &schema, const QString &table, const QString &record_id, QJsonDocument payload);

    /*!
     * \brief deleteRecord
     * \param type
     * \param db_name
     * \param schema
     * \param table
     * \param record_id
     */
    void deleteRecord(const QString &type, const QString &db_name, const QString &schema, const QString &table, const QString &record_id);

signals:
    void getRecordListDone(int errorCode, QJsonDocument data);
    void getRecordByIdDone(int errorCode, QJsonDocument data);
    void insertRecordDone(int errorCode, QJsonDocument data);
    void updateRecordDone(int errorCode, QJsonDocument data);
    void deleteRecordDone(int errorCode, QJsonDocument data);

private:
    QString m_baseUrl;
    NetworkRequest *m_request;
    QString m_token;
};

// DATABASE_H
