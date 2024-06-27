#ifndef MESSAGE_H
#define MESSAGE_H
#include <QObject>
#include <QVariant>
#include <QQmlEngine>

struct Message {
    Q_GADGET
    Q_PROPERTY(unsigned char address MEMBER address)
    Q_PROPERTY(MESSAGE_TYPE type MEMBER type)
    Q_PROPERTY(unsigned short size MEMBER size)
    Q_PROPERTY(QVariant data MEMBER data)

public:
    enum MESSAGE_TYPE {
        NUMBER = 1,
        TEXT = 2,
        FROM_EMPTY_DATA = 3,
        TO_EMPTY_DATA = 7
    };
    Q_ENUM(MESSAGE_TYPE)

    unsigned char address = 0;
    MESSAGE_TYPE type = MESSAGE_TYPE::NUMBER;
    unsigned short size = 0;
    QVariant data = QVariant("");
};

Q_DECLARE_METATYPE(Message)


#endif // MESSAGE_H
