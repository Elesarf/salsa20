import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ListView{
    id: cardList
    width: parent.width
    spacing: dp(8)
    clip: true
    Layout.alignment: Qt.AlignCenter
    Layout.preferredHeight: height

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

