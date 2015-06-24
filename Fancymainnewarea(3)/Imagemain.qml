// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle{
    property string imagepath: "images/sunny.png"
Image {
    id:mainim
    source: imagepath
    smooth: true
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter
    width: weathweek.height/1.3
    height: weathweek.height/1.3

}
}
