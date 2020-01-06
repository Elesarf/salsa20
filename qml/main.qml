import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Window 2.1
import com.ass.crypter 1.0
import "."

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 640
    height: 560
    minimumWidth: 320
    minimumHeight: 240
    title: qsTr("sc")

    color: "#00796b"

    property int dpi: Screen.pixelDensity * 25.4

    function dp(x){
        if(dpi < 120) {
            return x;
        } else {
            return x*(dpi/160);
        }
    }

    ViewModel{
        id: viewModel

        Component.onCompleted: cardList.setModel(viewModel.cardController.modelData)
    }

    StackLayout{
        id: stack
        anchors.fill: parent

        EnterScreen{
            width: parent.width
            height: parent.height
            model: viewModel

            onClose: mainWindow.close()
            onOpenStorage:{
                stack.currentIndex = (++stack.currentIndex) % stack.count
                cardList.enabled = true
            }
        }

        CardView{
            id: cardList
            width: parent.width
            height: parent.height
            enabled: false

            onFolderSelected:{
                viewModel.exportData(folder)
            }

            onFileSelected: {
                viewModel.importData(fileName)
            }
        }
    }
}
