// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import Qt.labs.particles 1.0

Rectangle
{
    id: canvas
    width: 480
    height: 640
    color: "transparent"
    property int seconds : 3

    Image
    {
        id: logo
        source: "images/holes.png"
        anchors.centerIn: parent

    }
    Flipable
    {
         id: flipable
         width: parent.width
         height: parent.height
         anchors.horizontalCenter : canvas.horizontalCenter
         property bool flipped: false

         transform: Rotation
         {
             id: rotation
             origin.x: flipable.width/2
             origin.y: flipable.height/3
             axis.x: 0; axis.y: 1; axis.z: 0      // set axis.y to 1 to rotate around y-axis
             angle: 0   // the default angle
         }

         back: WeekWeather
         {
             id: weathweek
             areastate: "unpressed"
         }

         states: State
         {
             name: "back"
             PropertyChanges { target: rotation; angle: 180 }
             when: flipable.flipped
         }

         transitions: Transition
         {
             NumberAnimation { target: rotation; property: "angle"; duration: 1000 }
         }

         MouseArea
         {
             id: mainmousearea
             width: canvas.width/1.143
             height: canvas.height/2.78
             x: 30
             y: 50
             enabled: true
             onDoubleClicked:
             {
                 flipable.flipped = !flipable.flipped;
                 snowtimer.stop();
             }
             onClicked:
             {
                 snowtimer.start();
                 if (flipable.flipped == true)
                     weathweek.areastate = weathweek.areastate == "unpressed" ? "pressed" : "unpressed"
             }
         }
         Timer
         {
             id: snowtimer
             interval: 700; running: false; repeat: false
             onTriggered:
             {
                      //if (flipable.flipped == true)
                        //weathweek.areastate = "unpressed"
             }
         }

          front:   Rectangle{
                        Particlessnow
                        {
                            id: snow
                            z:3;
                            anchors.horizontalCenter: parent.horizontalCenter
                            y: -50
                        }
                        Particlesrain
                        {
                            id: rain
                            z:3;
                            anchors.horizontalCenter: parent.horizontalCenter
                            y: -50
                        }
                        id: clockbg
                        width: canvas.width/1.143
                        height: canvas.height/2.78
                        anchors.horizontalCenter : flipable.horizontalCenter
                        y: canvas.width/10
                        border.color: "#696969"
                        radius: 10
                        color: Qt.rgba(79/255, 78/255, 78/255, 0.8)
                        smooth: true

                        Rectangle
                        {
                                 id: anchous
                                 anchors.fill: parent
                                 anchors.topMargin: -27
                                 anchors.leftMargin: 42
                                 anchors.rightMargin: 249
                                 anchors.bottomMargin: 550
                                 radius: 16
                                 color: "#c6c6c6"

                                 Rectangle
                                 {
                                     anchors.fill: parent
                                     border.width: 1
                                     radius: 10

                                     Rectangle
                                     {
                                         id: anch
                                         height: 20
                                         width: textHours.width-6
                                         radius: 16
                                         color: "lightgrey"
                                         smooth: true
                                         x:2
                                         gradient: Gradient {
                                                 GradientStop { position: 0; color: "grey" }
                                                 GradientStop { position: 0.01; color: "grey" }
                                                 GradientStop { position: 0.4; color: "#E6E6E6" }
                                             }
                                          }
                                       }
                                    }

                        Rectangle {
                                 id: anchous2
                                 anchors.fill: parent
                                 anchors.topMargin: -27
                                 anchors.leftMargin: 231
                                 anchors.rightMargin: 74
                                 anchors.bottomMargin: 550
                                 radius: 16
                                 color: "#c6c6c6"

                                 Rectangle {
                                     anchors.fill: parent
                                     border.width: 1
                                     radius: 10

                                     Rectangle {
                                         id: anch2
                                         height: 20
                                         width: textMinutes.width-6
                                         radius: 16
                                         color: "#c6c6c6"
                                         smooth: true
                                         x:2
                                         gradient: Gradient {
                                                 GradientStop { position: 0; color: "grey" }
                                                 GradientStop { position: 0.01; color: "grey" }
                                                 GradientStop { position: 0.4; color: "#E6E6E6" }
                                             }
                                           }
                                         }
                                       }
                 Column{
                     id: container
                     spacing: 10
                     Rectangle{
                         id: uppercontainer1
                         width: clockbg.width
                         height: clockbg.height/2
                         color: "transparent"
                         //border.color: "red"

                         Row{
                             spacing: -20
                             anchors.horizontalCenter : parent.horizontalCenter
                             Rectangle{
                                 id: hoursrect
                                 width: uppercontainer1.width/2
                                 height: uppercontainer1.height
                                 color: "transparent"
                                 //border.color: "white"
                                 THours{
                                     id: textHours
                                     font.family: "Arial Narrow"
                                     anchors.horizontalCenter : parent.horizontalCenter
                                     anchors.verticalCenter: parent.verticalCenter
                                 } 
                             }
                             Rectangle{
                                 id: minutesrect
                                 width: uppercontainer1.width/2
                                 height: uppercontainer1.height
                                 color: "transparent"
                                 //border.color: "blue"
                                 TMinutes{
                                     id: textMinutes;
                                     anchors.horizontalCenter : parent.horizontalCenter
                                     anchors.verticalCenter: parent.verticalCenter
                                 }
                             }
                         }
                     }

                     Rectangle{
                         id: downcontainer
                         width: clockbg.width
                         height: clockbg.height/2
                         color: "transparent"
                         //border.color: "green"
                         Row{
                             Rectangle{
                                 id: cityandconditions
                                 width: downcontainer.width/3
                                 height: downcontainer.height
                                 color: "transparent"
                                 //border.color: "yellow"
                                 Text{
                                     id: city
                                     font.family: "Arial Narrow"
                                     text:"N/A"
                                     font.pixelSize: 18
                                     color: "white"
                                     font.bold: true
                                     anchors.fill: parent
                                     horizontalAlignment : Text.AlignLeft
                                     verticalAlignment: Text.AlignBottom
                                     anchors.bottomMargin: 55
                                     anchors.leftMargin: 15

                                 }

                                 Text{
                                     id: weath
                                     font.family: "Arial Narrow"
                                     text: "N/A"
                                     font.pixelSize: 16
                                     color: "white"
                                     font.bold: true
                                     anchors.fill: parent
                                     horizontalAlignment : Text.AlignLeft
                                     verticalAlignment: Text.AlignBottom
                                     anchors.bottomMargin: 35
                                     anchors.leftMargin: 15
                                 }

                             }
                             Rectangle{
                                 id: mainimage
                                 width: downcontainer.width/3
                                 height: downcontainer.height
                                 color: "transparent"
                                 //border.color: "grey"
                                     Image {
                                          id:sun
                                           source: "images/sunny.png"
                                           anchors.horizontalCenter: parent.horizontalCenter
                                           anchors.verticalCenter: parent.verticalCenter
                                           anchors.fill: parent.fill
                                           width: clockbg.width/2.624
                                           height: clockbg.width/2.624
                                           smooth: true
                                           y:50
                                       }
                             }
                             Rectangle{
                                 id: dateandtemp
                                 width: downcontainer.width/3
                                 height: downcontainer.height
                                 color: "transparent"
                                 //border.color: "brown"
                                 Text{
                                     id: dateD
                                     font.family: "Arial Narrow"
                                     text:""
                                     font.pixelSize: 16
                                     color: "white"
                                     font.bold: true
                                     anchors.fill: parent
                                     horizontalAlignment : Text.AlignRight
                                     verticalAlignment: Text.AlignTop
                                     anchors.topMargin: 30
                                     anchors.rightMargin: 55
                                 }

                                 Text{
                                     id: dateM
                                     font.family: "Arial Narrow"
                                     text:"Aug"
                                     font.pixelSize: 16
                                     color: "white"
                                     font.bold: true
                                     anchors.fill: parent
                                     horizontalAlignment : Text.AlignRight
                                     verticalAlignment: Text.AlignTop
                                     anchors.topMargin: 30
                                     anchors.rightMargin: 28
                                 }

                                 Text{
                                     id: dateDN
                                     font.family: "Arial Narrow"
                                     text:"8"
                                     font.pixelSize: 16
                                     color: "white"
                                     font.bold: true
                                     anchors.fill: parent
                                     horizontalAlignment : Text.AlignRight
                                     verticalAlignment: Text.AlignTop
                                     anchors.topMargin: 30
                                     anchors.rightMargin: 15
                                 }



                                 Text{
                                     id: temp
                                     font.family: "Helvetica Neue"
                                     text:"64°"
                                     font.pixelSize: 35
                                     color: "white"
                                     anchors.fill: parent
                                     horizontalAlignment : Text.AlignRight
                                     verticalAlignment: Text.AlignBottom
                                     anchors.bottomMargin: 20
                                     anchors.rightMargin: 55

                                 }

                                 Text{
                                     id: tempmax
                                     font.family: "Arial"
                                     text:"H: 72°"
                                     font.pixelSize: 15
                                     color: "white"
                                     font.bold: true
                                     anchors.fill: parent
                                     horizontalAlignment : Text.AlignRight
                                     verticalAlignment: Text.AlignBottom
                                     anchors.bottomMargin: 40
                                     anchors.rightMargin: 15

                                 }

                                 Text{
                                     id: tempmin
                                     font.family: "Arial"
                                     text:"L: 54°"
                                     font.pixelSize: 15
                                     color: "white"
                                     font.bold: true
                                     anchors.fill: parent
                                     horizontalAlignment : Text.AlignRight
                                     verticalAlignment: Text.AlignBottom
                                     anchors.bottomMargin: 20
                                     anchors.rightMargin: 15

                                 }

                             }


     Timer {
              interval: 500; running: true; repeat: true
              onTriggered:  {
        var currentTime = new Date();
        var hours = currentTime.getHours();
        var minutes = currentTime.getMinutes();

        if (minutes < 10)
        {
            minutes = "0" + minutes;
        }
        if (hours >= 10)
        {
            hours.horizontalAlignment = Text.AlignLeft;
        }
        if (minutes >= 10 & minutes < 20)
        {
            minutes.horizontalAlignment = Text.AlignLeft;
        }
        // partofday.text = hours < 12 ? "AM" : "PM"
        textHours.text = hours;
        textMinutes.text = minutes;
        }
     }

     Timer {
              interval: 500; running: true; repeat: true
              onTriggered:  {
        var currentDate = new Date();
        var day = currentDate.getDay();
        var dayD = currentDate.getDate();
        var month = currentDate.getMonth();
        var weekday=new Array(7);
        weekday[0]="Sun,";
        weekday[1]="Mon,";
        weekday[2]="Tue,";
        weekday[3]="Wed,";
        weekday[4]="Thu,";
        weekday[5]="Fri,";
        weekday[6]="Sat,";

        var monthN=new Array(11);
        monthN[0]="Jan";
        monthN[1]="Feb";
        monthN[2]="Mar";
        monthN[3]="Apr";
        monthN[4]="May";
        monthN[5]="Jun";
        monthN[6]="Jul";
        monthN[7]="Aug";
        monthN[8]="Sep";
        monthN[9]="Oct";
        monthN[10]="Nov";
        monthN[11]="Dec";


        dateD.text = weekday[day];
        dateM.text = monthN[month];
        dateDN.text =" " + dayD
              }
     }


     XmlListModel
     {
         id: weathModel
         source: "http://xml.weather.yahoo.com/forecastrss/UPXX0016_c.xml"
         query: "/rss/channel"
         namespaceDeclarations: "declare namespace yweather = 'http://xml.weather.yahoo.com/ns/rss/1.0';"
         XmlRole { name: "city"; query: "yweather:location/@city/string()" }
         XmlRole { name: "condition"; query: "item/yweather:condition/@text/string()" }
         XmlRole { name: "code"; query: "item/yweather:condition/@code/string()" }
         XmlRole { name: "currenttemp"; query: "item/yweather:condition/@temp/string()" }
         XmlRole { name: "temperaturemax"; query: "item/yweather:forecast[1]/@high/string()" }
         XmlRole { name: "temperaturemin"; query: "item/yweather:forecast[1]/@low/string()" }
         onStatusChanged:
         {
             var currentDate = new Date();
             var dayD = currentDate.getDate();
             var hours = currentDate.getHours();
             var forecast = weathModel.get(0);
             var WeatherCondition = forecast.code;
             if (status == XmlListModel.Ready)
             {
                 weath.text = forecast.condition
                 temp.text = forecast.currenttemp + '°'
                 tempmax.text = 'H:' + ' ' + forecast.temperaturemax + '°';
                 tempmin.text = 'L:' + ' ' + forecast.temperaturemin + '°';
                 city.text = forecast.city

                 function snowy()
                 {
                    snow.visible = true;
                 }

                 function rainy()
                 {
                    rain.visible = true;
                 }

                 console.log("Condition is:", WeatherCondition);
                 //rainy();
                 //snowy();

                 if (parseInt(WeatherCondition) == 26)
                     sun.source ="images/Cloudy.png";
                 else if (parseInt(WeatherCondition) == 27)
                     sun.source ="images/mostlycloudyn.png";
                 else if (parseInt(WeatherCondition) == 28)
                     sun.source ="images/MostlyCloudy.png";
                 else if (parseInt(WeatherCondition) == 29)
                     sun.source ="images/Cloudyn.png";
                 else if (parseInt(WeatherCondition) == 30)
                     sun.source ="images/PartlyCloudy.png";
                 else if (parseInt(WeatherCondition) == 32)
                  sun.source ="images/sunny.png";
                 else if (parseInt(WeatherCondition) == 44)
                     sun.source ="images/PartlyCloudy.png";
                 else if (parseInt(WeatherCondition) == 11)
                 {
                     sun.source ="images/Rain.png";
                     rainy();
                 }
                 else if (parseInt(WeatherCondition) == 12)
                 {
                     sun.source ="images/Showers.png";
                     rainy();
                 }
                 else if (parseInt(WeatherCondition) == 46)
                 {
                     sun.source ="images/Snow.png";
                     snowy();
                 }
                 else if (parseInt(WeatherCondition) == 16)
                 {
                     sun.source ="images/Snow.png";
                     snowy();
                 }
                 else if (parseInt(WeatherCondition) == 34)
                     sun.source ="images/Sunny.png";
                 else if (parseInt(WeatherCondition) == 20)
                     sun.source = "images/fogn.png";
                 else if (parseInt(WeatherCondition) == 31)
                     sun.source = "images/sunny.png";
                 else if (parseInt(WeatherCondition) == 5)
                     sun.source = "images/snowrain.png";
                 else if (parseInt(WeatherCondition) == 14)
                 {
                     sun.source = "images/Snow.png";
                     snowy();
                 }
                 else if (parseInt(WeatherCondition) == 41)
                 {
                     sun.source = "images/Snow.png";
                     snowy();
                 }
                 else if (parseInt(WeatherCondition) == 7)
                 {
                     sun.source = "images/snowrain.png";
                     snowy();
                 }
                 else if (parseInt(WeatherCondition) == 33)
                     sun.source = "images/PartlyCloudy.png";
               }
             }
           }
         }
       }
     }
   }
 }
}
