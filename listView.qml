import QtQuick 2.0

Item {
    id: root
    width: 400
    height: 400
    ListView {
        anchors.fill: parent
        id:listView
        model: _myModel
        delegate: scenarioDelegate
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
            height: 60
            width: parent.width
            Rectangle {
                id:rect
                state: CurrentPlayer == 0 ? "" : CurrentPlayer == MaximumPlayer ? "ready" : "wip"
                property int rotationValue: 0
//
                anchors.fill: parent
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
                    id:playerCount
                    text: CurrentPlayer +'/'+ MaximumPlayer
                    anchors.top: parent.top
                    anchors.right: parent.right
                }
                Text {
                    id:durationId
                    text: qsTr("Duration:") + Duration
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                }
                Text {
                    id:gmId
                    text: qsTr("GM:") + GMName
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                }

                Behavior on state  {
                    SequentialAnimation {
                      PropertyAnimation { target: rect; property: "rotationValue"; to: 800 }//Easing.OutQuart
                      PropertyAnimation { target: rect; property: "rotationValue"; to: 0 }
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
