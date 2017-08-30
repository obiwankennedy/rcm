import QtQuick 2.7
import QtQuick.Controls 2.2

Item {
    id: root
    anchors.fill: parent
    property real factor: 0.04
    property alias msg: popupTop.msg

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
                radius: 20
                border.width: 1
                Text {
                    id:gametitleLabel
                    text:GameTitle
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: parent.height * root.factor * 1.5
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
                    y: gametitleLabel.contentHeight
                    width: parent.width * 0.5 - 10
                    height: parent.height* 0.8
                }
                Item  {
                    id: rootItem
                    anchors.left: image.right
                    anchors.leftMargin: -(image.width - image.paintedWidth)/2
                    anchors.top: gametitleLabel.bottom
                    anchors.right: rect.right
                    anchors.bottom: rect.bottom
                    //spacing: parent.height * root.factor
                    Text {
                        id:titleLabel
                        text:Title + "title"
                        font.pixelSize: parent.height * root.factor
                        textFormat: Text.RichText
                        anchors.top: parent.top
                        anchors.left: parent.left
                        height: contentHeight
                    }
                   Text {
                        id:gmId
                        anchors.top: titleLabel.bottom
                        anchors.left: parent.left
                        text: qsTr("Votre meneur:") + GMName
                        font.pixelSize: parent.height * root.factor
                        textFormat: Text.RichText
                        height: contentHeight
                        width: contentWidth
                    }
                    Rectangle {
                        id: playerCount
                        color: ColorRole
                        anchors.top: titleLabel.bottom
                        anchors.right: parent.right
                        width: playerCountTxt.contentWidth
                        height: playerCountTxt.height
                        Text {
                            id:playerCountTxt
                            anchors.top: parent.top
                            anchors.left: parent.left
                            anchors.right: parent.right
                            text: CurrentPlayer +'/'+ MaximumPlayer
                            font.pixelSize: rootItem.height * root.factor
                            textFormat: Text.RichText
                            height: contentHeight
                            verticalAlignment: Text.AlignTop

                        }
                    }



                    TextArea {
                        id:desc
                        text: Description
                        anchors.top: gmId.bottom
                        anchors.left: parent.left
                        font.pixelSize: parent.height * root.factor
                        wrapMode: Text.WordWrap
                        width: parent.width
                        height: parent.height * 0.8
                        textFormat: Text.RichText
                        leftPadding: 0
                    }



                }
                Text {
                    id:durationId
                    text: Duration+ qsTr("min")
                    font.pixelSize: parent.height*0.05
                    textFormat: Text.RichText
                    anchors.bottom: rect.bottom
                    anchors.horizontalCenter: parent.horizontalCenter

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
             PathAttribute { name: "itemOpacity"; value: 0.01 }
             PathAttribute { name: "itemRotation"; value: -54 }
             PathLine { x: 0; y: 3*view.height/8; }
             PathAttribute { name: "iconScale"; value: 0.3 }
             PathAttribute { name: "itemOpacity"; value: 0.01 }
             PathAttribute { name: "itemRotation"; value: 54 }
             PathLine { x: view.width*0.5; y: view.height*0.5; }
         }
         focus: true
       Keys.onLeftPressed: decrementCurrentIndex()
       Keys.onRightPressed: incrementCurrentIndex()

    }


    Rectangle {
        id: popupTop
        color: "white"
        border.width: 2
        border.color: "black"
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height * 0.07
        radius: 20
        property alias msg: popupMenu.text
        Text {
            id: popupMenu
            anchors.fill: parent
        }
    }

}
