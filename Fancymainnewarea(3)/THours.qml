// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1


Rectangle{
   property alias text: textHours.text
   property alias font: textHours.font
   id: clockhours
   width: 151
   height: 160
   radius: 10
   color: "#FAF8F9"
   smooth: true
   gradient: Gradient {
           GradientStop { position: 0.4; color: "#FAF8F9" }
           GradientStop { position: 0.7; color: "lightgrey" }
           GradientStop { position: 0.8; color: "#c6c6c6" }
           GradientStop { position: 0.985; color: "#c6c6c6" }
           GradientStop { position: 0.99; color: "#E5E5E5" }
           GradientStop { position: 1; color: "#E5E5E5" }
       }
   Text{
       id: textHours
       //font.family: "Arial Narrow"
       width: 100
       x: 10
       y: 5
       text:"24"
       horizontalAlignment: Text.AlignHCenter
       font.pixelSize: parent.height-28
       style: Text.Raised;
       //style: Text.Sunken;
       styleColor: "white"
       smooth: true
       anchors.centerIn:parent
       z: 0
   }
}

