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

    property int dpi: Screen.pixelDensity * 25.4

    function dp(x){
        if(dpi < 120) {
            return x; // Для обычного монитора компьютера
        } else {
            return x*(dpi/160);
        }
    }

    ViewModel{
        id: viewModel
    }

    Column{
        anchors.fill: parent
        spacing: dp(5)

        TextInput{
            id: masterPassInput
            width: parent.width
            height: dp(100)

            font.pointSize: 14
            color: "#ffffff"

            selectByMouse: true
            maximumLength: 32

            onAccepted: {
                viewModel.setMasterPassword(masterPassInput.text)
                viewModel.load()
                masterPassInput.focus = false
            }

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
        }

        ListView{
            id: cardList
            width: parent.width
            height: parent.height - masterPassInput.height - parent.spacing
            spacing: dp(8)
            clip: true
            Layout.alignment: Qt.AlignCenter
            Layout.preferredHeight: height

            model: viewModel.cardController.modelData
            delegate: PasswordDelegate{
                width: parent.width
                height: dp(250)

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
                height: dp(300)
                z: 2
                color: "#00796b"

                Rectangle{
                    width: dp(140)
                    height: dp(140)
                    radius: dp(70)
                    color: "#004c40"

                    anchors.right: parent.right
                    anchors.rightMargin: dp(40)
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: dp(40)

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
