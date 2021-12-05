import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle {
        id: killBtn
        width: 20
        height: width
        anchors.right: parent.right
        color: "red"
        MouseArea {
            anchors.fill: parent
            onClicked: Qt.quit()
        }
    }

    Rectangle {
        id: addLast
        width: 100
        height: 100
        border.color: "black"
        Text {
            anchors.centerIn: parent
            text: "ADD LAST"
        }
        MouseArea {
            anchors.fill: parent
            onClicked: addItem()
        }
    }

    Rectangle {
        id: add
        width: 100
        height: 100
        anchors.top: addLast.bottom
        anchors.topMargin: 10
        border.color: "black"
        Text {
            anchors.centerIn: parent
            text: "ADD RANDOM"
        }
        MouseArea {
            anchors.fill: parent
            onClicked: addItemAtRandomIndex()
        }
    }

    Rectangle {
        id: del
        width: 100
        height: 100
        anchors.top: add.bottom
        anchors.topMargin: 10
        border.color: "black"
        Text {
            anchors.centerIn: parent
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
            text: "DELETE RANDOM"
        }
        MouseArea {
            anchors.fill: parent
            onClicked: deleteRandomItem()
        }

    }

    Rectangle {
        id: listArea
        width: 200
        height: 400
        anchors.centerIn: parent
        clip: true
        color: "#AAAAAA"
        border.color: "black"
        ListView {
            id: lv
            property int itemH: 80
            model: MyModel
            width: parent.width
            height: parent.height
            interactive: contentHeight > height
            snapMode: ListView.SnapToItem
            delegate: Rectangle {
                width: lv.width
                height: lv.itemH
                color: Color
                Text {
                    id: label
                    anchors.centerIn: parent
                    text: Data
                    color: TextColor
                    font {
                        pixelSize: 15
                        bold: true
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: changeItemRandomlyAt(index)
                }
            }
        }
    }



    function addItem() {
        var hue = Math.floor(Math.random() * 361);                  // random Hue value from 0~360
        var saturation = Math.floor(Math.random() * 101) / 100;     // random Saturation value from 0~1.0
        var lightness = Math.floor(Math.random() * 101) / 100;      // random Lightness value from 0~1.0

        var data = strGenerator(16)
        var color = Qt.hsla(hue, saturation, lightness, 1)
        var textColor = lightness < 0.3 ? "white" : "black"

        console.warn("============= ADD ==============")
        MyModel.addLastItem(data, color, textColor)
        console.warn("================================")
        lv.positionViewAtEnd()
    }

    function addItemAtRandomIndex()
    {
        var idx = Math.floor(Math.random() * lv.count)              // random index
        var hue = Math.floor(Math.random() * 361);                  // random Hue value from 0~360
        var saturation = Math.floor(Math.random() * 101) / 100;     // random Saturation value from 0~1.0
        var lightness = Math.floor(Math.random() * 101) / 100;      // random Lightness value from 0~1.0

        var _data = strGenerator(16)
        var _color = Qt.hsla(hue, saturation, lightness, 1)
        var _textColor = lightness < 0.3 ? "white" : "black"

        console.warn("============ ADD AT ============")
        MyModel.addItemAt(idx, _data, _color, _textColor)
        console.warn("================================")
        lv.positionViewAtIndex(idx, ListView.Beginning)
    }

    function strGenerator(length) {
        var result           = '';
        var characters       = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
        var charactersLength = characters.length;
        for ( var i = 0; i < length; i++ ) {
          result += characters.charAt(Math.floor(Math.random() * charactersLength));
       }
       return result;
    }

    function deleteRandomItem() {
        var idx = Math.floor(Math.random() * lv.count)
        console.warn(idx)
        console.warn("============ DELETE ============")
        MyModel.deleteItem(idx)
        console.warn("================================")
        lv.positionViewAtIndex(idx, ListView.Beginning)
    }

    function changeItemRandomlyAt(idx) {
        var hue = Math.floor(Math.random() * 361);                  // random Hue value from 0~360
        var saturation = Math.floor(Math.random() * 101) / 100;     // random Saturation value from 0~1.0
        var lightness = Math.floor(Math.random() * 101) / 100;      // random Lightness value from 0~1.0

        var _data = strGenerator(16)
        var _color = Qt.hsla(hue, saturation, lightness, 1)
        var _textColor = lightness < 0.3 ? "white" : "black"

        console.warn("=========== RESET AT ===========")
        MyModel.changeItemAt(idx, _data, _color, _textColor)
        console.warn("================================")
        lv.positionViewAtIndex(idx, ListView.Beginning)
    }
}
