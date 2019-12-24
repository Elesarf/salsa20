import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import com.ass.crypter 1.0
import "."

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 640
    height: 560
    minimumWidth: 320
    minimumHeight: 240
    title: qsTr("tracking JSON pleer")

    color: "#00796b"

    ViewModel{
        id: viewModel
    }

    Column{
        anchors.fill: parent
        spacing: 4

        TextInput{
            id: masterPassInput
            width: parent.width
            height: 25

            font.pointSize: 14
            color: "#ffffff"

            selectByMouse: true
            maximumLength: 32

            Rectangle{
                anchors.fill: parent
                color: "#004c40"
                z: -99

                Image
                {
                    id: openButton
                    source: "qrc:/media/lock_open-24px.svg"

                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right

                    fillMode: Image.Pad

                    MouseArea{
                        anchors.fill: parent

                        onClicked: {
                            viewModel.setMasterPassword(masterPassInput.text)
                            viewModel.load()
                            masterPassInput.focus = false
                        }
                    }
                }
            }

            onAccepted: viewModel.setMasterPassword(text)
        }

        ListView{
            id: cardList
            width: parent.width
            height: parent.height - masterPassInput.height - parent.spacing
            spacing: 8
            clip: true
            Layout.alignment: Qt.AlignCenter
            Layout.preferredHeight: height

            model: viewModel.cardController.modelData
            delegate: PasswordDelegate{
                width: parent.width
                height: 80

                name: cardName
                login: cardLogin
                password: cardPassword

                onRemoveThis: cardList.model.removeRows(index, 1)
                onEditingFinished: {
                    cardName = name
                    cardLogin = login
                    cardPassword = password

                    viewModel.save()
                    viewModel.load()
                }
            }

            footerPositioning: ListView.OverlayFooter
            footer: Rectangle{
                width: parent.width
                height: 70
                z: 2
                color: "#00796b"

                Rectangle{
                    width: 50
                    height: 50
                    radius: 30
                    color: "#004c40"

                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 10

                    Image {
                        id: addIcon
                        source: "qrc:/media/add_circle_outline-24px.svg"

                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter

                        fillMode: Image.Pad
                    }

                    MouseArea{
                        anchors.fill: parent
                        onClicked: if (viewModel.readyToWork) cardList.model.add()
                    }
                }
            }
        }
    }
}
