import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Window 2.1
import com.ass.crypter 1.0
import "."

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 640
    height: 560
    minimumWidth: 320
    minimumHeight: 240
    title: qsTr("sc")

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

    StackLayout{
        id: stack
        anchors.fill: parent

        Rectangle{
            id: unlockScreen
            width: parent.width
            height: parent.height
            color: "black"
            opacity: 0.1
            z: -100

            Popup{
                id: unlockPopup
                width: dp(400)
                height: dp(140)
                x: Math.round((parent.width - width) / 2)
                y: Math.round((parent.height - height) / 2)

                modal: true
                focus: true
                closePolicy: Popup.NoAutoClose

                background: Rectangle{color: "#00796b"}

                Component.onCompleted: open()

                TextInput{
                    id: masterPassInput
                    width: parent.width
                    height: dp(50)

                    font.pointSize: 14
                    color: "#ffffff"
                    verticalAlignment: Text.AlignVCenter

                    wrapMode: TextInput.Wrap

                    selectByMouse: true
                    maximumLength: 32

                    Rectangle{
                        anchors.fill: parent
                        color: "#004c40"
                        z: -99
                    }

                    Button{
                        anchors.top: masterPassInput.bottom
                        anchors.topMargin: dp(12)

                        Image
                        {
                            id: closeButton
                            source: "qrc:/media/close-24px.svg"

                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter

                            fillMode: Image.Pad
                        }

                        onClicked: {
                            mainWindow.close()
                        }
                    }

                    Button{
                        anchors.top: parent.bottom
                        anchors.topMargin: dp(12)
                        anchors.right: parent.right

                        Image
                        {
                            id: openButton
                            source: "qrc:/media/lock_open-24px.svg"

                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter

                            fillMode: Image.Pad
                        }

                        onClicked: {
                            viewModel.setMasterPassword(masterPassInput.text)
                            viewModel.load()
                            masterPassInput.focus = false

                            unlockPopup.close()
                            stack.currentIndex = (++stack.currentIndex) % stack.count
                        }
                    }
                }
            }
        }

        ListView{
            id: cardList
            width: parent.width
            spacing: dp(8)
            clip: true
            Layout.alignment: Qt.AlignCenter
            Layout.preferredHeight: height

            model: viewModel.cardController.modelData

            delegate: PasswordDelegate{
                width: parent.width
                height: dp(100)

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
                height: dp(100)
                z: 2
                color: "#00796b"

                Rectangle{
                    width: dp(80)
                    height: dp(80)
                    radius: dp(40)
                    color: "#004c40"

                    anchors.right: parent.right
                    anchors.rightMargin: dp(8)
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: dp(8)

                    Image {
                        anchors.fill: parent
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
