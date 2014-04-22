import QtQuick 2.0
import QtQuick.Window 2.1
import Deepin.DockApplet 1.0
import Deepin.Widgets 1.0
import DBus.Com.Deepin.Daemon.Network 1.0

DockApplet{
    title: "DSS"
    appid: "AppletNetwork"
    icon: iconPath
    property url iconPath: "images/icon.png"
    property var dconstants: DConstants {}

    function showNetwork(){
        dbusControlCenter.ShowModule("network")
    }

    function hideNetwork(){
        set_hide_applet("network")
    }

    onActivate: {
        showNetwork()
    }

    property var dbusNetwork: NetworkManager{}
    property var activeConnections: dbusNetwork.activeConnections

    function getWirelessDeviceList(){
        var r = new Array()
        var devices = dbusNetwork.wirelessDevices
        for(var i in devices){
            r.push(devices[i][0])
        }
        return r
    }
    property var wirelessDeviceList: getWirelessDeviceList()

    function getWiredDeviceList(){
        var r = new Array()
        var devices = dbusNetwork.wiredDevices
        for(var i in devices){
            r.push(devices[i][0])
        }
        return r
    }
    property var wiredDeviceList: getWiredDeviceList()

    window: DockQuickWindow {
        id: root
        width: 280
        height: content.height
        color: Qt.rgba(0, 0, 0, 0.85)

        Column {
            id: content
            width: parent.width

            Loader {
                id: wiredNetworkArea
                width: parent.width
                height: childrenRect.height
                source: "WiredConnection.qml"
                visible: dbusNetwork.wiredConnections.length > 0
            }

            DSeparatorHorizontal {
                visible: wiredNetworkArea.visible && wirelessDeviceList.length > 0
                width: parent.width * 0.9
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Repeater{
                id: wirelessNetworkRepeater
                model: wirelessDeviceList
                delegate: Loader {
                    id: wirelessNetworkArea
                    width: parent.width
                    height: childrenRect.height
                    source: "WirelessConnection.qml"
                }
            }
        }
    }
}