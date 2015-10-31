// This file is automatically generated, please don't edit manually.
import QtQuick 2.1
import Deepin.Widgets 1.0
import "../edit"

BaseEditSection { 
    id: sectionIpv6
    virtualSection: "vs-ipv6"
    
    header.sourceComponent: EditDownArrowHeader{
        text: dsTr("IPv6")
    }

    content.sourceComponent: Column { 
        EditLineComboBox {
            id: lineIpv6Method
            connectionSession: sectionIpv6.connectionSession
            availableSections: sectionIpv6.availableSections
            availableKeys: sectionIpv6.availableKeys
            errors: sectionIpv6.errors
            section: "ipv6"
            key: "method"
            text: dsTr("Method")
        }
        EditLineTextInput {
            id: lineIpv6VkAddressesAddress
            connectionSession: sectionIpv6.connectionSession
            availableSections: sectionIpv6.availableSections
            availableKeys: sectionIpv6.availableKeys
            errors: sectionIpv6.errors
            section: "ipv6"
            key: "vk-addresses-address"
            text: dsTr("IP Address")
        }
        EditLineSpinner {
            id: lineIpv6VkAddressesPrefix
            connectionSession: sectionIpv6.connectionSession
            availableSections: sectionIpv6.availableSections
            availableKeys: sectionIpv6.availableKeys
            errors: sectionIpv6.errors
            section: "ipv6"
            key: "vk-addresses-prefix"
            text: dsTr("Prefix")
            max: 128
            min: 0
        }
        EditLineTextInput {
            id: lineIpv6VkAddressesGateway
            connectionSession: sectionIpv6.connectionSession
            availableSections: sectionIpv6.availableSections
            availableKeys: sectionIpv6.availableKeys
            errors: sectionIpv6.errors
            section: "ipv6"
            key: "vk-addresses-gateway"
            text: dsTr("Gateway")
        }
        EditLineTextInput {
            id: lineIpv6VkDns
            connectionSession: sectionIpv6.connectionSession
            availableSections: sectionIpv6.availableSections
            availableKeys: sectionIpv6.availableKeys
            errors: sectionIpv6.errors
            section: "ipv6"
            key: "vk-dns"
            text: dsTr("DNS Server")
        }
    }
}