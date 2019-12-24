import QtQuick 2.5
import QtQuick.Controls 2.0
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

    color: "grey"

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
            selectByMouse: true
            maximumLength: 32

            Rectangle{
                anchors.fill: parent
                border.width: 1
                border.color: "blue"
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
            height: 460
            spacing: 4

            Rectangle{
                anchors.fill: parent
                z:-99
                border.width: 1
                border.color: "blue"
            }

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

            footer: Rectangle{
                width: parent.width
                height: 40

                Image {
                    id: addIcon
                    source: "qrc:/media/add_circle_outline-24px.svg"

                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter

                    fillMode: Image.Pad
                }

                border.width: 2
                border.color: "blue"

                MouseArea{
                    anchors.fill: parent

                    onClicked: if (viewModel.readyToWork) cardList.model.add()
                }
            }

            footerPositioning: ListView.OverlayFooter
        }
    }
}
