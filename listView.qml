import QtQuick 2.0

Item {
    id: root
    width: 400
    height: 400

    Rectangle {
        anchors.fill: parent
        color: "black"
    }

  /*  ListView {
        anchors.fill: parent
        id:listView
        objectName:"listView"
        highlightFollowsCurrentItem :  true
        model: _myModel
        delegate: scenarioDelegate
        currentIndex: -1
        highlight: Rectangle {
            height: 60
            width: parent.width
            color: "lightsteelblue";
            radius: 5 }
        focus: true


    }*/


    Component {
        id: scenarioDelegate
        Item {
            height: parent.height*0.8//listView.currentIndex == index ? 120 : 60
            width: parent.width*0.8
            opacity: PathView.itemOpacity
            property double rotationValue2: PathView.itemRotation
            scale: PathView.iconScale
            z: PathView.isCurrentItem ? 5 : 0

            onRotationValue2Changed: {
                console.log("Rotation value2="+rotationValue2)
            }

            transform: Rotation { origin.x: width/2; origin.y: height/2; axis { x: 0; y: 1; z: 0 } angle:  rotationValue2}
            Rectangle {
                id:rect
                state: CurrentPlayer == 0 ? "" : CurrentPlayer == MaximumPlayer ? "ready" : "wip"
               // property int rotationValue: 0
                property int playerCount: CurrentPlayer
//


                anchors.fill: parent
                height: parent.height
                color: "red"//ColorRole
                radius: 5
                border.width: 1
               // transform: Rotation { origin.x: rect.width/2; origin.y: rect.height/2; axis { x: 1; y: 0; z: 0 } angle: rect.rotationValue}


                Text {
                    id:titleLabel
                    text:Title
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text {
                    id:gametitleLabel
                    text:GameTitle
                    anchors.top: titleLabel.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text {
                    id:levelid
                    text: "("+Level+")"
                    anchors.top: gametitleLabel.top
                    anchors.left: gametitleLabel.right
                    width: 100
                    height:20
                }
                Text {
                    id:playerCountTxt
                    text: CurrentPlayer +'/'+ MaximumPlayer
                    anchors.top: parent.top
                    anchors.right: parent.right
                }
                Text {
                    id:durationId
                    text: qsTr("Duration: ") + Duration
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                }
                Text {
                    id:gmId
                    text: qsTr("GM:") + GMName
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                }
                Image {
                    id: image
                    source: PixmapRole ? "image://game/"+PixmapRole : "image://game/default"
                    cache: false

                    visible:PixmapRole.length>0

                    fillMode: Image.PreserveAspectFit
                    anchors.top: parent.top
                    anchors.left: gmId.right
                    anchors.leftMargin: 5
                    anchors.bottom: parent.bottom
                }

               /* Behavior on playerCount  {
                    SequentialAnimation {
                      PropertyAnimation { target: rect; property: "rotationValue"; to: 800 }//Easing.OutQuart
                      PropertyAnimation { target: rect; property: "rotationValue"; to: 0 }
                    }
                }*/

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        listView.currentIndex = index;
                    }
                }
                states: [
                    State {
                        name: ""
                    },
                    State {
                        name: "wip"
                    },
                    State {
                        name: "ready"
                    }

                ]

            }
        }
    }

    PathView {
        id: view
            anchors.fill: parent
         //model: 32
         model: _myModel
         delegate: scenarioDelegate
         path: Path {
             startX: view.width/2
             startY: view.height/2
             PathAttribute { name: "iconScale"; value: 1.0 }
             PathAttribute { name: "itemOpacity"; value: 1 }
             PathAttribute { name: "itemRotation"; value: 0.0 }
            // PathAttribute { name: "itemZValue"; value: 5.0 }
             PathLine { x:view.width; y: 3*view.height/8 }
             //PathQuad { x: view.width/2; y: view.height/8; controlX: 3*view.width/2; controlY: 3*view.height/8 }
             PathAttribute { name: "iconScale"; value: 0.3 }
             PathAttribute { name: "itemOpacity"; value: 0.5 }
             PathAttribute { name: "itemRotation"; value: -54 }
             PathLine { x: 0; y: 3*view.height/8; }
             PathAttribute { name: "iconScale"; value: 0.3 }
             PathAttribute { name: "itemOpacity"; value: 0.5 }
             PathAttribute { name: "itemRotation"; value: 54 }
             PathLine { x: view.width*0.5; y: view.height*0.5; }

             //PathAttribute { name: "itemZValue"; value: 5.0 }
             //PathQuad { x: view.width/2; y: view.height/2; controlX: -view.width/12; controlY: 3*view.height/8 }
            /* PathAttribute { name: "itemOpacity"; value: 0.5 }
             PathAttribute { name: "itemRotation"; value: 54.0 }
             PathAttribute { name: "itemZValue"; value: 0.0 }
             PathLine { x: view.width*0.2; y: view.height/2 }
             PathAttribute { name: "itemOpacity"; value: 1 }
             PathAttribute { name: "itemRotation"; value: 0.0 }
             PathAttribute { name: "itemZValue"; value: 5.0 }
             PathLine { x: view.width/2; y: view.height/2 }
             PathAttribute { name: "itemOpacity"; value: 1 }
             PathAttribute { name: "itemRotation"; value: 0.0 }
             PathAttribute { name: "itemZValue"; value: 5.0 }
             PathLine { x: view.width*0.8; y: view.height/2 }
             PathAttribute { name: "itemOpacity"; value: 0.5 }
             PathAttribute { name: "itemRotation"; value: -54.0 }
             PathAttribute { name: "itemZValue"; value: 0.0 }
             PathLine { x: view.width*2; y: view.height/2 }*/

         }
         focus: true
       Keys.onLeftPressed: decrementCurrentIndex()
       Keys.onRightPressed: incrementCurrentIndex()

    }

}
/*path: Path {
    id: p
    property real width: 200
    property real height: 200
    property real margin: 50
    property real cx: width / 2
    property real cy: height / 2
    property real rx: width / 2 - margin
    property real ry: height / 2 - margin
    property real mx: rx * magic
    property real my: ry * magic
    property real magic: 0.551784
    startX: p.cx; startY: p.cy + p.ry
    PathCubic { // second quadrant arc
    control1X: p.cx - p.mx; control1Y: p.cy + p.ry
    control2X: p.cx - p.rx; control2Y: p.cy + p.my
    x: p.cx - p.rx; y: p.cy
    }
    PathCubic { // third quadrant arc
    control1X: p.cx - p.rx; control1Y: p.cy - p.my
    control2X: p.cx - p.mx; control2Y: p.cy - p.ry
    x: p.cx; y: p.cy - p.ry
    }
    PathCubic { // forth quadrant arc
    control1X: p.cx + p.mx; control1Y: p.cy - p.ry
    control2X: p.cx + p.rx; control2Y: p.cy - p.my
    x: p.cx + p.rx; y: p.cy
    }
    PathCubic { // first quadrant arc
    control1X: p.cx + p.rx; control1Y: p.cy + p.my
    control2X: p.cx + p.mx; control2Y: p.cy + p.ry
    x: p.cx; y: p.cy + p.ry
    }
   }*/
