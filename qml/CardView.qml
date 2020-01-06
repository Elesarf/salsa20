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

    SwipeView{
        id: swipeView
        anchors.fill: parent
        interactive: false

        spacing: dp(10)

        CardList{
            id: cardList

            onExportData: swipeView.currentIndex = ++swipeView.currentIndex % swipeView.count
        }

        FilePicker {
            showDotAndDotDot: true
            onFolderSelected: {
                swipeView.currentIndex = --swipeView.currentIndex % swipeView.count
                cardView.folderSelected(path)
            }

            onBack: swipeView.currentIndex = --swipeView.currentIndex % swipeView.count
        }
    }
}
