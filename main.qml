import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import Modules 1.0
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Medlinx-test")

    Control {
        anchors.fill: parent
        padding: 10
        contentItem: ColumnLayout {
            DelegateItem {
                Layout.fillWidth: true
                address: 'Адрес'
                type: 'Тип'
                size: 'Размер'
                messageData: 'Данные'
                fontBold: true
            }
            Control {
                Layout.fillWidth: true
                Layout.fillHeight: true
                contentItem: ListView {
                    id: listView
                    anchors.fill: parent
                    clip: true
                    model: MessageModel { id: messageModel }
                    ScrollBar.vertical: ScrollBar {
                        active: true
                    }

                    delegate: DelegateItem {
                        implicitWidth: listView.width
                        address: display.address
                        type: {
                            switch(display.type) {
                            case Message.NUMBER:
                                return 'Число'
                            case Message.TEXT:
                                return 'Текст'
                            }
                            return 'Пусто'
                        }
                        size: display.size
                        messageData: display.data
                    }
                }
                background: Rectangle {
                    border.color: 'black'
                    radius: 10
                }
            }
            Item {
                Layout.fillWidth: true
                Layout.preferredHeight: childrenRect.height
                RowLayout {
                    width: parent.width
                    Item {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 1
                    }
                    Button {
                        padding: 10
                        text: 'Очистить'
                        font.pixelSize: 16
                        onClicked: {
                            messageModel.clear()
                        }
                    }

                    Button {
                        padding: 10
                        text: messageSerialPort.isReading ? 'Стоп' : 'Считать /dev/tnt0'
                        font.pixelSize: 16
                        onClicked: {
                            if (messageSerialPort.isReading) {
                                messageSerialPort.stop()
                            } else {
                                messageSerialPort.readData()
                            }
                        }
                    }
                }
            }
        }
    }

    MessageSerialPort {
        id: messageSerialPort
        onNewMessage: {
            messageModel.insert(message)
        }
        onError: {
            messageDialog.informativeText = text
            messageDialog.open()
        }
    }

    MessageDialog {
        id: messageDialog
        icon: StandardIcon.Critical
        title: 'Ошибка'
        text: 'Возникла ошибка у serialport:'
    }
}

