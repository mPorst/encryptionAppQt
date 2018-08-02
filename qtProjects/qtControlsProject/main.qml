import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
//import QtCharts 2.0

ApplicationWindow {
    id: windoof
    objectName: "windoof"
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    // TABBAR

    TabBar {
        id: bar
        objectName: "bar"
        width: windoof.width
        TabButton {
            text: qsTr("encrypt")
        }
        TabButton {
            text: qsTr("graph")
        }
    }

    StackLayout {
        width: parent.width
        height: parent.height
        currentIndex: bar.currentIndex
        Item {
            id: homeTab
            Button {
                id: fileButton
                text: "choose file"
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.leftMargin: 30
                anchors.topMargin: 80
                onClicked: {
                    fileDialog.open()
                }
                }

            Text {
            id: filename
                text: "no file chosen yet"
                anchors.left: fileButton.left
                anchors.top: fileButton.bottom
                anchors.topMargin: 10
            }

            Button {
                id: encryptButton
                anchors.top: filename.bottom
                anchors.topMargin: 20
                anchors.left: fileButton.left
                text: "encrypt!"
                onClicked: {
                    backend.encrypt(filename.text, passwordField.text)
                }
            }

            PasswordTextInput {
                id: passwordField
                echomode: TextInput.Password
                text: "my valid text"
                anchors.left: encryptButton.right
                anchors.leftMargin: 10
                anchors.top: encryptButton.top
            }
    }
        Item {
            id: graphTab

            Text{
                id: someTextArea
                objectName: "someTextArea"
                width: 240
                height: 240
                anchors.centerIn: parent
                wrapMode:Text.Wrap
                text: "Here the file preview will be shown"
            }

            Button {
                id: previewButton
                objectName: "previewButton"
                text: "preview file"
                anchors.right: someTextArea.left
                anchors.rightMargin: 30
                anchors.verticalCenter: someTextArea.verticalCenter
                onClicked: {
                    backend.updateFilePreview(filename.text)
                }

            }

            }
    }



    // hidden

    FileDialog {
                id: fileDialog
                title: "Please choose a file"
                folder: shortcuts.home
                onAccepted: {
                    console.log("You chose: " + fileDialog.fileUrls)
                    filename.text = fileDialog.fileUrl
                }
                onRejected: {
                    console.log("canceled")
                }
            }
        Component.onCompleted: visible = true

}

