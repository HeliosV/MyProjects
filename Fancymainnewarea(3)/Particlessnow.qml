// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import Qt.labs.particles 1.0

Rectangle
{
     id: snow
     width: 500
     height: 300
     color: "transparent"
     visible: false
     Rectangle
     {
         id: maincontainer
         width: snow.width
         height: snow.height
         color: "transparent"
         Column
         {
             spacing: 0
     Rectangle
     {
         id: cloudcontainer
         width: snow.width
         height: snow.height/3
         color: "transparent"
         anchors.horizontalCenter: parent.horizontalCenter
         Row
         {
             spacing: -80
             anchors.horizontalCenter: parent.horizontalCenter
             Rectangle
             {
                 width: cloudcontainer.width/2
                 height: cloudcontainer.height
                 color: "transparent"

                 Image
                 {
                     id: snowcloud
                     width: 250
                     height: 150
                     source: "images/cloud_03.png"
                     smooth: true

                 }
             }
             Rectangle
             {
                 width: cloudcontainer.width/2
                 height: cloudcontainer.height
                 color: "transparent"
                 Image
                 {
                     id: snowcloud2
                     width: 250
                     height: 150
                     source: "images/cloud_03.png"
                     mirror: true
                     smooth: true
                 }
             }
         }
     }
     Rectangle
     {
         id: snowcontainer
         width: 350
         height: 300
         color: "transparent"
         anchors.horizontalCenter: parent.horizontalCenter
     Particles
     {
         y: 0
         width: parent.width
         height: 30
         source: "images/snow_01.png"
         lifeSpan: 5000
         count: 10
         angle: 70
         angleDeviation: 45
         velocity: 30
         velocityDeviation: 10
         ParticleMotionWander
         {
             xvariance: 30
             pace: 100
         }
     }
     Particles
     {
         y: 0
         width: parent.width
         height: 30
         source: "images/snow_03.png"
         lifeSpan: 5000
         count: 10
         angle: 70
         angleDeviation: -45
         velocity: 30
         velocityDeviation: 10
         ParticleMotionWander
         {
             xvariance: 30
             pace: 100
         }
     }

     Particles
     {
         y: 0
         width: parent.width
         height: 30
         source: "images/snow_05.png"
         lifeSpan: 5000
         count: 10
         angle: 70
         angleDeviation: 45
         velocity: 30
         velocityDeviation: 10
         ParticleMotionWander
         {
             xvariance: 30
             pace: 100
         }
     }

     Particles
     {
         y: 0
         width: parent.width
         height: 30
         source: "images/snow_07.png"
         lifeSpan: 5000
         count: 10
         angle: 70
         angleDeviation: -45
         velocity: 30
         velocityDeviation: 10
         ParticleMotionWander
         {
             xvariance: 30
             pace: 100
         }
     }
     Particles
     {
         y: 0
         width: parent.width
         height: 30
         source: "images/snow_08.png"
         lifeSpan: 5000
         count: 10
         angle: 70
         angleDeviation: 45
         velocity: 30
         velocityDeviation: 10
         ParticleMotionWander
         {
             xvariance: 30
             pace: 100
         }
     }
     Particles
     {
         y: 0
         width: parent.width
         height: 30
         source: "images/flake_02.png"
         lifeSpan: 2000
         count: 3
         angle: 70
         angleDeviation: -45
         velocity: 30
         velocityDeviation: 10
         ParticleMotionWander
         {
             xvariance: 30
             pace: 100
         }
     }
     Particles
     {
         y: 0
         width: parent.width
         height: 30
         source: "images/flake_01.png"
         lifeSpan: 5000
         count: 8
         angle: 70
         angleDeviation: 45
         velocity: 30
         velocityDeviation: 10
         ParticleMotionWander
         {
             xvariance: 30
             pace: 80
         }
     }
     Particles
     {
         y: 0
         width: parent.width
         height: 30
         source: "images/flake_03.png"
         lifeSpan: 1000
         count: 2
         angle: 70
         angleDeviation: -45
         velocity: 30
         velocityDeviation: 10
         fadeInDuration: 100
         fadeOutDuration: 400
         ParticleMotionWander
         {
             xvariance: 30
             pace: 50
         }
     }
     }
         }

 }
     }
