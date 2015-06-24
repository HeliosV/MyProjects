// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: nighttemp
    width: 40
    height: 20
    smooth: true
    color: "transparent"
    //border.width: 1
    //border.color: "white"
    property alias text: text2.text
    property int otstupotimage : 85
    Text {
        id: text2
        //clip: true
        //text: "Text"
        color: "#7E96DE"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment:  Text.AlignVCenter
        anchors.fill: parent
        anchors.topMargin: nighttemp.otstupotimage
        //anchors.bottomMargin: 20
        //anchors.leftMargin: 25
        //anchors.rightMargin: -20
        font.bold: true
        font.pixelSize: parent.height-6

    }
}
