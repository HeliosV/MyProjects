import QtQuick 2.3
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.3
import QtQuick.Dialogs 1.2
import FileIO 1.0

ApplicationWindow {
    id: gameWindow
    objectName: "gameWindow"
    visible: true
    width: 640
    height: 640
    title: qsTr("Chess Game")

    FileIO {
        id: modelFile
        source: "saved_model.txt"
        onError: console.log(msg)
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("Game")
            MenuItem {
                text: qsTr("&Stop game")
                onTriggered: gameWindow.close()
            }
            MenuItem {
                text: qsTr("&Save Game")
                onTriggered: {
                    modelFile.clear();
                    var i;
                    for (i = 0; i < chessFigures.modelContainer.length; ++i)
                        modelFile.write(chessFigures.modelContainer[i]);
                }
            }
        }
    }

    Rectangle {
        id: mainRec
        anchors.fill: parent
        color: "transparent"

        ChessBoard{
            id: chessBoard
            width: parent.width
            height: parent.height
            anchors.fill: parent
        }

        ChessFigures{
            id: chessFigures
            width: parent.width
            height: parent.height
            anchors.fill: parent
        }
    }
}
