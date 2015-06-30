import QtQuick 2.0
import QtGraphicalEffects 1.0

Grid {
    id: chessGrid
    rows: 8
    columns: 8

    property string currentModel: ""
    property string currentFigure: " "


    ChessFiguresModel{
        id: chessFiguresModel
    }

    Repeater
    {
        id:chessPiecesRptr
        model: chessFiguresModel

        delegate:
            Rectangle {
            id:chessBox
            smooth: true
            antialiasing: true
            width: chessGrid.width/8
            height: chessGrid.height/8

            color: "transparent"

            Image
            {
                id: figure
                source: {
                    modelData!=" "?(modelData===modelData.toUpperCase()?
                                        "images/white/"+modelData+".png":"images/black/"+modelData+".png"):""
                }
                width: parent.width/3;
                height: parent.height/2;
                anchors.centerIn: parent
            }
            MouseArea{
                id: clickArea
                anchors.fill: parent
                onClicked: makeMoveTo(index)
            }
        }
    }

    property int i: 0;
    function makeMoveTo(moveIndex)
    {
        currentModel = "";
        if (chessFiguresModel.get(moveIndex).modelData !== " ")
        {
            currentFigure = chessFiguresModel.get(moveIndex).modelData;
            console.log(currentFigure);
            chessFiguresModel.remove(moveIndex)
            chessFiguresModel.insert(moveIndex, {"modelData": " "})
        }
        else
        {
            chessFiguresModel.remove(moveIndex)
            chessFiguresModel.insert(moveIndex, {"modelData": currentFigure})
            currentFigure = " ";
        }
        for (i = 0; i < chessFiguresModel.count; ++i)
        {
            currentModel+=chessFiguresModel.get(i).modelData;
            console.log(chessFiguresModel.get(i).modelData);
        }
    }
    property int j: 0;
    function load()
    {
        for (j = 0; j < currentModel.length; ++j)
        {
            chessFiguresModel.remove(j)
            chessFiguresModel.insert(j, {"modelData": currentModel.charAt(j)})
        }
    }
}

