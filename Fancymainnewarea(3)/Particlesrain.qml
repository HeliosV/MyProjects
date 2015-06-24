// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import Qt.labs.particles 1.0

Rectangle {
     id: rain
     width: 400
     height: 300
     color: "transparent"
     visible: false
     Particles {
         y: parent.height/2
         width: parent.width
         height: 30
         source: "images/drop_01.png"
         lifeSpan: 3000
         count: 1
         angle: 90
         //angleDeviation: 45
         velocity: 1
         //velocityDeviation: 10
         fadeInDuration: 100
         fadeOutDuration: 400
     }
     Particles {
         y: parent.height/2.5
         width: parent.width
         height: 30
         source: "images/drop_01.png"
         lifeSpan: 3000
         count: 1
         angle: 90
         //angleDeviation: 45
         velocity: 1
         //velocityDeviation: 10
         fadeInDuration: 100
         fadeOutDuration: 400
     }
     Particles {
         y: parent.height/2.3
         width: parent.width
         height: 30
         source: "images/drop_06.png"
         lifeSpan: 3000
         count: 1
         angle: 90
         //angleDeviation: 45
         velocity: 1
         //velocityDeviation: 10
         fadeInDuration: 100
         fadeOutDuration: 400
     }
     Particles {
         y: parent.height/2.7
         width: parent.width
         height: 30
         source: "images/drop_07.png"
         lifeSpan: 3000
         count: 1
         angle: 90
         //angleDeviation: 45
         velocity: 1
         //velocityDeviation: 10
         fadeInDuration: 100
         fadeOutDuration: 400
     }
     Particles {
         y: parent.height/2.1
         width: parent.width
         height: 30
         source: "images/drop_08.png"
         lifeSpan: 3000
         count: 1
         angle: 90
         //angleDeviation: 45
         velocity: 1
         //velocityDeviation: 10
         fadeInDuration: 100
         fadeOutDuration: 400
     }
     Particles {
         y: 0
         width: parent.width
         height: 10
         source: "images/rain_drop_little.png"
         lifeSpan: 2000
         count: 25
         angle: 90
         //angleDeviation: 45
         velocity: 800
         //velocityDeviation: 10
         fadeInDuration: 100
         fadeOutDuration: 200
     }
 }
