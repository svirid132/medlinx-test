#include "messageserialport.h"

#include <QSerialPortInfo>

MessageSerialPort::MessageSerialPort(QObject *parent)
    : QObject{parent}
{
    m_serialPort.setPortName("tnt0");
    m_serialPort.setBaudRate(QSerialPort::Baud115200);
    m_serialPort.setStopBits(QSerialPort::OneStop);
    connect(&m_serialPort, &QSerialPort::readyRead, this, [this]() {
        const QByteArray data = m_serialPort.readAll();
        if (data.length() < 3) {
            return;
        }
        int rawDataSize = data.size() - 2; // без двух байт crc16
        unsigned short calculecCrc16 = crc16((unsigned char*)data.data(), rawDataSize);
        unsigned short receivedCrc16 = dataToUshort(data.data() + rawDataSize);
        if (calculecCrc16 != receivedCrc16) {
            return;
        }
        Message message;
        message.address = data[0];
        message.type = static_cast<Message::MESSAGE_TYPE>(data[1]);
        message.size = dataToUshort(data.data() + 2);;
        switch (message.type) {
        case Message::NUMBER: {
            qint32 num = dataToInt(data.data() + 4);
            message.data = QVariant::fromValue( num );
            break;
        }
        case Message::TEXT: {
            message.data = QVariant::fromValue( QString::fromUtf8(data.mid(4, message.size)) );
            break;
        }
        default:
            break;
        }
        emit newMessage(message);
    });
}

void MessageSerialPort::readData()
{
    if(!m_serialPort.open(QIODevice::ReadWrite)) {
        emit error(QString("Код ошибки %1").arg(m_serialPort.error()));
        return;
    }

    m_isReading = true;
    emit isReadingChanged();
}

void MessageSerialPort::stop()
{
    if (m_serialPort.isOpen()) {
        m_serialPort.close();
    }
    m_isReading = false;
    emit isReadingChanged();
}

bool MessageSerialPort::isReading() const
{
    return m_isReading;
}

unsigned short MessageSerialPort::crc16(unsigned char *pcBlock, unsigned short len)
{
    unsigned short crc = 0xFFFF;
    unsigned char i;

    while (len--)
    {
        crc ^= *pcBlock++ << 8;

        for (i = 0; i < 8; i++)
            crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
    }
    return crc;
}

unsigned short MessageSerialPort::dataToUshort(const char *data)
{
    unsigned short num = 0;
    num = ((unsigned char)data[0] << 8) |
            (unsigned char)data[1];
    return num;
}

qint32 MessageSerialPort::dataToInt(const char *data)
{
    quint32 num = 0;
    num = ((unsigned char)data[0] << 24) |
            ((unsigned char)data[1] << 16) |
            ((unsigned char)data[2] << 8) |
            (unsigned char)data[3];
    return (qint32)num;
}
