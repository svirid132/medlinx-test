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
    Q_PROPERTY(NOTIFY error)

public:
    explicit MessageSerialPort(QObject *parent = nullptr);
    Q_INVOKABLE void readData();
    Q_INVOKABLE void stop();
    bool isReading() const;


signals:
    void isReadingChanged();
    void newMessage(const Message& message);
    void error(const QString& text);

private:
    QSerialPort m_serialPort;
    bool m_isReading = false;
    unsigned short crc16(unsigned char *pcBlock, unsigned short len);
    unsigned short dataToUshort(const char *data);
    qint32 dataToInt(const char* data);
};

#endif // MESSAGESERIALPORT_H
