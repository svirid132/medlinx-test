#include "messagemodel.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlResult>
#include <QSqlError>

MessageModel::MessageModel() {
    createConnectionDB();
    filledModelFromDB();
}

int MessageModel::rowCount(const QModelIndex &parent) const
{
    return m_messages.size();
}

QVariant MessageModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        const int row = index.row();
        return QVariant::fromValue( m_messages.at(row) );
    }

    return QVariant();
}

void MessageModel::insert(const Message &message)
{
    const int newIndex = m_messages.size();
    beginInsertRows(QModelIndex(), newIndex, newIndex);
    QString queryText = QString("insert into message (address, type, size, data) values(%1, "
                                "%2, %3, \"%4\")")
                            .arg(message.address)
                            .arg(message.type)
                            .arg(message.size)
                            .arg(message.data.toString());
    m_messages.append(message);
    QSqlQuery query;
    query.exec(queryText);
    endInsertRows();
}

void MessageModel::clear()
{
    beginResetModel();
    m_messages.clear();
    QSqlQuery query;
    query.exec("DELETE FROM message");
    endResetModel();
}

bool MessageModel::createConnectionDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("MessageData");
    db.open();

    QSqlQuery query;
    query.exec("create table message (id int primary key, "
               "address int, type int, size int, data text)");

    return true;
}

void MessageModel::filledModelFromDB()
{
    beginResetModel();
    m_messages.clear();
    QSqlQuery query;
    query.exec("SELECT * FROM message");
    while (query.next()) {
        Message message;
        message.address = query.value(1).toInt();
        message.type = static_cast<Message::MESSAGE_TYPE>(query.value(2).toInt());
        message.size = query.value(3).toInt();
        message.data = query.value(4);
        m_messages.append(message);
    }
    endResetModel();
}
