import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
    id: root
    anchors.fill: parent
    property real factor: 0.05

    Rectangle {
        anchors.fill: parent
        color: "black"
    }
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

            }
            transform: Rotation { origin.x: width/2; origin.y: height/2; axis { x: 0; y: 1; z: 0 } angle:  rotationValue2}
            Rectangle {
                id:rect
                state: CurrentPlayer == 0 ? "" : CurrentPlayer == MaximumPlayer ? "ready" : "wip"
                property int playerCount: CurrentPlayer
                anchors.fill: parent
                height: parent.height
                color: "white"//ColorRol
                radius: 5
                border.width: 1
                Text {
                    id:gametitleLabel
                    text:GameTitle
                    font.pixelSize: parent.height * root.factor
                    textFormat: Text.RichText
                    horizontalAlignment: Text.AlignHCenter
                    width: parent.width * 0.5
                }
                Image {
                    id: image
                    source: PixmapRole ? "image://game/"+PixmapRole : "image://game/default"
                    cache: false
                    visible:PixmapRole.length>0
                    fillMode: Image.PreserveAspectFit
                    x: 5
                    y: parent.height * 0.1
                    width: parent.width * 0.5
                    height: parent.height* 0.8
                }
                Column  {
                    anchors.left: image.right
                    anchors.top: rect.top
                    anchors.right: rect.right
                    anchors.bottom: image.bottom
                    Text {
                        id:titleLabel
                        text:Title
                        font.pixelSize: parent.height * root.factor
                        textFormat: Text.RichText
                        width: parent.width * 0.5
                        height: parent.height * 0.1
                    }
                    Row {
                        height: parent.height * 0.1
                        width: parent.width
                        Rectangle {
                            color: ColorRole
                            width: 100
                            height: parent.height
                            Text {
                                id:playerCountTxt
                                anchors.fill: parent
                                text: CurrentPlayer +'/'+ MaximumPlayer
                                font.pixelSize: parent.height * 0.8
                                textFormat: Text.RichText
                            }
                        }
                        Text {
                            id:durationId
                            text: Duration+ qsTr("min")
                            font.pixelSize: parent.height
                            textFormat: Text.RichText
                        }
                        Text {
                            id:gmId
                            text: qsTr("GM:") + GMName
                            font.pixelSize: parent.height
                            textFormat: Text.RichText
                        }
                    }
                    TextArea {
                        id:desc
                        text: Description
                        font.pixelSize: parent.height * root.factor
                        wrapMode: Text.WordWrap
                        //elide:  Text.ElideRight
                        width: parent.width
                        height: parent.height * 0.6
                        textFormat: Text.RichText
                    }


                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        view.currentIndex = index;
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
         }
         focus: true
       Keys.onLeftPressed: decrementCurrentIndex()
       Keys.onRightPressed: incrementCurrentIndex()

    }

}
