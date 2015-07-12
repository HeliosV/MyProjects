import QtQuick 2.0
import QtGraphicalEffects 1.0
import FileIO 1.0
import QtQuick.Dialogs 1.1

Grid {
    id: chessGrid
    rows: 8
    columns: 8
    smooth: true
    property bool rotated: false

    property string currentModel: ""
    property string currentFigure: " "
    property string previousFigure: ""
    property variant modelContainer: []
    property bool isFirstMove: true
    property bool figureRotated: false

    states: [
        State {
            PropertyChanges { target: chessGrid; rotation: 180 }
            when: chessGrid.rotated
        }
    ]

    transitions: Transition {
        id: rotationAnimation
        RotationAnimation { duration: 1000; direction: RotationAnimation.Counterclockwise }
    }

    Timer {
        id: rotateTimer
        interval: 1000;
        running: false;
        repeat: false;
        onTriggered: rotateDesk();
    }

    Component.onCompleted:
    {
        var i;
        for (i = 0; i < chessFiguresModel.count; ++i)
        {
            currentModel+=chessFiguresModel.get(i).modelData; //add starting model data
        }
        modelContainer.push(currentModel);
    }

    MessageDialog {
        id: messageDialog
        title: "Chess info"
        text: "Check!"
        Component.onCompleted: visible = false
    }

    ChessFiguresModel{
        id: chessFiguresModel
    }

    FileIO {
        id: modelFile
        source: "saved_model.txt"
        onError: console.log(msg)
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

            property int rowIndex:Math.floor(index/8)
            color: index%2?(rowIndex%2?brightChessBoxColor:darkChessBoxColor):(rowIndex%2?darkChessBoxColor:brightChessBoxColor)

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
                states: [
                    State {
                        PropertyChanges { target: figure; rotation: 180 }
                        when: chessGrid.rotated
                    }
                ]
            }
            MouseArea{
                id: clickArea
                anchors.fill: parent
                onClicked: makeMoveTo(index)
            }
        }
    }

    function rotateDesk()
    {
        chessGrid.rotated = !chessGrid.rotated ? true : false;
        figureRotated = !figureRotated ? true : false;
    }

    property int getIndex: 0;

    function makeMoveTo(moveIndex)
    {
        currentModel = "";
        if (chessFiguresModel.get(moveIndex).modelData !== " " && currentFigure === " ")
        {
            currentFigure = chessFiguresModel.get(moveIndex).modelData;

            if (previousFigure === previousFigure.toLowerCase() && currentFigure === currentFigure.toUpperCase())//check whose turn
            {
                isFirstMove = false;
                getIndex = moveIndex;
                chessFiguresModel.remove(moveIndex)
                chessFiguresModel.insert(moveIndex, {"modelData": " "})
            }
            else if (previousFigure === previousFigure.toUpperCase() && currentFigure === currentFigure.toLowerCase() && !isFirstMove)//check whose turn
            {
                getIndex = moveIndex;
                chessFiguresModel.remove(moveIndex)
                chessFiguresModel.insert(moveIndex, {"modelData": " "})
            }
            else
            {
                currentFigure = " ";
                return;
            }
        }
        else
        {
            if (moveIndex === getIndex) // check whether figure was got and put on the same cell
            {
                chessFiguresModel.remove(moveIndex)
                chessFiguresModel.insert(moveIndex, {"modelData": currentFigure})
                currentFigure = " ";
            }
            else
            {
                if (checkDirections(currentFigure, moveIndex, getIndex))
                {
                    chessFiguresModel.remove(moveIndex)
                    chessFiguresModel.insert(moveIndex, {"modelData": currentFigure})
                    previousFigure = currentFigure;
                    //                    if (isCheck(currentFigure, moveIndex))
                    //                        messageDialog.visible = true;
                    currentFigure = " ";
                    //rotateTimer.start();
                }
                else
                    return;
            }
        }

        for (var i = 0; i < chessFiguresModel.count; ++i)
        {
            currentModel+=chessFiguresModel.get(i).modelData; //add current model data(model data on currnt move)
        }
        modelContainer.push(currentModel);
    }

    //chess pieces rules

    function checkFigurePath(put_index, get_index)
    {
        var diff = put_index - get_index;
        if (diff > 0)
        {
            if (diff%8 === 0)
            {
                for (var i = get_index; i < put_index; i+=8)
                {
                    if (chessFiguresModel.get(i).modelData !== " ")
                        return false;
                }
            }
            else if (diff%7 === 0)
            {

                for (var j = get_index; j < put_index; j+=7)
                {
                    if (chessFiguresModel.get(j).modelData !== " ")
                        return false;
                }
            }
            else if (diff%9 === 0)
            {
                for (var k = get_index; k < put_index; k+=9)
                {
                    if (chessFiguresModel.get(k).modelData !== " ")
                        return false;
                }
            }
        }
        else if (diff < 0)
        {
            if (diff%8 === 0)
            {
                for (var l = get_index; l > put_index; l-=8)
                {
                    if (chessFiguresModel.get(l).modelData !== " ")
                        return false;
                }
            }
            else if (diff%7 === 0)
            {
                for (var m = get_index; m > put_index; m-=7)
                {
                    if (chessFiguresModel.get(m).modelData !== " ")
                        return false;
                }
            }
            else if (diff%9 === 0)
            {
                for (var n = get_index; n > put_index; n-=9)
                {
                    if (chessFiguresModel.get(n).modelData !== " ")
                        return false;
                }
            }
        }
        return true;
    }
    //---------------------CHECK verification
    function isCheck(name, put_index)  //in development
    {
        if (name === "q" || name === "r")
        {
            for (var i = put_index; i <= 64; i+=8)
            {
                if (chessFiguresModel.get(i).modelData === "K")
                    return true;
            }
        }
        if (name === "b" || name === "q")
        {
            for (var j = put_index; j <= 64; j+=7)
            {
                if (chessFiguresModel.get(j).modelData === "K")
                    return true;
            }
        }
        if (name === "b" || name === "q")
        {
            for (var k = put_index; k <= 64; k+=9)
            {
                if (chessFiguresModel.get(k).modelData === "K")
                    return true;
            }
        }
        if (name === "Q" || name === "R")
        {
            for (var l = put_index; l >= 0; l-=8)
            {
                if (chessFiguresModel.get(l).modelData === "k")
                    return true;
            }
        }
        if (name === "Q" || name === "B")
        {
            for (var m = put_index; m >= 0; m-=7)
            {
                if (chessFiguresModel.get(m).modelData === "k")
                    return true;
            }
        }
        if (name === "Q" || name === "B")
        {
            for (var n = put_index; n >= 0; n-=9)
            {
                if (chessFiguresModel.get(n).modelData === "k")
                    return true;
            }
        }
        return false;
    }
    //------------

    function isPawnFirstMove(put_index, get_index)
    {
        if (put_index - get_index === 16 && get_index > 7 && get_index < 16)
            return true;
        else if (put_index - get_index === -16 && get_index > 47 && get_index < 56)
            return true;
        else
            return false;
    }

    function checkDirections(name, put_index, get_index)
    {
        console.log(get_index);
        console.log(put_index);

        if (name === "p" || name === "P") //Pawn rule
        {
            console.log("Pawn");
            if (isPawnFirstMove(put_index, get_index))
                return true;
            if ((checkFigurePath(put_index, get_index) && (name === "p" && put_index - get_index === 8 || //added checking name for preventing back move for pawns
                                                           name === "p" && chessFiguresModel.get(put_index).modelData !== " " && put_index - get_index === 7 ||
                                                           name === "p" && chessFiguresModel.get(put_index).modelData !== " " && put_index - get_index === 9)) ||
                    (checkFigurePath(put_index, get_index) && (name === "P" && put_index - get_index === -8 ||
                                                               name === "P" && chessFiguresModel.get(put_index).modelData !== " " && put_index - get_index === -7 ||
                                                               name === "P" && chessFiguresModel.get(put_index).modelData !== " " && put_index - get_index === -9)))
            {
                return true;
            }
            else
                return false;
        }
        if (name === "n" || name === "N") //Knight rule
        {
            console.log("Knight");
            if (put_index - get_index === 15 || put_index - get_index === -15 ||
                    put_index - get_index === 6 || put_index - get_index === -6 ||
                    put_index - get_index === 10 || put_index - get_index === -10 ||
                    put_index - get_index === 17 || put_index - get_index === -17)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if (name === "r" || name === "R") //Rook rule
        {
            console.log("Rook");
            if (checkFigurePath(put_index, get_index) && (get_index >= 0 && get_index < 8 && put_index >= 0 && put_index < 8 ||
                                                          get_index > 7 && get_index < 16 && put_index > 7 && put_index < 16 ||
                                                          get_index > 15 && get_index < 24 && put_index > 15 && put_index < 24 ||
                                                          get_index > 23 && get_index < 32 && put_index > 23 && put_index < 32 ||
                                                          get_index > 31 && get_index < 40 && put_index > 31 && put_index < 40 ||
                                                          get_index > 39 && get_index < 48 && put_index > 39 && put_index < 48 ||
                                                          get_index > 47 && get_index < 56 && put_index > 47 && put_index < 56 ||
                                                          get_index > 55 && get_index < 64 && put_index > 55 && put_index < 64 ||
                                                          (put_index - get_index)%8 === 0))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if (name === "b" || name === "B") //Bishop rule
        {
            console.log("Bishop");
            if (checkFigurePath(put_index, get_index) && (chessPiecesRptr.itemAt(get_index).color === chessPiecesRptr.itemAt(put_index).color) &&
                    (put_index - get_index)%7 === 0 ||
                    checkFigurePath(put_index, get_index) && (chessPiecesRptr.itemAt(get_index).color === chessPiecesRptr.itemAt(put_index).color) &&
                    (put_index - get_index)%9 === 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if (name === "k" || name === "K") //King rule
        {
            console.log("King");
            if (put_index - get_index === 1 || put_index - get_index === -1 ||
                    put_index - get_index === 7 || put_index - get_index === -7 ||
                    put_index - get_index === 8 || put_index - get_index === -8 ||
                    put_index - get_index === 9 || put_index - get_index === -9)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if (name === "q" || name === "Q") //Queen rule
        {
            console.log("Queen");
            if ((checkFigurePath(put_index, get_index)) && (get_index >= 0 && get_index < 8 && put_index >= 0 && put_index < 8 ||
                                                            get_index > 7 && get_index < 16 && put_index > 7 && put_index < 16 ||
                                                            get_index > 15 && get_index < 24 && put_index > 15 && put_index < 24 ||
                                                            get_index > 23 && get_index < 32 && put_index > 23 && put_index < 32 ||
                                                            get_index > 31 && get_index < 40 && put_index > 31 && put_index < 40 ||
                                                            get_index > 39 && get_index < 48 && put_index > 39 && put_index < 48 ||
                                                            get_index > 47 && get_index < 56 && put_index > 47 && put_index < 56 ||
                                                            get_index > 55 && get_index < 64 && put_index > 55 && put_index < 64 ||
                                                            (put_index - get_index)%8 === 0 ||
                                                            (chessPiecesRptr.itemAt(get_index).color === chessPiecesRptr.itemAt(put_index).color) &&
                                                            (put_index - get_index)%7 === 0 ||
                                                            (chessPiecesRptr.itemAt(get_index).color === chessPiecesRptr.itemAt(put_index).color) &&
                                                            (put_index - get_index)%9 === 0))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

    }
    // -----------------

    function setModel()
    {
        var j;
        for (j = 0; j < currentModel.length; ++j)
        {
            chessFiguresModel.remove(j)
            chessFiguresModel.insert(j, {"modelData": currentModel.charAt(j)})
        }
    }
}

