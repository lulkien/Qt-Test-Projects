import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Rectangle {
        id: button
        width: 100
        height: 100
        anchors.centerIn: parent
        color: "green"
        MouseArea {
            anchors.fill: parent
            onClicked: SearchEngine.startCrawler()
        }
    }
}
