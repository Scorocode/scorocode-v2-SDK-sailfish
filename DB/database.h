#pragma once

#include <QObject>

#include "Utils/networkrequest.h"

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QString baseUrl, QObject *parent = nullptr);

    void setToken(const QString &token);

    /*!
     * \brief getRecordList - perform a simple search in a database
     * \param type
     * \param db_name
     * \param schema
     * \param table
     */
    void getRecordList(const QString &type, const QString &db_name, const QString &schema, const QString &table);

    /*!
     * \brief getRecordList - perform a search with filtration in a database
     * \param type
     * \param db_name
     * \param schema
     * \param table
     * \param additional
     */
    void getRecordList(const QString &type, const QString &db_name, const QString &schema, const QString &table, const QStringList &additional);

    /*!
     * \brief getRecordById - perform a simple search in a database for an apropriate record
     * \param type
     * \param db_name
     * \param schema
     * \param table
     * \param record_id
     */
    void getRecordById(const QString &type, const QString &db_name, const QString &schema, const QString &table, const QString &record_id);

    /*!
     * \brief insertRecord - add a new record to a database
     * \param type
     * \param db_name
     * \param schema
     * \param table
     * \param payload
     */
    void insertRecord(const QString &type, const QString &db_name, const QString &schema, const QString &table, const QString &payload);

    /*!
     * \brief updateRecord - update a record in a database
     * \param type
     * \param db_name
     * \param schema
     * \param table
     * \param record_id
     * \param payload
     */
    void updateRecord(const QString &type, const QString &db_name, const QString &schema, const QString &table, const QString &record_id, const QString &payload);

    /*!
     * \brief deleteRecord - delete a record from a database
     * \param type
     * \param db_name
     * \param schema
     * \param table
     * \param record_id
     */
    void deleteRecord(const QString &type, const QString &db_name, const QString &schema, const QString &table, const QString &record_id);

    enum class DatabaseError
    {
        NoError = 0,
        TypeIsEmpty,
        DbNameIsEmpty,
        SchemaIsEmpty,
        TableNameIsEmpty,
        RecordIdIsEmpty,
        PayloadIsEmpty
    };

signals:
    void getRecordDone(int errorCode, QJsonDocument data, QString tableName);
    void insertRecordDone(int errorCode, QJsonDocument data, QString tableName);
    void updateRecordDone(int errorCode, QJsonDocument data, QString tableName);
    void deleteRecordDone(int errorCode, QJsonDocument data, QString tableName);
    void DbRequestError(Database::DatabaseError errorCode);

private:
    QString m_baseUrl;
    NetworkRequest *m_request;
    QString m_token;

    QString m_tableName;
};

// DATABASE_H
