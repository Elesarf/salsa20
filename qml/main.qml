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

    ListView{
        id: cardList
        anchors.centerIn: parent
        width: 420
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
            Component.onCompleted: console.log(index)
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

                onClicked: cardList.model.add()
            }
        }

        footerPositioning: ListView.OverlayFooter
    }

    Button{
        id: saveButton
        text: qsTr("save")
        anchors.bottom: parent.bottom

        onClicked: viewModel.save()
    }

    Button{
        id: loadButton
        text: qsTr("load")
        anchors.bottom: parent.bottom
        anchors.left: saveButton.right
        anchors.leftMargin: 4

        onClicked: viewModel.load()
    }

    Button{
        id: setMasterPasswordButton
        text: qsTr("set pass")
        anchors.bottom: parent.bottom
        anchors.left: loadButton.right
        anchors.leftMargin: 4

        onClicked: viewModel.setMasterPassword("qwertyui")
    }
}
