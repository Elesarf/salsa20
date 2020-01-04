import QtQuick 2.5
import QtQuick.Controls 2.0
import Qt.labs.folderlistmodel 2.1
import Qt.labs.platform 1.0

Item {
	id:picker
    signal fileSelected(string fileName)
    signal folderSelected(string path)
    signal back()

    property bool showDotAndDotDot: true
    property bool showHidden: false
	property bool showDirsFirst: true
    property string folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
	property string nameFilters: "*.*"

    function clearHistory(){
        folder = StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
    }

	function currentFolder() {
		return folderListModel.folder;
	}

	function isFolder(fileName) {
		return folderListModel.isFolder(folderListModel.indexOf(folderListModel.folder + "/" + fileName));
    }

	function canMoveUp() {
		return folderListModel.folder.toString() !== "file:///";
	}

	function onItemClick(fileName) {

        if(!isFolder(fileName)) {
			return;
		}

		if(fileName === ".." && canMoveUp()) {
            folderListModel.folder = folderListModel.parentFolder
        } else if(fileName !== ".") {
            if(folderListModel.folder.toString() === "file:///") {
                folderListModel.folder += fileName
            } else {
                folderListModel.folder += "/" + fileName
            }
        }
	}

	FolderListModel {
        id:  folderListModel
        showDotAndDotDot: picker.showDotAndDotDot
		showHidden: picker.showHidden
		showDirsFirst: picker.showDirsFirst
		folder: picker.folder
		nameFilters: picker.nameFilters
    }

    ListView {
        id: view
        anchors.fill: parent
		model: folderListModel
        header: Rectangle {
            width: parent.width
            height: dp(24)

            color: "transparent"

            Text {
                id: filePath
                text: folderListModel.folder.toString().replace("file:///", "../")
                renderType: Text.NativeRendering
                elide: Text.ElideMiddle
                font.italic: true
                font.bold: true
                verticalAlignment: Text.AlignVCenter
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                anchors.top: parent.top
                font.pixelSize: dp(14)
            }
        }

        footerPositioning: ListView.OverlayFooter
        footer: Rectangle{
            width: parent.width
            height: dp(92)
            z: 2
            color: "transparent"

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
                        clearHistory()
                    }
                }
            }

            Rectangle{
                width: dp(60)
                height: dp(60)
                radius: dp(30)
                color: "#004c40"

                anchors.right: parent.right
                anchors.rightMargin: dp(16)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: dp(16)

                Image{
                    anchors.fill: parent
                    mipmap: true
                    autoTransform: true
                    source: "qrc:/media/done-24px.svg"
                    fillMode: Image.Pad
                }

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        folderSelected(currentFolder())
                    }
                }
            }
        }

        delegate: Component {
			id: fileDelegate
            Item {
                height: dp(48)
                width: parent.width
                enabled: isFolder(fileNameText.text)
                visible: enabled

                Rectangle {
					anchors.fill: parent

                    color: "#48a999"
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            onItemClick(fileNameText.text)
                        }
                    }

					Text {
						id: fileNameText
						height: width
						anchors.left: image.right
						anchors.top: parent.top
						anchors.bottom: parent.bottom
						anchors.right: parent.right
                        text: fileName
						verticalAlignment: Text.AlignVCenter
					}

					Image {
						id: image
                        height: dp(24)
						width: height
						anchors.left: parent.left
                        anchors.leftMargin: dp(12)
						anchors.verticalCenter: parent.verticalCenter
                        source: isFolder(fileNameText.text) ? "qrc:/media/ic_folder_open_black_48dp.png" : ""
					}
				}
			}
        }
	}
}
