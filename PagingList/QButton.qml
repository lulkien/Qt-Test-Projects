import QtQuick 2.0

Rectangle {
    width: 100
    height: 100
    property string label: ""
    property string labelColor: "black"
    signal buttonClicked()
    MouseArea {
        anchors.fill: parent
        onClicked: buttonClicked()
    }
    Text {
        anchors.centerIn: parent
        text: label
        color: labelColor
    }
}
