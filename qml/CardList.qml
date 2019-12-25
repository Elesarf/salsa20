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
        height: dp(92)
        z: 2
        color: "transparent"

        Rectangle{
            width: dp(60)
            height: dp(60)
            radius: dp(30)
            color: "#004c40"

            anchors.right: parent.right
            anchors.rightMargin: dp(16)
            anchors.bottom: parent.bottom
            anchors.bottomMargin: dp(16)


            Rectangle{
                width: dp(2)
                height: dp(30)

                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter

                border.width: dp()
                border.color: "black"
            }

            Rectangle{
                width: dp(30)
                height: dp(2)

                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter

                border.width: dp(3)
                border.color: "black"
            }

            MouseArea{
                anchors.fill: parent
                onClicked: if (viewModel.readyToWork) cardList.model.add()
            }
        }
    }
}

