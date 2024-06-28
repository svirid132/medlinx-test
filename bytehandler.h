#ifndef BYTEHANDLER_H
#define BYTEHANDLER_H

#include <QByteArray>

template<typename T> T translateByteArrayToNum(QByteArray bytes){
    T num = 0;
    size_t size = sizeof(T);
    for (int i = 0; i < size; ++i) {
        num = num << 8;
        num += (unsigned char)bytes[i];
    }

    return num;
}

#endif // BYTEHANDLER_H
