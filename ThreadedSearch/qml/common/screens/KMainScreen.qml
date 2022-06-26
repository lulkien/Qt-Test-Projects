import QtQuick 2.0
import "../components"

Rectangle {
    id: main_root
    width: KConstant.WINDOWS_WIDTH
    height: KConstant.WINDOWS_HEIGHT
    color: KConstant.BG_COLOR

    Item {
        id: controllerArea
        width: main_root.width/2
        height: main_root.height
        anchors {
            left: main_root.left
            top: main_root.top
        }

        KTextInput {
            id: thisTextInput
            width: controllerArea.width
            height: 40
            anchors {
                horizontalCenter: controllerArea.horizontalCenter
                top: controllerArea.top ; topMargin: 10
            }
            guideTextVisible: text === "";
            fontSize: 20
            onTextChanged: {
                SearchEngine.search(thisTextInput.text)
            }
        }

    }

    Rectangle {
        height: main_root.height
        width: 1
        anchors {
            horizontalCenter: main_root.horizontalCenter
        }
        color: "#FFFFFF"
    }

    Item {
        id: listArea
        width: main_root.width / 2
        height: main_root.height
        anchors {
            right: main_root.right
            top: main_root.top
        }
        clip: true

        Rectangle {
            id: list_bg
            color: KConstant.SLIM_WHITE
            width: listArea.width - 20
            height: listArea.height - 20
            anchors.centerIn: listArea
            radius: 5
        }

        KAbstractList {
            id: listView
            anchors.centerIn: listArea
            width: list_bg.width
            height: list_bg.height
            interactive: true
            currentIndex: 0
            itemPerPage: 6
            delegate: delegate
        }
    }



    Component {
        id: delegate
        Item {
            id: delegateItem
            width: listView.delegateWidth
            height: listView.delegateHeight
            readonly property bool isFocus: listView.currentIndex === index
            Rectangle {
                anchors.fill: parent
                color: delegateItem.isFocus ? KConstant.ITEM_FOCUSING : KConstant.INVISIBLE
                opacity: 0.5
            }
            Text {
                anchors.centerIn: parent
                color: "black"
                text: name
            }
            MouseArea {
                anchors.fill: parent
                onClicked: listView.currentIndex = index
            }
        }
    }
}
