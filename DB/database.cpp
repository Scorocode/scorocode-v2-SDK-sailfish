#include "database.h"

Database::Database(QString baseUrl, QObject *parent) :
    QObject(parent)
{
    m_baseUrl = baseUrl + "sc/db/api/v2/";
    m_request = new NetworkRequest();
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
        QUrl url = m_baseUrl + type + "/" + db_name + "/" + schema + "/" + table;
        m_request->getRequest(url, m_token);
        connect(m_request, &NetworkRequest::replyGet, this, &Database::getRecordListDone);
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
            path += attr + "=" + value;
        }
        QUrl url = path;
        m_request->getRequest(url, m_token);
        connect(m_request, &NetworkRequest::replyGet, this, &Database::getRecordListDone);
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
        QUrl url = m_baseUrl + type + "/" + db_name + "/" + schema + "/" + table + "/" + record_id;
        m_request->getRequest(url, m_token);
        connect(m_request, &NetworkRequest::replyGet, this, &Database::getRecordByIdDone);
    }
}

void Database::insertRecord(const QString &type, const QString &db_name, const QString &schema, const QString &table, const QString &payload)
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
    if (payload.isEmpty())
    {
        emit DbRequestError(Database::DatabaseError::PayloadIsEmpty);
        return;
    }
    if (!m_token.isNull())
    {
        QJsonDocument doc = QJsonDocument::fromJson(payload.toUtf8());
        qDebug() << "payload" << doc.toJson();
        QUrl url = m_baseUrl + type + "/" + db_name + "/" + schema + "/" + table;
        m_request->postRequest(url, doc.toJson(), m_token);
        connect(m_request, &NetworkRequest::replyPost, this, &Database::insertRecordDone);
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
        QJsonDocument doc = QJsonDocument::fromJson(payload.toUtf8());
        qDebug() << "payload" << doc.toJson();
        QUrl url = m_baseUrl + type + "/" + db_name + "/" + schema + "/" + table + "/" + record_id;
        m_request->putRequest(url, doc.toJson(), m_token);
        connect(m_request, &NetworkRequest::replyPut, this, &Database::updateRecordDone);
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
        QUrl url = m_baseUrl + type + "/" + db_name + "/" + schema + "/" + table + "/" + record_id;
        m_request->deleteRequest(url, m_token);
        connect(m_request, &NetworkRequest::replyDelete, this, &Database::deleteRecordDone);
    }
}
