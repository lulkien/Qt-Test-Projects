import QtQuick 2.15
import QtQuick.Window 2.15
import "common/screens"

Window {
    id: root
    width: KConstant.WINDOWS_WIDTH
    height: KConstant.WINDOWS_HEIGHT
    minimumHeight: height
    maximumHeight: height
    minimumWidth: width
    maximumWidth: width
    visible: true
    title: qsTr("Search Engine")

    Loader {
        anchors.fill: parent
        sourceComponent: KMainScreen {}
    }
}
