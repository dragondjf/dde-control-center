import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import Deepin.Widgets 1.0
import "vpn"
import "dsl"

Column {
    id:body

    property int realHeight: childrenRect.height

    WiredDeviceExpand {
        id: wiredArea
    }

    WirelessDevicesArea{
        id: wirelessArea
    }

    VpnExpand {}

    DslExpand {}
}