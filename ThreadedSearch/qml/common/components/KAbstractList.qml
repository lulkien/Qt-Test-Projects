import QtQuick 2.0

ListView {
    id: abstractList_root
    property int delegateWidth: abstractList_root.width
    readonly property int delegateHeight: abstractList_root.height / itemPerPage
    property int itemPerPage:   5
    property int topViewIndex:  99
    property int bottomViewIndex:  99
    readonly property bool outOfView: currentIndex > bottomViewIndex
                                      || currentIndex < topViewIndex

    currentIndex: 0
    snapMode: ListView.SnapToItem
    highlightMoveDuration: 0
    // slots
    onMovementEnded: {
        updateBoundIndex()
    }

    onCountChanged: {
        updateBoundIndex()
    }

    Component.onCompleted: {
        updateBoundIndex()
        currentIndex = 0
    }
    // function
    function focusUp() {
        console.warn("[QAbstractList][focusUp]")
        currentIndex = (currentIndex + count - 1) % count
        if (outOfView) {
            updatePageView(false, currentIndex)
        }
    }

    function focusDown() {
        console.warn("[QAbstractList][focusDown]")
        currentIndex = (currentIndex + 1) % count
        if (outOfView) {
            updatePageView(true, currentIndex)
        }
    }

    function updatePageView(isScrollDown, nextIndex) {
        // update view index
        topViewIndex = isScrollDown ? Math.min(currentIndex, count - itemPerPage)
                                    : Math.max(0, currentIndex - itemPerPage + 1)
        bottomViewIndex = Math.min(count - 1, topViewIndex + itemPerPage - 1)
        // set position
        positionViewAtIndex(currentIndex, isScrollDown ? ListView.Beginning : ListView.End)
        console.warn("[QAbstractList][updatePageView] New View Index:", topViewIndex, bottomViewIndex)
    }

    function updateBoundIndex() {
        var newTopIndex = indexAt(delegateWidth / 2, contentY + delegateHeight / 2)
        if (newTopIndex !== -1) {
            topViewIndex = newTopIndex
            bottomViewIndex = Math.min(count - 1, topViewIndex + itemPerPage - 1)
        } else {
            topViewIndex = 0
            bottomViewIndex = 0
        }

        if (outOfView) {
            currentIndex = newTopIndex === -1 ? 0 : newTopIndex
        } else {
            console.warn("[QAbstractList][updateBoundIndex] Not update currentIndex")
        }
        console.warn("[QAbstractList][updateBoundIndex]", topViewIndex, bottomViewIndex)
    }
}
