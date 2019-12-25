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
        border.width: 1
    }

    Rectangle{
        anchors.fill: parent
        color: "#48a999"
        z:-99
    }

    Rectangle{
        id: nameSection
        z:-99
        x: background.x
        y: background.y

        height: parent.height / 2.0
        width: parent.width

        color: "#004c40"

        TextInput {
            id: nameTextInput
            x: parent.x + dp(8)
            text: name
            enabled: editMode
            height: parent.height
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter

            font.pointSize: 14
            color: "#ffffff"

            selectByMouse: true

            onAccepted: name = nameTextInput.text
            onFocusChanged: name = nameTextInput.text
        }

        Image {
            id: editButton
            source: "qrc:/media/more_horiz-24px.svg"
            fillMode: Image.Pad

            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: dp(28)

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

        font.pointSize: 14
        color: "#ffffff"

        selectByMouse: true

        anchors.top: nameSection.bottom
        anchors.left: parent.left
        anchors.leftMargin: dp(8)

        onAccepted: login = loginTextInput.text
        onFocusChanged: login = loginTextInput.text
    }

    Rectangle{
        id: fieldsBorder
        x: nameSection.width / 2
        height: nameSection.height - nameSection.border.width * dp(8 * 2)
        width: 2

        anchors.top: nameSection.bottom
        anchors.topMargin: dp(8)

        border.width: 1
        border.color: "#004c40"
    }

    TextInput {
        id: passwordTextInput
        text: showPassword ? password : hideString(password)
        enabled: editMode
        height: parent.height / 2.0
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        font.pointSize: 14
        color: "#ffffff"

        selectByMouse: true

        anchors.top: nameSection.bottom
        anchors.left: fieldsBorder.left
        anchors.leftMargin: dp(8)

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
        anchors.rightMargin: dp(16)

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

        for (var i = 0; i < 9; ++i)
            hidingString += "*"

        return hidingString
    }
}

