import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.3

ApplicationWindow {
    property string brightChessBoxColor: "#ecf0f1"
    property string darkChessBoxColor:"#2c3e50"

    id: applicationWindow
    objectName: "applicationWindow"
    visible: true
    width: 640
    height: 640
    title: qsTr("Chess Game")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&New game")
                onTriggered: newGame();
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    property variant win;

    Rectangle {
        id: mainRec
        objectName:"mainRec"
        anchors.fill: parent
        color: "transparent"

        ChessBoard{
            id: chessBoxes
            anchors.fill: parent
        }

        Column{
            anchors.centerIn: parent
            spacing: 10
            width: parent.width/3
            height: parent.height/2
            Button{
                id: newGameButton
                text: "New game"
                onClicked: {newGame();}
                width: parent.width
                height: parent.height/5
                style: ButtonStyle {
                      label: Text {
                        renderType: Text.NativeRendering
                        verticalAlignment: Text.AlignVCenter
                        font.family: "Helvetica"
                        horizontalAlignment: Text.AlignHCenter
                        font.pointSize: 20
                        color: "#2c3e50"
                        text: control.text
                    }
                }
            }
            Button{
                id: loadGameButton
                text: "Load game"
                onClicked: {loadGame();}
                width: parent.width
                height: parent.height/5
                style: ButtonStyle {
                      label: Text {
                        renderType: Text.NativeRendering
                        verticalAlignment: Text.AlignVCenter
                        font.family: "Helvetica"
                        horizontalAlignment: Text.AlignHCenter
                        font.pointSize: 20
                        color: "#2c3e50"
                        text: control.text
                    }
                }
            }
        }
    }
    function newGame(){
        var component = Qt.createComponent("GameWindow.qml");
        win = component.createObject(mainRec);
    }

    function loadGame(){
        var component = Qt.createComponent("LoadedGame.qml");
        win = component.createObject(mainRec);
    }
}
