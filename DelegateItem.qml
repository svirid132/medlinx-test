import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Modules 1.0

Rectangle {
    id: root
    implicitHeight: childrenRect.height
    property string address: ''
    property string type: ''
    property string size: ''
    property string messageData: ''
    property color textColor: 'black'
    property bool fontBold: false
    color: 'transparent'
    Control {
        id: control
        width: root.width
        padding: 10
        contentItem: Item {
            implicitWidth: control.availableWidth
            implicitHeight: childrenRect.height
            RowLayout {
                width: parent.implicitWidth
                CustomLabel {
                    Layout.preferredWidth: 80
                    horizontalAlignment: Text.AlignHCenter
                    text: root.address
                    color: root.textColor
                    font.bold: root.fontBold
                }
                CustomLabel {
                    Layout.preferredWidth: 80
                    horizontalAlignment: Text.AlignHCenter
                    text: root.type
                    color: root.textColor
                    font.bold: root.fontBold
                }
                CustomLabel {
                    horizontalAlignment: Text.AlignHCenter
                    Layout.preferredWidth: 80
                    text: root.size
                    color: root.textColor
                    font.bold: root.fontBold
                }
                CustomLabel {
                    horizontalAlignment: Text.AlignHCenter
                    Layout.fillWidth: true
                    text: root.messageData
                    color: root.textColor
                    font.bold: root.fontBold
                    wrapMode: Text.Wrap
                }
            }
        }
    }
}
