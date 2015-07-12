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
    height: 700
    title: qsTr("Chess Game")

    property int moves: modelFile.moveCount()-1
    property int step_index: moves;

    Component.onCompleted: {
        load();
        console.log(modelFile.moveCount()-1);
    }

    FileIO {
        id: modelFile
        source: "saved_model.txt"
        onError: console.log(msg)
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("Game")
            MenuItem {
                text: qsTr("&New game")
                onTriggered: newGame();
            }
            MenuItem {
                text: qsTr("&Stop game")
                onTriggered: gameWindowLoaded.close()
            }
            MenuItem {
                text: qsTr("&Load game")
                onTriggered: {
                    load();
                }
            }
        }
        Menu{
            title: qsTr("&Move")
            MenuItem{
                text: qsTr("&Previous step")
                onTriggered: {
                    prevStep();
                }
            }
            MenuItem {
                text: qsTr("&Next step")
                onTriggered: {
                    nextStep();
                }
            }
        }
    }

    Rectangle {
        id: mainRec
        anchors.fill: parent
        color: "transparent"

        Column{
            id: loadedGameCol
            width: parent.width
            height: parent.height
            Rectangle{
                id: gameBoard
                width: parent.width
                height: parent.height/1.1
                color: "transparent"

                ChessFigures{
                    id: chessFigures
                    width: parent.width
                    height: parent.height
                }
            }
            Rectangle{
                id: buttonsRect
                width: parent.width
                height: mainRec.height/11
                color: "transparent"
                Row {
                    anchors.fill: parent
                    spacing: 5
                    Button{
                        id: prevMoveButton
                        text: "Previous move"
                        onClicked: {prevStep();}
                        width: buttonsRect.width/2
                        height: buttonsRect.height
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
                        id: nextMoveButton
                        text: "Next move"
                        onClicked: {nextStep();}
                        width: buttonsRect.width/2
                        height: buttonsRect.height
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
        }
    }

    function load(){
        chessFigures.currentModel = modelFile.readCurrentLine(step_index);
        console.log(chessFigures.currentModel);
        chessFigures.setModel();
    }

    function prevStep()
    {
        if (step_index === 0)
            return;
        chessFigures.currentModel = modelFile.readCurrentLine(step_index);
        console.log(chessFigures.currentModel);
        chessFigures.setModel();
        --step_index;
        console.log(step_index);
    }

    function nextStep()
    {
        if(step_index > moves)
            return;
        chessFigures.currentModel = modelFile.readCurrentLine(step_index);
        console.log(chessFigures.currentModel);
        chessFigures.setModel();
        ++step_index;
        console.log(step_index);
    }

    function newGame(){
        var component = Qt.createComponent("GameWindow.qml");
        var win = component.createObject(mainRec);
        gameWindowLoaded.hide();
    }
}

