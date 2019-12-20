import QtQuick 2.5
import QtQuick.Controls 2.0
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

    PasswordDelegate{
        anchors.centerIn: parent
        width: 320
        height: 40
    }
}
