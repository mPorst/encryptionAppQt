import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1

Item {
    width: 200
    height: 30
    id: pwInput
    property alias echomode: passwordInput.echoMode
    property alias text: passwordInput.text
    signal clicked(int echomode)

    TextField {
        //property int echomode: 0
        id: passwordInput
        //echoMode: TextInput.Password
        text: "example Text"
        anchors.centerIn: parent
        }
    RadioButton {
        id: clearButton
        anchors.top: passwordInput.bottom
        anchors.left: passwordInput.left
        anchors.topMargin: 10
        text: "show password"
        checked: false
        onClicked: {
            passwordInput.echoMode = (clearButton.checked-1)*(-2) // hacking the radio button
            //console.log("Clicked button" + TextInput.Password)
            console.log(passwordInput.echoMode)
        }
    }
    }
