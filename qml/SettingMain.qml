import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


ColumnLayout {
    id: column
    width: parent.width
    height: parent.height
    Layout.fillWidth: true

    RowLayout {
        Image {
            id: baidu_img
            scale: 0.5
            source: "qrc:/icon/Baidu_Translate.png"
            fillMode: Image.PreserveAspectFit

        }
        Text {
            text: qsTr("百度翻译")
        }


        Item {
            id: it
            Layout.fillWidth: true
        }

        Switch {
            id: baidu_sw
        }

        ToolButton {
            Layout.rightMargin : 10
            icon.source: "qrc:/icon/settings_FILL0_wght400_GRAD0_opsz48.png"
            onClicked: settingLoader.sourceComponent = settingBaidu
        }
    }

    TextInput {
        id: baidu_appid

    }

}

