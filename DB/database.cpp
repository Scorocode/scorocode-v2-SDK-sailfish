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
    if (!m_token.isNull())
    {
        QUrl url = m_baseUrl + type + "/" + db_name + "/" + schema + "/" + table;
        m_request->getRequest(url, m_token);
        connect(m_request, &NetworkRequest::replyGet, this, &Database::getRecordListDone);
    }
}

void Database::getRecordById(const QString &type, const QString &db_name, const QString &schema, const QString &table, const QString &record_id)
{
    if (!m_token.isNull())
    {
        QUrl url = m_baseUrl + type + "/" + db_name + "/" + schema + "/" + table + "/" + record_id;
        m_request->getRequest(url, m_token);
        connect(m_request, &NetworkRequest::replyGet, this, &Database::getRecordByIdDone);
    }
}

void Database::insertRecord(const QString &type, const QString &db_name, const QString &schema, const QString &table, QJsonDocument payload)
{
    if (!m_token.isNull())
    {
        QUrl url = m_baseUrl + type + "/" + db_name + "/" + schema + "/" + table;
        m_request->postRequest(url, payload.toJson(), m_token);
        connect(m_request, &NetworkRequest::replyPost, this, &Database::insertRecordDone);
    }
}

void Database::updateRecord(const QString &type, const QString &db_name, const QString &schema, const QString &table, const QString &record_id, QJsonDocument payload)
{
    if (!m_token.isNull())
    {
        QUrl url = m_baseUrl + type + "/" + db_name + "/" + schema + "/" + table + "/" + record_id;
        m_request->putRequest(url, payload.toJson(), m_token);
        connect(m_request, &NetworkRequest::replyPut, this, &Database::updateRecordDone);
    }
}

void Database::deleteRecord(const QString &type, const QString &db_name, const QString &schema, const QString &table, const QString &record_id)
{
    if (!m_token.isNull())
    {
        QUrl url = m_baseUrl + type + "/" + db_name + "/" + schema + "/" + table + "/" + record_id;
        m_request->deleteRequest(url, m_token);
        connect(m_request, &NetworkRequest::replyDelete, this, &Database::deleteRecordDone);
    }
}
