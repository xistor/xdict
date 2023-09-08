import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.settings

ColumnLayout {
    width: parent.width
    height: parent.height
    Layout.fillWidth: true

    Settings{
       id:baidu_settings
       fileName: "settings.ini"
       property var url
       property var appID
       property var secretKey
    }

    Image {
        id: baidu_img
        scale: 0.5
        source: "qrc:/icon/Baidu_Translate.png"
        fillMode: Image.PreserveAspectFit

    }

    RowLayout {
        Layout.fillWidth: true
        Text {
            Layout.leftMargin : 20
            text: qsTr("Baidu URL")
        }

        Rectangle {
            id: url_rect
            height: 40
            Layout.fillWidth: true
            Layout.leftMargin : 20
            Layout.rightMargin : 20

            radius: 10

            border {
                color: "gainsboro"
                width: 2
            }
            TextInput {
                id: baidu_url
                width: parent.width
                leftPadding: 10
                rightPadding: 10
                topPadding: 10
                bottomPadding: 10
                focus: true
                selectByMouse: true
                clip: true
                text: "http://api.fanyi.baidu.com/api/trans/vip/translate?"
            }
        }

    }

    RowLayout {
        Layout.fillWidth: true
        Text {
            Layout.leftMargin : 20
            width:50
            text: qsTr("App ID")
        }

        Rectangle {
            id: appid_rect
            height: 40
            Layout.fillWidth: true
            Layout.leftMargin : 20
            Layout.rightMargin : 20

            radius: 10

            border {
                color: "gainsboro"
                width: 2
            }
            TextInput {
                id: baidu_appid
                width: parent.width
                leftPadding: 10
                rightPadding: 10
                topPadding: 10
                bottomPadding: 10
                focus: true
                selectByMouse: true
                clip: true
                text: baidu_settings.appID
            }
        }

    }

    RowLayout {
        Layout.fillWidth: true
        Text {
            Layout.leftMargin : 20
            width:50
            text: qsTr("Secret Key")
        }

        Rectangle {
            id: secretKey_rect
            height: 40
            Layout.fillWidth: true
            Layout.leftMargin : 20
            Layout.rightMargin : 20

            radius: 10

            border {
                color: "gainsboro"
                width: 2
            }
            TextInput {
                id: baidu_secretKey
                width: parent.width
                leftPadding: 10
                rightPadding: 10
                topPadding: 10
                bottomPadding: 10
                focus: true
                selectByMouse: true
                clip: true
                text: baidu_settings.secretKey

            }
        }

    }

    Item {
        id: it
        Layout.fillHeight: true
    }

    RowLayout {
        Layout.fillWidth: true

        Item {
            id: it2
            Layout.fillWidth: true
        }
        Button {
            text: "Back"
            Layout.bottomMargin: 20
            Layout.rightMargin: 20
            onClicked: {
                settingLoader.sourceComponent = settingMain
            }
        }

        Button {
            text: "OK"
            Layout.bottomMargin: 20
            Layout.rightMargin: 20

            onClicked: {
                baidu_settings.url = baidu_url.text
                baidu_settings.appID = baidu_appid.text
                baidu_settings.secretKey = baidu_secretKey.text
                close()
            }
        }

    }


}

