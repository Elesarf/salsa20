import QtQuick 2.0

Item {

    property string name: "name"
    property string value: "value"
    property bool showPassword: true

    Rectangle{
        id: background
        anchors.fill: parent
        z:-99
        border.width: 2
        border.color: "blue"
    }

    Text {
        id: nameText
        text: name
        height: parent.height
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 4
    }

    Rectangle{
        id: border
        x: parent.width / 2
        height: parent.height - background.border.width * 4
        width: 2
        anchors.verticalCenter: parent.verticalCenter

        border.width: 1
        border.color: "blue"
    }

    Text {
        id: valueText
        text: showPassword ? value : hideString(value)
        height: parent.height
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: border.left
        anchors.leftMargin: 4
    }

    Image{
        source: showPassword ? "qrc:/media/visibility_off-24px.svg" : "qrc:/media/visibility-24px.svg"
        fillMode: Image.Pad

        height: parent.height - background.border.width * 4
        width : height

        anchors.right: parent.right
        anchors.rightMargin: 4
        anchors.verticalCenter: parent.verticalCenter

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

