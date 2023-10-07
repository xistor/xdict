import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.platform
import Translator

Window {
    id: mainWin
    x: 100
    y: 100
    width: 800
    height: 300
    minimumWidth: 600
    minimumHeight: 200
    visible: true
    title: qsTr("xdict")
    flags: Qt.FramelessWindowHint

    property var floatingWIndow

    Component.onCompleted: {
        var component = Qt.createComponent("FloatingWin.qml")
        floatingWIndow    = component.createObject(mainWin)
        floatingWIndow.visible = false
    }

    // drag resize
    DragHandler {
        onActiveChanged: if(active) startSystemMove();
    }


    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton

        property int edges: 0;
        property int edgeOffest: 2;

        function setEdges(x, y) {
            edges = 0;
            if(x < edgeOffest) edges |= Qt.LeftEdge;
            if(x > (width - edgeOffest))  edges |= Qt.RightEdge;
            if(y < edgeOffest) edges |= Qt.TopEdge;
            if(y > (height - edgeOffest)) edges |= Qt.BottomEdge;
        }

        cursorShape: {
            return !containsMouse ? Qt.ArrowCursor:
                   edges == 3 || edges == 12 ? Qt.SizeFDiagCursor :
                   edges == 5 || edges == 10 ? Qt.SizeBDiagCursor :
                   edges & 9 ? Qt.SizeVerCursor :
                   edges & 6 ? Qt.SizeHorCursor : Qt.ArrowCursor;
        }

        onPositionChanged: setEdges(mouseX, mouseY);
        onPressed: {
            setEdges(mouseX, mouseY);
            if(edges && containsMouse) {
                startSystemResize(edges);
            }
        }
    }

    // system tray
    Menu {
        id: systemTrayMenu
        MenuItem {
            text: qsTr("隐藏")
            onTriggered: mainWin.hide()
        }
        MenuItem {
            text: qsTr("退出")
            onTriggered: Qt.quit()
        }
    }

    SystemTrayIcon {
        id:trayIcon
        visible: true
        icon.source: "qrc:/icon/x.png"
        tooltip: "xdict"
        onActivated: {
            mainWin.show()
            mainWin.raise()
            mainWin.requestActivate()
        }

        menu: systemTrayMenu
    }

    ColumnLayout {
        width: parent.width
        height: parent.height
        Layout.fillWidth: true

        // top toolbar
        ToolBar{
            width: parent.width
            Layout.fillWidth: true
            Layout.minimumHeight: 40

            // drag move
            MouseArea{
                property point clickPos: "0,0"
                anchors.fill: parent
                drag.minimumX: 0
                drag.maximumX: ScreenInfo.desktopAvailableWidth - mainWin.width
                drag.minimumY: 0
                drag.maximumY: ScreenInfo.desktopAvailableHeight - mainWin.height
                onPressed: {
                    mainWin.requestActivate()
                    clickPos = Qt.point(mouseX, mouseY)
                }

                onPositionChanged: {
                    var delta = Qt.point(mouseX - clickPos.x, mouseY - clickPos.y)
                    mainWin.x += delta.x
                    mainWin.y += delta.y
                }
            }

            RowLayout {
                anchors.centerIn: parent
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignCenter

                ComboBox {
                    id: sourceLang
                    model: ["auto", "english", "chinese"]
                }

                ToolButton {
                    id: translate_img
                    icon.source: "qrc:icon/translate.svg"

                    onPressed: {
                        var t =  targetLang.currentIndex
                        targetLang.currentIndex = sourceLang.currentIndex
                        sourceLang.currentIndex = t
                        src_edit.text = tar_edit.text
                        translator.translate(sourceLang.currentText, targetLang.currentText, src_edit.text);
                    }
                }

                ComboBox {
                    id: targetLang
                    model: ["english", "chinese"]
                    currentIndex: 1
                }

            }

            RowLayout {
                anchors.right: parent.right
                Layout.alignment: Qt.AlignHCenter
                ToolButton {
                    id: menu_img
                    icon.source: "qrc:/icon/menu_FILL0_wght400_GRAD0_opsz48.png"

                    onClicked: {
                        var component = Qt.createComponent("SettingWin.qml")
                        var settingWindow    = component.createObject(mainWin)
                        settingWindow.show()
                    }
                }

                ToolButton {
                    id: minimize_img
                    icon.source: "qrc:/icon/minimize_FILL0_wght400_GRAD0_opsz48.png"

                    onPressed: {
                        mainWin.hide();

                    }
                }
                ToolButton {
                    id: close_img
                    icon.source: "qrc:/icon/close_FILL0_wght400_GRAD0_opsz48.png"

                    onPressed: {
                        Qt.exit(0)
                    }
                }
            }
        }

        // Text input & output
        RowLayout {
            Layout.fillHeight: true
            width: mainWin.width
            Layout.fillWidth: true

            Rectangle {
                id: src_rect
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.leftMargin : 10
                Layout.topMargin: 2
                Layout.bottomMargin: 10

                radius: 12

                border {
                    color: "gainsboro"
                    width: 2
                }

                ColumnLayout {
                    anchors.top: parent.top;
                    anchors.left: parent.left;
                    anchors.right: parent.right;
                    anchors.bottom: parent.bottom;


                    Flickable {
                        id: src_flick
                        Layout.alignment: Qt.AlignTop
                        width: src_rect.width;
                        height: src_rect.height - src_toolbar_row.height - 10;
                        contentWidth: src_edit.contentWidth
                        contentHeight: src_edit.contentHeight
                        clip: true

                        function ensureVisible(r)
                        {
                            if (contentX >= r.x)
                                contentX = r.x;
                            else if (contentX+width <= r.x+r.width)
                                contentX = r.x+r.width-width;
                            if (contentY >= r.y)
                                contentY = r.y;
                            else if (contentY+height <= r.y+r.height)
                                contentY = r.y+r.height-height;
                        }

                        TextEdit {
                            id: src_edit
                            width: src_flick.width
                            height: src_flick.height
                            leftPadding: 10
                            rightPadding: 10
                            topPadding: 10
                            bottomPadding: 10
                            focus: true
                            wrapMode: TextEdit.Wrap
                            selectByMouse: true
                            onCursorRectangleChanged: src_flick.ensureVisible(cursorRectangle)
                        }
                    }

                    RowLayout{
                        id : src_toolbar_row
                        Layout.alignment: Qt.AlignBottom
                        Layout.fillWidth: true
                        Layout.leftMargin : 10
                        Layout.rightMargin : 10
                        Layout.bottomMargin: 10

                        Item {
                            id: it
                            Layout.fillWidth: true
                        }
                        RoundButton {
                            id: trans_button
                            Layout.alignment:  Qt.AlignRight | Qt.AlignBottom
                            text: "Translate"
                            radius: 10

                            onClicked: {
                               translator.translateText(src_edit.text, Translator.TEXT_INPUT_BOX);
                            }
                        }
                    }
                }
            }

            Rectangle {
                id: tar_rect
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.rightMargin : 10
                Layout.topMargin: 2
                Layout.bottomMargin: 10

                radius: 12

                border {
                    color: "gainsboro"
                    width: 2
                }

                Flickable {
                    id: tar_flick

                    width: tar_rect.width;
                    height: tar_rect.height;
                    contentWidth: tar_edit.contentWidth
                    contentHeight: tar_edit.contentHeight
                    clip: true

                    function ensureVisible(r)
                    {
                        if (contentX >= r.x)
                            contentX = r.x;
                        else if (contentX+width <= r.x+r.width)
                            contentX = r.x+r.width-width;
                        if (contentY >= r.y)
                            contentY = r.y;
                        else if (contentY+height <= r.y+r.height)
                            contentY = r.y+r.height-height;
                    }

                    TextEdit {
                        id: tar_edit
                        width: tar_flick.width
                        height: tar_flick.height
                        leftPadding: 10
                        rightPadding: 10
                        topPadding: 10
                        bottomPadding: 10
                        focus: true
                        wrapMode: TextEdit.Wrap
                        selectByMouse: true
                        onCursorRectangleChanged: tar_flick.ensureVisible(cursorRectangle)


                    }
                }
            }
        }
    }

    // get translate result
    Connections {
        target: translator
        function onTranslateResult(result, ts) {

            if(ts === Translator.TEXT_INPUT_BOX)
            {
                tar_edit.text = result
            }
            else if(ts === Translator.CURSOR_SELECTED)
            {

                floatingWIndow.visible = true

            }

        }
    }

}
