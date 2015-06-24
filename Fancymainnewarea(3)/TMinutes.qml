// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1



Rectangle{
   property alias text: textMinutes.text
   property alias font: textMinutes.font
   id: clockmin
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
       id: textMinutes
       x:15
       y:5
       font.family: "Arial Narrow"
       text: "00"
       font.pixelSize: parent.height-28
       style: Text.Raised;
       //style: Text.Sunken;
       styleColor: "white"
       anchors.centerIn:parent
       horizontalAlignment: Text.AlignHCenter



   }

}

