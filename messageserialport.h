#ifndef MESSAGESERIALPORT_H
#define MESSAGESERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include "Message.h"

class MessageSerialPort : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isReading READ isReading NOTIFY isReadingChanged)
    Q_PROPERTY(NOTIFY newMessage)

public:
    explicit MessageSerialPort(QObject *parent = nullptr);
    Q_INVOKABLE void readData();
    Q_INVOKABLE void stop();
    bool isReading() const;


signals:
    void isReadingChanged();
    void newMessage(const Message& message);

private:
    QSerialPort m_serialPort;
    bool m_isReading = false;
    unsigned short crc16(unsigned char *pcBlock, unsigned short len);
};

#endif // MESSAGESERIALPORT_H
