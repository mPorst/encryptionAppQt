import QtQuick 2.2
import QtCharts 2.2
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
//import QtCharts 2.0

Item {
    id: windoof
    objectName: "windoof"
    visible: true
    width: 640
    height: 480

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

            Text {
                id: labelToSomeTextArea
                width:240
                height:20
                anchors.bottom: someTextArea.top
                anchors.bottomMargin: 10
                anchors.left: someTextArea.left
                anchors.leftMargin: -20
                text: "File Preview:"
            }

            Text{
                id: someTextArea
                objectName: "someTextArea"
                width: 240
                height: 240
                anchors.left: passwordField.right
                anchors.leftMargin: 30
                anchors.top: parent.top
                anchors.topMargin: 80
                wrapMode:Text.Wrap
                text: "Here the file preview will be shown"
                //text: backend.graphValues.toString() // for debug purposes
            }

            /*
                Button {
                id: previewButton
                objectName: "previewButton"
                text: "preview file"
                anchors.right: someTextArea.left
                anchors.rightMargin: 30
                anchors.top: passwordField.bottom
                anchors.topMargin: 30
                anchors.verticalCenter: someTextArea.verticalCenter
                onClicked: {
                    backend.updateFilePreview(filename.text)
                }
                }
            */

            }
        Item {
            id: graphTab
            objectName: "graphTab"
            anchors.fill: parent

            ChartView {
                id: myChartview
                objectName: "chartview"
                theme: ChartView.ChartThemeDark
                title: "Character Distribution in File"
                width: 400
                height: 400
                anchors.centerIn: parent
                //legend.alignment: Qt.AlignBottom
                antialiasing: true

                BarSeries {
                    objectName: "barseries"
                    id: mySeries
                    //axisX: BarCategoryAxis { categories: ["2007", "2008", "2009", "2010", "2011"] }
                    axisX: BarCategoryAxis {categories: backend.xLabels }
                    axisY: ValueAxis { min: 0; max: backend.yMax }
                    BarSet {  label: backend.fileText; values: backend.graphValues; objectName: "barset"}
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
                    //afterwards may be set (if not preview stays empty, throws no error)
                    backend.updateFilePreview(filename.text)
                    backend.updateGraph(filename.text)
                }
                onRejected: {
                    console.log("canceled")
                }
            }
        Component.onCompleted: visible = true

}

