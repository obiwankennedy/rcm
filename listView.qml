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
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        focus: true

    }
    Component {
        id: scenarioDelegate
        Item {
            height: 40
            width: parent.width
            Rectangle {
                anchors.fill: parent
                //color: "#d7b1b1"
                radius: 2
                border.width: 2



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
            }
        }
    }

    //    Rectangle {
    //        anchors.fill: parent
    //        color:"red"
    //    }

    // Text { text: "Scenario: " + Title + ", " + CurrentPlayer }

}
