import QtQuick 2.0

Rectangle {
    property bool isHorizontal: true
    property int lineSize: 100
    width: isHorizontal ? lineSize : 1
    height: isHorizontal ? 1 : lineSize
    color: "black"
}
