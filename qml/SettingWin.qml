import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: setting_win
    width: 400; height: 350
    title: qsTr("Setting")
    color: "gainsboro"


    // Loader加载不同组件，实现切换页面的功能
    Loader{
        id:settingLoader
        anchors.fill: parent // 弹出的界面都居中显示
    }

    // on start
    Component.onCompleted: {
        x= mainWin.x + mainWin.width / 2
        y= mainWin.y + mainWin.height / 2
        settingLoader.sourceComponent = settingMain
    }



    // main
    Component{
        id:settingMain
        SettingMain {
        }
    }

    Component{
        id:settingBaidu
        SettingBaidu {
        }
    }


}
