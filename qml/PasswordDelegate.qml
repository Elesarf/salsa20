import QtQuick 2.0

Item {
    property string name: ""
    property string login: ""
    property string password: ""
    property bool showPassword: false
    property bool editMode: false

    signal removeThis

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

        Text {
            id: nameText
            text: name
            height: parent.height
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Image {
            id: removeButton
            source: "qrc:/media/remove_circle_outline-24px.svg"
            fillMode: Image.Pad

            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 4

            MouseArea{
                anchors.fill: parent

                onClicked: removeThis()

            }
        }
    }

    Text {
        id: loginText
        text: showPassword ? login : hideString(login)
        height: parent.height / 2.0
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        anchors.top: nameSection.bottom
        anchors.left: parent.left
        anchors.leftMargin: 4
    }

    Rectangle{
        id: border
        x: nameSection.width / 2
        height: nameSection.height - nameSection.border.width * 4
        width: 2

        anchors.top: nameSection.bottom
        anchors.topMargin: 2

        border.width: 1
        border.color: "blue"
    }

    Text {
        id: valueText
        text: showPassword ? password : hideString(password)
        height: parent.height / 2.0
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        anchors.top: nameSection.bottom
        anchors.left: border.left
        anchors.leftMargin: 4
    }

    Image{
        source: showPassword ? "qrc:/media/visibility_off-24px.svg" : "qrc:/media/visibility-24px.svg"
        fillMode: Image.Pad

        height: parent.height / 2.0
        width : height

        anchors.top: nameSection.bottom
        anchors.right: parent.right
        anchors.rightMargin: 4

        MouseArea{
            anchors.fill: parent

            onClicked: showPassword = !showPassword
        }
    }

    function hideString(stringToHide){
        var hidingString = ""

        for (var i = 0; i < stringToHide.length; ++i)
            hidingString += "*"

        return hidingString
    }
}

