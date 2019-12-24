import QtQuick 2.0
import QtQuick.Controls 2.0

Item {
    property string name: ""
    property string login: ""
    property string password: ""
    property bool showPassword: false
    property bool editMode: false

    signal removeThis
    signal editingFinished

    onEditModeChanged: {
        if (editMode)
            showPassword = true

        if (!editMode)
            editingFinished()
    }

    Rectangle{
        id: background
        anchors.fill: parent
        z:-99
        border.width: 2
        border.color: "blue"
        radius: 8
    }

    Rectangle{
        id: nameSection
        z:-99
        x: background.x
        y: background.y

        height: parent.height / 2.0
        width: parent.width

        border.width: 2
        border.color: "blue"

        TextInput {
            id: nameTextInput
            text: name
            enabled: editMode
            height: parent.height
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            onAccepted: name = nameTextInput.text
            onFocusChanged: name = nameTextInput.text
        }

        Image {
            id: editButton
            source: "qrc:/media/more_horiz-24px.svg"
            fillMode: Image.Pad

            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 8

            MouseArea{
                anchors.fill: parent
                onClicked: menu.open()

                Menu {
                    id: menu

                    MenuItem {
                        text: editMode ? "Save" : "Edit"
                        onTriggered: editMode = !editMode
                    }
                    MenuItem {
                        text: "Remove"
                        onTriggered: removeThis()
                    }

                }
            }
        }
    }

    TextInput {
        id: loginTextInput
        text: showPassword ? login : hideString(login)
        enabled: editMode
        height: parent.height / 2.0
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        anchors.top: nameSection.bottom
        anchors.left: parent.left
        anchors.leftMargin: 4

        onAccepted: login = loginTextInput.text
        onFocusChanged: login = loginTextInput.text
    }

    Rectangle{
        id: fieldsBorder
        x: nameSection.width / 2
        height: nameSection.height - nameSection.border.width * 4
        width: 2

        anchors.top: nameSection.bottom
        anchors.topMargin: 2

        border.width: 1
        border.color: "blue"
    }

    TextInput {
        id: passwordTextInput
        text: showPassword ? password : hideString(password)
        enabled: editMode
        height: parent.height / 2.0
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        anchors.top: nameSection.bottom
        anchors.left: fieldsBorder.left
        anchors.leftMargin: 4

        onAccepted: password = passwordTextInput.text
        onFocusChanged: password = passwordTextInput.text
    }

    Image{
        source: showPassword ? "qrc:/media/visibility_off-24px.svg" : "qrc:/media/visibility-24px.svg"
        fillMode: Image.Pad

        height: parent.height / 2.0
        width : height

        anchors.top: nameSection.bottom
        anchors.right: parent.right

        MouseArea{
            anchors.fill: parent
            onClicked: {
                if (!editMode)
                    showPassword = !showPassword
            }
        }
    }

    function hideString(stringToHide){
        var hidingString = ""

        for (var i = 0; i < stringToHide.length; ++i)
            hidingString += "*"

        return hidingString
    }
}

