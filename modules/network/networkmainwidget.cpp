#include <QDebug>
#include <QVBoxLayout>

#include <libdui/dthememanager.h>
#include <libdui/libdui_global.h>
#include <libdui/dseparatorhorizontal.h>
#include <libdui/dswitchbutton.h>
#include <libdui/dtextbutton.h>
#include <libdui/dheaderline.h>
#include <libdui/dlistwidget.h>

#include "moduleheader.h"
#include "constants.h"
#include "normallabel.h"
#include "imagenamebutton.h"
#include "genericlistitem.h"
#include "generaladdbutton.h"

#include "wirednetworklistitem.h"
#include "wirelessnetworklistitem.h"
#include "vpnconnectswidget.h"
#include "networkmainwidget.h"
#include "networkglobal.h"
#include "addconnectpage.h"

namespace DCCNetwork {
    NetworkMainWidget *parentNetworkMainWidget(const QObject *obj)
    {
        QObject *tmp_obj = obj->parent();

        while(tmp_obj) {
            NetworkMainWidget *widget = qobject_cast<NetworkMainWidget*>(tmp_obj);
            if(widget)
                return widget;
            tmp_obj = tmp_obj->parent();
        }

        return NULL;
    }
}

NetworkMainWidget::NetworkMainWidget(QWidget *parent) :
    ScrollFrame(parent)
{
    m_dbusNetwork = new DBusNetwork(this);

    initUI();
    updateUI();

    connect(m_dbusNetwork, &DBusNetwork::DevicesChanged, this, &NetworkMainWidget::updateUI);
}

DBusNetwork *NetworkMainWidget::dbusNetwork() const
{
    return m_dbusNetwork;
}

void NetworkMainWidget::updateUI()
{
    QJsonDocument json_doc = QJsonDocument::fromJson(m_dbusNetwork->devices().toUtf8());
    QJsonObject json_obj = json_doc.object();

    QList<AbstractDeviceWidget*> tmp_list = m_mapPathToObject.values();

    m_wiredCount = m_wirelessCount = m_modemCount = 0;

    for(const QJsonValue &value : json_obj[DeviceType::Wired].toArray()) {
        const QVariantMap &map = value.toObject().toVariantMap();
        if(map["State"].toInt() == DeviceState::Unavailable
                && map["Vendor"].toString().toLower() == "apply")
            continue;

        ++m_wiredCount;

        const QString &path = map["Path"].toString();
        AbstractDeviceWidget *item = m_mapPathToObject.value(path, nullptr);

        if(item) {
            item->updateInfoByMap(map);
            tmp_list.removeOne(item);
        } else {
            item = new WiredNetworkListItem(m_dbusNetwork, this);
            item->updateInfoByMap(map);

            m_mapPathToObject[path] = item;

            mainLayout()->insertWidget(m_wiredCount - 1, item);
            qDebug() << "new wired:" << path << item << item->hwAddress() << item->uniqueUuid();
        }
    }

    for(const QJsonValue &value : json_obj[DeviceType::Modem].toArray()) {
        qDebug() << "add device:" << DeviceType::Modem << value.toVariant();
    }

    for(const QJsonValue &value : json_obj[DeviceType::Wireless].toArray()) {
        ++m_wirelessCount;

        const QVariantMap &map = value.toObject().toVariantMap();
        const QString &path = map["Path"].toString();

        AbstractDeviceWidget *item = m_mapPathToObject.value(path, nullptr);
        if(item) {
            item->updateInfoByMap(map);
            tmp_list.removeOne(item);
        } else {
            item = new WirelessNetworkListItem(m_dbusNetwork, this);
            item->updateInfoByMap(value.toObject().toVariantMap());
            m_mapPathToObject[path] = item;

            mainLayout()->insertWidget(m_wiredCount + m_modemCount + m_wirelessCount - 1, item);

            qDebug() << "new wireless:" << path << item << item->hwAddress() << item->uniqueUuid();
        }
    }

    for(AbstractDeviceWidget *widget : tmp_list) {
        m_mapPathToObject.remove(widget->path());
        widget->deleteLater();
    }
}

void NetworkMainWidget::initUI()
{
    ModuleHeader *header = new ModuleHeader(tr("Network"), false);
    QWidget *header_right_widget = new QWidget;
    QHBoxLayout *header_right_widget_layout = new QHBoxLayout(header_right_widget);
    GeneralAddButton *add_button = new GeneralAddButton;
    ImageNameButton *info_button = new ImageNameButton("info");

    header->setFixedSize(DCC::ModuleContentWidth, DUI::CONTENT_HEADER_HEIGHT);
    header_right_widget_layout->setMargin(0);
    header_right_widget_layout->setSpacing(5);
    header_right_widget_layout->addWidget(add_button);
    header_right_widget_layout->addWidget(info_button);
    header->setRightContent(header_right_widget);

    headerLayout()->addWidget(header);
    headerLayout()->addWidget(new DSeparatorHorizontal);

    m_vpnConnectsWidget = new VPNConnectsWidget(m_dbusNetwork, this);

    mainLayout()->addWidget(m_vpnConnectsWidget);

    connect(this, &NetworkMainWidget::currentMainWidgetChanged,
            this, [header_right_widget, this](const QWidget *w){
        header_right_widget->setVisible(w == mainLayout()->parentWidget());
    });
    connect(add_button, &GeneralAddButton::clicked, this, [this] {
        AddConnectPage *add_connect_page = new AddConnectPage;
        pushWidget(add_connect_page);
    });
}