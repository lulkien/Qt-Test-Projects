import QtQuick 2.0

Item {
    id: root_wasd
    property int buttonSize: 75
    readonly property int gapSize: buttonSize / 5
    readonly property int round: buttonSize / 10

    property string keyColor: "white"
    property string textColor: "black"

    width: buttonSize * 3 + gapSize * 4
    height: buttonSize * 2 + gapSize * 3

    signal wKeyClicked()
    signal aKeyClicked()
    signal sKeyClicked()
    signal dKeyClicked()

    QButton {
        id: w_key
        width: buttonSize
        height: buttonSize
        radius: round

        anchors {
            top: root_wasd.top
            topMargin: gapSize
            horizontalCenter: root_wasd.horizontalCenter
        }

        color: keyColor
        border.color: textColor

        label: "W"
        labelColor: textColor
        onButtonClicked: wKeyClicked()
    }

    QButton {
        id: a_key
        width: buttonSize
        height: buttonSize
        radius: round

        anchors {
            top: s_key.top
            right: s_key.left
            rightMargin: gapSize
        }

        color: keyColor
        border.color: textColor

        label: "A"
        labelColor: textColor
        onButtonClicked: aKeyClicked()
    }

    QButton {
        id: s_key
        width: buttonSize
        height: buttonSize
        radius: round

        anchors {
            top: w_key.bottom
            topMargin: gapSize
            horizontalCenter: root_wasd.horizontalCenter
        }

        color: keyColor
        border.color: textColor

        label: "S"
        labelColor: textColor
        onButtonClicked: sKeyClicked()
    }


    QButton {
        id: d_key
        width: buttonSize
        height: buttonSize
        radius: round

        anchors {
            top: s_key.top
            left: s_key.right
            leftMargin: gapSize
        }

        color: keyColor
        border.color: textColor

        label: "D"
        labelColor: textColor
        onButtonClicked: dKeyClicked()
    }
}
