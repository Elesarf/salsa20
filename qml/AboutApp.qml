import QtQuick 2.5
import com.ass.crypter 1.0

Item {
    signal back()

    Version{
        id: version
    }


    Image
    {
        id: owl
        width: dp(240)
        height: dp(150)
        source: "qrc:/media/owlkey.png"

        anchors.top: parent.top
        anchors.topMargin: dp(36)

        anchors.horizontalCenter: parent.horizontalCenter
    }

    Text{
        id: aboutText
        width: parent.width - dp(24 * 2)
        height: parent.height

        anchors.top: owl.bottom
        anchors.topMargin: dp(36)

        text: "Salsa build number " + version.versionNumber() + "\r\n" +
              "Created by Alexey Fedchenko aka Elesar, Tver city, Russia.\r\n" +
              "email: elesarf@gmail.com"

        font.pointSize: 12
        color: "#ffffff"
        horizontalAlignment: Text.AlignHCenter

        wrapMode: TextInput.Wrap
    }

    Rectangle{
        width: dp(60)
        height: dp(60)
        radius: dp(30)
        color: "#004c40"

        anchors.left: parent.left
        anchors.leftMargin: dp(16)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: dp(16)

        Image{
            anchors.fill: parent
            mipmap: true
            autoTransform: true
            source: "qrc:/media/close-24px.svg"
            fillMode: Image.Pad
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                back()
            }
        }
    }
}
