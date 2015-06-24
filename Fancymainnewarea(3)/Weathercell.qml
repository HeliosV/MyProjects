// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1


Rectangle {
    property int widt
    property int heigt
    smooth: true
    color: "transparent"
    //border.width: 1
    border.color: "red"
    property alias text: text1.text
    Text {
        id: text1
        clip: true
        //text: "Text"
        color: "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment:  Text.AlignVCenter
        anchors.fill: parent
        anchors.topMargin: 17
        anchors.bottomMargin: 20
        //anchors.leftMargin: 5
        //anchors.rightMargin: 5
        font.bold: true
        font.pixelSize: parent.height-6

    }
}

