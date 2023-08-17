import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Server App")

    Connections {
        target: server
        function onNewMessage(ba){
            listModelMessages.append({
                                        message: ba + ""
                                     })
        }
    }
    ColumnLayout{
        anchors.fill: parent
        ListView{
            Layout.fillHeight: true
            Layout.fillWidth: true
            clip: true
            model: ListModel{
                id: listModelMessages
                ListElement{
                    message: "Welcome to server"
                }
            }
            delegate: ItemDelegate{
                text: message
            }
            ScrollBar.vertical: ScrollBar{}
        }
        RowLayout{
            TextField{
                id: textFieldMessage
                placeholderText: qsTr("Ваше сообщение...")
                Layout.fillWidth: true
                onAccepted: buttonSend.clicked()
            }
            Button{
                id: buttonSend
                text: qsTr("Отправить")
                onClicked: {
                    server.sendMessage(textFieldMessage.text)
                    textFieldMessage.clear()
                }
            }
        }
    }
}
