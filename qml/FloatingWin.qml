import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.settings
import Qt.labs.platform
import Translator


Window{
    id:floatingWin
    flags: Qt.FramelessWindowHint
    width: 300
    height: 100

    onActiveChanged: {
        // hide window when lose focus
        if (!active) {
            floatingWin.visible = false;
        }
    }

    Component.onCompleted: {

    }

    Text {
        id: translated_texts
        width: floatingWin.width
        height: floatingWin.height
        text: qsTr("Hello ")
        wrapMode: TextEdit.Wrap
    }




    // get translate result
    Connections {
        target: translator
        function onTranslateResult(result, ts) {
            console.log("onTranslateResult")
            console.log(ts)

            if(ts === Translator.CURSOR_SELECTED)
            {
                translated_texts.text = result

                floatingWin.visible = true
                // set window position

                floatingWin.x = picker.getTextPostion().x / 2
                floatingWin.y = picker.getTextPostion().y / 2

                //bring window to front
                floatingWin.requestActivate();

            }

        }
    }
}


