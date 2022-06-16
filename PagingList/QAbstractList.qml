import QtQuick 2.0

ListView {
    id: root_abstractList
    property int delegateWidth: 100
    property int delegateHeight: 100


    property int itemPerPage: 6
    property int topViewIndex: 0
    property int botViewIndex: 0

    // function
    function focusUp() {
        console.log("[QAbstractList][focusUp]")
        var nextIndex = (currentIndex + count - 1) % count
        currentIndex = nextIndex
        if (nextIndex > botViewIndex || nextIndex < topViewIndex) {
            updateViewIndex(false, nextIndex)
        }
    }

    function focusDown() {
        console.log("[QAbstractList][focusDown]")
        var nextIndex = (currentIndex + 1) % count
        currentIndex = nextIndex
        if (nextIndex > botViewIndex || nextIndex < topViewIndex) {
            updateViewIndex(true, nextIndex)
        }
    }

    function updateViewIndex(isScrollDown, nextIndex) {
        console.log("[QAbstractList][updateViewIndex] old", topViewIndex, botViewIndex)
        if (isScrollDown) {
            topViewIndex = nextIndex
            botViewIndex = Math.min(topViewIndex + itemPerPage - 1,
                                    topViewIndex + (count - topViewIndex - 1))
            root_abstractList.contentY = topViewIndex * delegateHeight
        } else {
            botViewIndex = nextIndex
            topViewIndex = Math.max(0, botViewIndex - itemPerPage - 1)
            root_abstractList.contentY = topViewIndex * delegateHeight
        }
        console.log("[QAbstractList][updateViewIndex] new:", topViewIndex, botViewIndex)
    }

    Component.onCompleted: {
        updateViewIndex(true, 0)
    }
    onCountChanged: {
        updateViewIndex(true, topViewIndex)
    }
}
