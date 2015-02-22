import QtQuick 2.0

Item {
    id: root
    width: 400
    height: 400



    ListView {
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


    }
    Component {
        id: scenarioDelegate
        Item {
            height: listView.currentIndex == index ? 120 : 60
            width: parent.width
            Rectangle {
                id:rect
                state: CurrentPlayer == 0 ? "" : CurrentPlayer == MaximumPlayer ? "ready" : "wip"
                property int rotationValue: 0
                property int playerCount: CurrentPlayer
//


                anchors.fill: parent
                height: parent.height
                color: ColorRole
                radius: 5
                border.width: 1
                transform: Rotation { origin.x: rect.width/2; origin.y: rect.height/2; axis { x: 1; y: 0; z: 0 } angle: rect.rotationValue}


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

                Behavior on playerCount  {
                    SequentialAnimation {
                      PropertyAnimation { target: rect; property: "rotationValue"; to: 800 }//Easing.OutQuart
                      PropertyAnimation { target: rect; property: "rotationValue"; to: 0 }
                    }
                }

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
}
