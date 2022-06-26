import QtQuick 2.0

Item {
    id: textInput_root
    width: 100
    height: 30
    property alias text: inputBox.text
    property alias fontSize: inputBox.font.pixelSize
    property alias guideTextVisible: guideText.visible

    Rectangle {
        id: box
        width: textInput_root.width - 40
        height: textInput_root.height
        border.color: KConstant.BG_COLOR
        anchors.centerIn: textInput_root
        color: KConstant.SLIM_WHITE
        radius: height / 4
        clip: true

        TextInput {
            id: inputBox
            width: box.width - 20
            height: box.height
            anchors.centerIn: box
            verticalAlignment: TextInput.AlignVCenter
        }

        Text {
            id: guideText
            font.pixelSize: textInput_root.fontSize
            anchors {
                verticalCenter: box.verticalCenter
                left: box.left  ;   leftMargin: 12
            }
            text: "STR_INPUT_EMPTY"
            opacity: 0.5
            visible: true
        }
    }
}
