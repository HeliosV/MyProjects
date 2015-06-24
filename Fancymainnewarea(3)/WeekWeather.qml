 // import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import Qt.labs.particles 1.0

Rectangle {
    property string areastate: "unpressed"
    id: canvas2
    width: 480
    height: 640
    color: "transparent"

    Rectangle {
        id: weathweek
        state: areastate
        width: canvas2.width/1.2
        height: canvas2.height/3
        anchors.horizontalCenter : parent.horizontalCenter
        y: canvas2.width/12
        anchors.margins: 250
        border.color: "#7C8DA9"
        border.width: 3
        radius: 10
        opacity: 1
        smooth: true
        color: "#475D81"
        gradient: Gradient {
                GradientStop { position: 0; color: "#DEDEDE"; }
                GradientStop { position: 0.17; color: "#DEDEDE" }
                GradientStop { position: 0; color: "#A7ADB7" }
                GradientStop { position: 0.03; color: "#A5ABB5" }
                GradientStop { position: 0.05; color: "#9BA2AF" }
                GradientStop { position: 0.08; color: "#838C9E" }
                GradientStop { position: 0.11; color: "#78839A" }
                GradientStop { position: 0.14; color: "#717E96" }
                GradientStop { position: 0.17; color: "#6A7993" }
                GradientStop { position: 0.18; color: "#475D81" }
            }

        states:
        [
            State
            {
                name: "pressed";
                PropertyChanges { target: weathweek;  height: canvas2.height/8;}
                PropertyChanges { target: downcontainer; visible: false; }
                PropertyChanges { target: htemp; font.pixelSize: weathweek.height/5.7; }
                PropertyChanges { target: ltemp; font.pixelSize: weathweek.height/5.7; }
                PropertyChanges { target: citty; font.pixelSize: weathweek.height/4.5; }
                PropertyChanges { target: bigtemp; font.pixelSize: weathweek.height/1.12;}
                PropertyChanges { target: htemp; anchors.topMargin: weathweek.height/4;}
                PropertyChanges { target: ltemp; anchors.topMargin: weathweek.height/1.2;}
                PropertyChanges { target: citty; anchors.topMargin: weathweek.height/2;}
                PropertyChanges { target: mainsunny; anchors.bottomMargin: weathweek.height/12  }
                PropertyChanges { target: mainim; width: weathweek.height*2.05; height: weathweek.height*2.05  }
            },
            State
            {
                name: "unpressed";
                PropertyChanges { target: weathweek;  height: canvas2.height/3;}
            }
        ]
        transitions:
        [
            Transition
            {
                 NumberAnimation { properties: "height"; easing.type: Easing.InOutQuad;}
                 NumberAnimation { properties: "anchors.bottomMargin"; easing.type: Easing.InOutQuad; }
                 NumberAnimation { properties: "anchors.topMargin"; easing.type: Easing.InOutQuad; }
            }
        ]


Column{
  id: container


   Rectangle{
       id: uppercontainer
       width: weathweek.width
       height: weathweek.height/2.5
       color: "transparent"
          Row{
             Rectangle{
                width: weathweek.width/3
                height: weathweek.height/2.5
                color: "transparent"
                  Text{
                      id: htemp
                      text: "H: 34°"
                      font.family: "Helvetica Neue"
                      font.pixelSize: weathweek.height/15
                      color: "white"
                      smooth: true
                      anchors.fill: parent
                      horizontalAlignment: Text.AlignHCenter
                      verticalAlignment:  Text.AlignVCenter
                      anchors.bottomMargin: weathweek.height/7
                  }

                  Text{
                      id: ltemp
                      text: "L: 16°"
                      font.family: "Helvetica Neue"
                      font.pixelSize: weathweek.height/15
                      color: "white"
                      smooth: true
                      anchors.fill: parent
                      horizontalAlignment: Text.AlignHCenter
                      verticalAlignment:  Text.AlignVCenter
                      anchors.topMargin: weathweek.height/7
                  }

                  Text{
                      id: citty
                      text: "Undefined"
                      font.family: "Helvetica Neue"
                      font.bold: true
                      font.pixelSize: weathweek.height/12
                      color: "white"
                      smooth: true
                      anchors.fill: parent
                      horizontalAlignment: Text.AlignHCenter
                      verticalAlignment:  Text.AlignVCenter
                  }
         }


             Rectangle{
                  //property alias mainimgsource: mainimage.mainimg
                  width: weathweek.width/3
                  height: weathweek.height/2.5
                  color: "transparent"
              /* VisualItemModel{
                   id: mainimage
                   //property alias mainimg: mainim.source
                  Image{
                      id:mainim
                      source: "images/sunny.png"
                      smooth: true
                      anchors.horizontalCenter: parent.horizontalCenter
                      anchors.verticalCenter: parent.verticalCenter
                      width: weathweek.height/1.3
                      height: weathweek.height/1.3

                 }
               }*/
             }


              Rectangle{
                  id: currenttemp
                  width: weathweek.width/3
                  height: weathweek.height/2.5
                  color: "transparent"
                  radius: 10
                  Text{
                      id: bigtemp
                      text: "34°"
                      font.family: "Arial"
                      font.pixelSize: weathweek.height/3
                      color: "white"
                      smooth: true
                      anchors.fill: parent
                      horizontalAlignment : Text.AlignRight
                      verticalAlignment: Text.AlignTop
                      anchors.topMargin: -5
                  }
              }
          }


        XmlListModel {
            id: weathModel0
            source: "http://xml.weather.yahoo.com/forecastrss/UPXX0016_c.xml"
            query: "/rss/channel"
            namespaceDeclarations: "declare namespace yweather = 'http://xml.weather.yahoo.com/ns/rss/1.0';"
            XmlRole { name: "city"; query: "yweather:location/@city/string()" }
            XmlRole { name: "curtemp"; query: "item/yweather:condition/@temp/string()" }
            XmlRole { name: "weathcond0"; query: "item/yweather:condition/@code/string()" }
            XmlRole { name: "lowtemp1"; query: "item/yweather:forecast[1]/@low/string()" }
            XmlRole { name: "hightemp1"; query: "item/yweather:forecast[1]/@high/string()" }
            onStatusChanged: {
                var forecaster0 = weathModel0.get(0);
                bigtemp.text = forecaster0.curtemp + '°';
                citty.text = forecaster0.city;
                htemp.text = 'H: ' + forecaster0.hightemp1 + '°';
                ltemp.text = 'L: ' + forecaster0.lowtemp1 + '°';
                var weath = forecaster0.weathcond0;
                var currentDate = new Date();
                var hours = currentDate.getHours();

                if (parseInt(weath) == 26){
                    mainim.source ="images/Cloudy.png";
               }
                else if
                (parseInt(weath) == 27){
                    mainim.source ="images/mostlycloudyn.png";
               }
                else if
                (parseInt(weath) == 28){
                    mainim.source ="images/MostlyCloudy.png";
               }
                else if
                (parseInt(weath) == 29){
                    mainim.source ="images/Cloudyn.png";
               }
                if (parseInt(weath) == 30){
                    mainim.source ="images/PartlyCloudy.png";
               }
                else if
                (parseInt(weath) == 32){
                    mainim.source ="images/sunny.png";
               }
                else if
                (parseInt(weath) == 44){
                    mainim.source ="images/PartlyCloudy.png";
               }
                else if
                (parseInt(weath) == 11){
                    mainim.source ="images/Rain.png";
               }
                else if
                (parseInt(weath) == 12){
                    mainim.source ="images/Showers.png";
               }
                else if
                (parseInt(weath) == 46){
                    mainim.source ="images/Snow.png";
               }
                else if
                (parseInt(weath) == 16){
                    mainim.source ="images/Snow.png";
               }
                else if
                (parseInt(weath) == 34){
                    mainim.source ="images/Sunny.png";
               }
               // else if
                //(parseInt(weath) == 20){
                 //   mainim.source = "images/fog.png";
               //}
                else if
                (parseInt(weath) == 20){
                    mainim.source = "images/fogn.png";
               } 
                else if
                (parseInt(weath) == 5){
                    mainim.source = "images/snowrain.png";
               }
                else if
                (parseInt(weath) == 14){
                    mainim.source = "images/Snow.png";
               }
                else if
                (parseInt(weath) == 41){
                    mainim.source = "images/Snow.png";
               }
                else if
                (parseInt(weath) == 7){
                    mainim.source = "images/snowrain.png";
               }
            }
        }
    }



   Rectangle{
       id: downcontainer
       width: weathweek.width
       height: weathweek.height/1.65
       color: "transparent"


      Rectangle{ color: "#435079"; width: weathweek.width-2; height: 1; smooth: true;anchors.horizontalCenter: downcontainer.horizontalCenter}

           Rectangle{
               id: horline
               width: weathweek.width-4
               height: weathweek.height/7
               color: "#536998";
               smooth: true;
               anchors.horizontalCenter: downcontainer.horizontalCenter
               y:1
       }

           Rectangle{

               id: weathercontainer
               width: downcontainer.width
               height: downcontainer.height
               //border.color: "red"
               color: "transparent"
               Row {
                    id: rowV

                       Repeater {
                           id: repeaterV
                           model: weathModel1
                           Rectangle { 
                               id: vertlinecontainer 
                               width: weathercontainer.width/repeaterV.count;
                               height: weathercontainer.height
                               color: "transparent"

                               Rectangle{
                                   width: weathweek.width/repeaterV.count
                                   height: weathweek.height/7
                                   color: "transparent";

                                   Text{
                                       id: dayofweek
                                       text: day
                                       font.bold: true
                                       font.pixelSize: parent.height/2
                                       color: "white"
                                       anchors.horizontalCenter: parent.horizontalCenter
                                       anchors.verticalCenter: parent.verticalCenter
                                       font.capitalization: Font.AllUppercase;
                                   }
                               }


                               Weathercell{
                                   widt: vertlinecontainer.width
                                   heigt: vertlinecontainer.height
                                   Imagecell {
                                       id:littim1
                                       parent: vertlinecontainer
                                       width: vertlinecontainer.width/2
                                       height: vertlinecontainer.width/2
                                       anchors.horizontalCenter: parent.horizontalCenter
                                       anchors.verticalCenter: parent.verticalCenter
                                       function imageset(WeatherCondition){
                                           switch (WeatherCondition) {
                                             case "46":
                                                 return "images/Snow.png"
                                             case "26":
                                                 return "images/Cloudy.png"
                                             case "27":
                                                 return "images/mostlycloudyn.png"
                                             case "28":
                                                 return "images/MostlyCloudy.png"
                                             case "29":
                                                 return "images/Cloudyn.png"
                                             case "30":
                                                 return "images/PartlyCloudy.png"
                                             case "32":
                                                 return "images/sunny.png"
                                             case "44":
                                                 return "images/PartlyCloudy.png"
                                             case "11":
                                                 return "images/Rain.png"
                                             case "12":
                                                 return "images/Showers.png"
                                             case "16":
                                                 return "images/Snow.png"
                                             case "34":
                                                 return "images/sunny.png"
                                             case "5":
                                                 return "images/snowrain.png"
                                             case "7":
                                                 return "images/snowrain.png"
                                             case "14":
                                                 return "images/Snow.png"
                                             case "41":
                                                 return "images/Snow.png"
                                             default:
                                                 return "images/sunny.png"
                                           }

                                       }
                                       imag: imageset(weathcond1)
                                   }

                                   Daytempcell{
                                       id: daytemp
                                       parent: vertlinecontainer
                                       anchors.horizontalCenter: parent.horizontalCenter
                                       anchors.verticalCenter: parent.verticalCenter
                                       text: hightemp1 + '°'
                                       otstupotimage: vertlinecontainer.height/3.5
                                   }

                                   Nighttempcell{
                                       id: nighttemp
                                       parent: vertlinecontainer
                                       anchors.horizontalCenter: parent.horizontalCenter
                                       anchors.verticalCenter: parent.verticalCenter
                                       text: lowtemp1 + '°'
                                       otstupotimage: vertlinecontainer.height/1.5
                                   }
                                 }


                               Rectangle{
                                   id: verticalline
                                   color: "#435079";
                                   width: 1;
                                   height: weathercontainer.height-20;
                                   smooth: true;
                                   y:weathercontainer.height/30
                                   //anchors.fill: parent
                                   anchors.topMargin: 5
                                   //anchors.horizontalCenter: vertlinecontainer.horizontalCenter
                                   visible: index !==0;
                           }
                         }
                       }
                     }



               XmlListModel {
                   id: weathModel1
                   source: "http://xml.weather.yahoo.com/forecastrss/UPXX0016_c.xml"
                   query: "/rss/channel/item/yweather:forecast"
                   namespaceDeclarations: "declare namespace yweather = 'http://xml.weather.yahoo.com/ns/rss/1.0';"
                   XmlRole { name: "day"; query: "@day/string()" }
                   XmlRole { name: "lowtemp1"; query: "@low/string()" }
                   XmlRole { name: "hightemp1"; query: "@high/string()" }
                   XmlRole { name: "weathcond1"; query: "@code/string()" }
                   onStatusChanged: {

                       var currentDate = new Date();
                       var dayD = currentDate.getDate();
                       var hours = currentDate.getHours();
                       var forecaster = weathModel1.get(0);
                       var weathimag = "images/Cloudy.png";
                       var weath = forecaster.weathcond1;
                       //console.log(mainimage.objectName)


                  }
                }
              }
            }
      }
     Rectangle{
         id: mainsunny
         width: 100
         height: 100
         color: "transparent"
         anchors.horizontalCenter: parent.horizontalCenter
         anchors.fill: parent
         anchors.bottomMargin: weathweek.height/1.64
         Image{
             id:mainim
             source: "images/sunny.png"
             smooth: true
             width: weathweek.height/1.3
             height: weathweek.height/1.3
             anchors.horizontalCenter: parent.horizontalCenter
             anchors.verticalCenter: parent.verticalCenter
             anchors.fill: parent.fill
        }
     }

     Rectangle
     {
            width: weathweek.width
            height: weathweek.height
            color: "transparent"
            //MouseArea
            //{
            //    id: mousearea
            //    anchors.fill: parent
            //    onClicked:
            //    {
                    //weathweek.state = weathweek.state == "unpressed" ? "pressed" : "unpressed";
            //    }
            //}
     }
/*ListView{
    id: imloader
    model: mainimage
    //delegate: Loader{ sourceComponent:  mainimage}
    //sourceComponent: mainimage
    //delegate: Image{source: mainim.source }
    anchors.fill: parent
    //anchors.top: parent.bottom
    anchors.bottomMargin: weathweek.height
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter
}*/
    }
  }










