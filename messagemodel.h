#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include "Message.h"

#include <QAbstractListModel>
#include <QObject>

class MessageModel : public QAbstractListModel
{
    Q_OBJECT
public:
    MessageModel();
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    Q_INVOKABLE void insert(const Message& message);
    Q_INVOKABLE void clear();
    bool createConnectionDB();
    void filledModelFromDB();

private:
    QList<Message> m_messages;
};

#endif // MESSAGEMODEL_H
