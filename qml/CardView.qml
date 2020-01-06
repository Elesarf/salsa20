import QtQuick 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0

Item{
    id: cardView
    function setModel(model){
        if (model !== null)
            cardList.model = model
    }

    signal folderSelected(string folder)
    signal fileSelected(string fileName)

    SwipeView{
        id: swipeView
        anchors.fill: parent
        interactive: false

        spacing: dp(10)

        Component.onCompleted: swipeView.currentIndex = ++swipeView.currentIndex % swipeView.count

        AboutApp{
            onBack: swipeView.currentIndex = ++swipeView.currentIndex % swipeView.count
        }

        CardList{
            id: cardList

            onExportData:{
                picker.showFiles = false
                swipeView.currentIndex = ++swipeView.currentIndex % swipeView.count
            }

            onImportData: {
                picker.showFiles = true
                swipeView.currentIndex = ++swipeView.currentIndex % swipeView.count
            }

            onAboutApp: swipeView.currentIndex = --swipeView.currentIndex % swipeView.count
        }

        FilePicker {
            id: picker
            showDotAndDotDot: true
            onFolderSelected: {
                swipeView.currentIndex = --swipeView.currentIndex % swipeView.count
                cardView.folderSelected(path)
            }

            onFileSelected: {
                swipeView.currentIndex = --swipeView.currentIndex % swipeView.count
                cardView.fileSelected(fileName)
            }

            onBack: swipeView.currentIndex = --swipeView.currentIndex % swipeView.count
        }
    }
}
