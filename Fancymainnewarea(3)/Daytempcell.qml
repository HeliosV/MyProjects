// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: daytemp
    width: 40
    height: 20
    smooth: true
    color: "transparent"
    //border.width: 1
    //border.color: "white"
    property alias text: text1.text
    property int otstupotimage : 45
    Text {
        id: text1
        color: "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment:  Text.AlignVCenter
        anchors.fill: parent
        anchors.topMargin: daytemp.otstupotimage
        font.bold: true
        font.pixelSize: parent.height

    }
}
