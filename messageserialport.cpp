#include "messageserialport.h"

MessageSerialPort::MessageSerialPort(QObject *parent)
    : QObject{parent}
{
    m_serialPort.setPortName("/dev/ttyUSB0");
    m_serialPort.setBaudRate(QSerialPort::Baud115200);
    connect(&m_serialPort, &QSerialPort::readyRead, this, [this]() {
        const QByteArray data = m_serialPort.readAll();
        if (data.length() < 3) {
            return;
        }
        int rawDataSize = data.length() - 2; // без двух байт crc16
        unsigned short calculecCrc16 = crc16((unsigned char*)data.data(), rawDataSize);
        unsigned short receivedCrc16 = data.mid( rawDataSize - 1, 2 ).toUShort();
        if (calculecCrc16 != receivedCrc16) {
            return;
        }
        Message message;
        message.address = data[0];
        message.type = static_cast<Message::MESSAGE_TYPE>(data[1]);
        message.size = data.mid(2, 2).toUShort();
        switch (message.type) {
        case Message::NUMBER:
            message.data = QVariant::fromValue( data.mid(4, message.size).toInt() );
            break;
        case Message::TEXT:
            message.data = QVariant::fromValue( QString::fromUtf8(data.mid(4, message.size)) );
            break;
        default:
            break;
        }
        emit newMessage(message);
    });
}

void MessageSerialPort::readData()
{
    if(!m_serialPort.open(QIODevice::ReadOnly)) {
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
