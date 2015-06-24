// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: 40
    height: 40
    smooth: true
    color: "transparent"
    //border.width: 1
    //border.color: "white"
    property variant imag: "images/sunny.png"
    //property int weathercondition: 12
    Image {
        id: image
        clip: true
        source: imag;
        anchors.fill: parent
        anchors.topMargin: -12
        anchors.bottomMargin: 12
       // anchors.leftMargin: 20
       // anchors.rightMargin: -20
    }
}
