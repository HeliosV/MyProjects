import QtQuick 2.2

Grid {
    id: chessGrid
    rows: 8
    columns: 8

    Repeater
    {
        id:chessBoxesRptr
        model: 64
        delegate: Rectangle {
            id:chessBox
            smooth: true
            antialiasing: true
            width: parent.width/8
            height: parent.height/8

            property int rowIndex:Math.floor(index/8)
            color: index%2?(rowIndex%2?brightChessBoxColor:darkChessBoxColor):(rowIndex%2?darkChessBoxColor:brightChessBoxColor)

//            states: State {
//                name: "rotated"
//                PropertyChanges { target: chessGrid; rotation: 180 }
//            }

//            transitions: Transition {
//                RotationAnimation { duration: 1000; direction: RotationAnimation.Counterclockwise }
//            }
        }
    }
}

