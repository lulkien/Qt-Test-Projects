import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: root
    width: 1280
    height: 780
    visible: true
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width

    title: qsTr("Hello World")

    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: 0.4
    }

    ListModel {
        id: listModel
    }

    QLine {
        isHorizontal: false
        lineSize: parent.height
        anchors.centerIn: parent
        color: "black"
    }

    Item {
        id: mainLeft
        width: parent.width / 2
        height: parent.height
        anchors {
            left: parent.left
            top: parent.top
        }

        QButton {
            id: addButton
            width: 200
            height: 100
            anchors {
                top: mainLeft.top ; topMargin: 100
                horizontalCenter: mainLeft.horizontalCenter
                horizontalCenterOffset: -175
            }
            color: "#32A853"
            label: "ADD"
            onButtonClicked: {
                var tmpName = listModel.count
                listModel.append( { name: tmpName} )
            }
        }

        QButton {
            id: delButton
            width: 200
            height: 100
            anchors {
                top: mainLeft.top ; topMargin: 100
                horizontalCenter: mainLeft.horizontalCenter
                horizontalCenterOffset: 175
            }
            color: "#A83232"
            label: "DEL"
            onButtonClicked: {
                if (listModel.count > 0) {
                    listModel.remove(listModel.count - 1)
                } else {
                    console.log("[main.qml][delButton] Empty listModel!!!")
                }
            }
        }

        WASD_Keypad {
            anchors.horizontalCenter: mainLeft.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 100
            onWKeyClicked: {
                console.log("W")
                listView.focusUp()
            }
            onSKeyClicked: {
                console.log("S")
                listView.focusDown()
            }
        }
    }

    Item {
        id: mainRight
        width: root.width / 2
        height: root.height
        anchors {
            right: parent.right
            top: parent.top
        }

        QAbstractList {
            id: listView
            model: listModel
            anchors.centerIn: mainRight
            clip: true
            width: mainRight.width - 50
            height: mainRight.height - 50
            delegateWidth: mainRight.width - 50
            delegateHeight: (mainRight.height - 50) / listView.itemPerPage
            interactive: true
            currentIndex: 0
            itemPerPage: 5
            QBorder { }
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
            QLine {
                isHorizontal: true
                lineSize: delegateItem.width - 20
                anchors.bottom: delegateItem.bottom
                anchors.horizontalCenter: delegateItem.horizontalCenter
                visible: index !== listView.count - 1
            }
            Rectangle {
                anchors.fill: parent
                color: delegateItem.isFocus ? "#32A899" : "transparent"
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

    Component.onCompleted: {
        for (var i = 0; i < 13; i++) {
            listModel.append({ name: i })
        }
    }

}
