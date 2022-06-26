import QtQuick 2.0

Item {
    width: KConstant.WIDNOWS_WIDTH
    height: KConstant.WIDNOWS_HEIGHT
    Rectangle {
        id: button
        width: 100
        height: 100
        anchors.centerIn: parent
        color: "green"
        MouseArea {
            anchors.fill: parent
            onClicked: SearchEngine.testFunction()
        }
    }
}
