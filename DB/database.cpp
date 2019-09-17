#include "database.h"

Database::Database(QString baseUrl, QObject *parent) :
    QObject(parent)
{
    m_baseUrl = baseUrl + "sc/db/api/v2/";
    m_request = new NetworkRequest();

    connect(m_request, &NetworkRequest::replyDelete, this, [this](int errCode, QJsonDocument data) {
        emit deleteRecordDone(errCode, data, m_tableName);
    });
    connect(m_request, &NetworkRequest::replyPost, this, [this](int errCode, QJsonDocument data) {
        emit insertRecordDone(errCode, data, m_tableName);
    });
    connect(m_request, &NetworkRequest::replyPut, this, [this](int errCode, QJsonDocument data) {
        emit updateRecordDone(errCode, data, m_tableName);
    });
    connect(m_request, &NetworkRequest::replyGet, this, [this](int errCode, QJsonDocument data) {
        emit getRecordDone(errCode, data, m_tableName);
    });
}

void Database::setToken(const QString &token)
{
    if (!token.isEmpty() && !token.isNull())
    {
        m_token = token;
    }
}

void Database::getRecordList(const QString &type, const QString &db_name, const QString &schema, const QString &table)
{
    if (type.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::TypeIsEmpty);
        return;
    }
    if (db_name.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::DbNameIsEmpty);
        return;
    }
    if (schema.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::SchemaIsEmpty);
        return;
    }
    if (table.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::TableNameIsEmpty);
        return;
    }
    if (!m_token.isNull())
    {
        m_tableName = table;
        QUrl url = m_baseUrl + type + "/" + db_name + "/" + schema + "/" + table;
        m_request->getRequest(url, m_token);
    }
}

void Database::getRecordList(const QString &type, const QString &db_name, const QString &schema, const QString &table, const QStringList &additional)
{
    if (type.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::TypeIsEmpty);
        return;
    }
    if (db_name.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::DbNameIsEmpty);
        return;
    }
    if (schema.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::SchemaIsEmpty);
        return;
    }
    if (table.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::TableNameIsEmpty);
        return;
    }
    if (!m_token.isNull())
    {
        QString path = m_baseUrl + type + "/" + db_name + "/" + schema + "/" + table;
        foreach (auto item, additional)
        {
            if(!item.isEmpty())
            {
                QString attr = item.section(':', 0, 0);
                QString value = item.section(':', 1, 1);
                if (item == additional.at(0))
                {
                    path += "?";
                }
                else
                {
                    path += "&";
                }
                path += attr + ":" + value;
            }
        }
        m_tableName = table;
        QUrl url = path;
        qDebug() << "Get data" << url;
        m_request->getRequest(url, m_token);
    }
}

void Database::getRecordById(const QString &type, const QString &db_name, const QString &schema, const QString &table, const QString &record_id)
{
    if (type.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::TypeIsEmpty);
        return;
    }
    if (db_name.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::DbNameIsEmpty);
        return;
    }
    if (schema.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::SchemaIsEmpty);
        return;
    }
    if (table.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::TableNameIsEmpty);
        return;
    }
    if (record_id.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::RecordIdIsEmpty);
        return;
    }
    if (!m_token.isNull())
    {
        m_tableName = table;
        QUrl url = m_baseUrl + type + "/" + db_name + "/" + schema + "/" + table + "/" + record_id;
        m_request->getRequest(url, m_token);
    }
}

void Database::insertRecord(const QString &type, const QString &db_name, const QString &schema, const QString &table, const QString &payload)
{
    qDebug() << "payload" << payload;
    if (type.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::TypeIsEmpty);
        return;
    }
    if (db_name.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::DbNameIsEmpty);
        return;
    }
    if (schema.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::SchemaIsEmpty);
        return;
    }
    if (table.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::TableNameIsEmpty);
        return;
    }
    if (payload.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::PayloadIsEmpty);
        return;
    }
    if (!m_token.isNull())
    {
        m_tableName = table;
        QJsonDocument doc = QJsonDocument::fromJson(payload.toUtf8());
        qDebug() << "payload" << doc.toJson();
        QUrl url = m_baseUrl + type + "/" + db_name + "/" + schema + "/" + table;
        m_request->postRequest(url, doc.toJson(), m_token);
    }
}

void Database::updateRecord(const QString &type, const QString &db_name, const QString &schema, const QString &table, const QString &record_id, const QString &payload)
{
    if (type.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::TypeIsEmpty);
        return;
    }
    if (db_name.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::DbNameIsEmpty);
        return;
    }
    if (schema.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::SchemaIsEmpty);
        return;
    }
    if (table.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::TableNameIsEmpty);
        return;
    }
    if (record_id.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::RecordIdIsEmpty);
        return;
    }
    if (payload.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::PayloadIsEmpty);
        return;
    }
    if (!m_token.isNull())
    {
        m_tableName = table;
        QJsonDocument doc = QJsonDocument::fromJson(payload.toUtf8());
        qDebug() << "payload" << doc.toJson();
        QUrl url = m_baseUrl + type + "/" + db_name + "/" + schema + "/" + table + "/" + record_id;
        m_request->putRequest(url, doc.toJson(), m_token);
    }
}

void Database::deleteRecord(const QString &type, const QString &db_name, const QString &schema, const QString &table, const QString &record_id)
{
    if (type.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::TypeIsEmpty);
        return;
    }
    if (db_name.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::DbNameIsEmpty);
        return;
    }
    if (schema.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::SchemaIsEmpty);
        return;
    }
    if (table.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::TableNameIsEmpty);
        return;
    }
    if (record_id.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::RecordIdIsEmpty);
        return;
    }
    if (!m_token.isNull())
    {
        m_tableName = table;
        QUrl url = m_baseUrl + type + "/" + db_name + "/" + schema + "/" + table + "/" + record_id;
        m_request->deleteRequest(url, m_token);
    }
}
