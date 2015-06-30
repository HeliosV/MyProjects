import QtQuick 2.3
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.3
import QtQuick.Dialogs 1.2
import FileIO 1.0

ApplicationWindow {
    id: gameWindowLoaded
    objectName: "gameWindow"
    visible: true
    width: 640
    height: 640
    title: qsTr("Chess Game")

    Component.onCompleted: {load()}

    FileIO {
        id: gameFile
        source: "saved_game.txt"
        onError: console.log(msg)
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("Game")
            MenuItem {
                text: qsTr("&Stop game")
                onTriggered: gameWindowLoaded.close()
            }
        }
        Menu{
            title: qsTr("&Move")
            MenuItem{
                text: qsTr("&Previous step")
                onTriggered: console.log("Prevoius step")
            }
            MenuItem {
                text: qsTr("&Next step")
                onTriggered: console.log("Next step")
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
    function load(){
        chessFigures.currentModel = gameFile.read();
        console.log(chessFigures.currentModel);
        chessFigures.load();
    }
}

