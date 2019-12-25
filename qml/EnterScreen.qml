import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item{

    property var model: null

    signal close
    signal openStorage

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

            Text{
                id: popupLabel
                width: parent.width
                height: dp(14)

                anchors.top: parent.top

                text: model.cardController.isDataFileAvailable() ? "Enter master password:" : "Enter new master password:"
                font.pointSize: 12
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter

                wrapMode: TextInput.Wrap
            }

            TextInput{
                id: masterPassInput
                width: parent.width
                height: dp(40)
                anchors.top: popupLabel.bottom
                anchors.topMargin: dp(12)

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
                        close()
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
                        masterPassInput.focus = false
                        model.setMasterPassword(masterPassInput.text)
                        model.load()

                        unlockPopup.close()
                        openStorage()
                    }
                }
            }
        }
    }
}
