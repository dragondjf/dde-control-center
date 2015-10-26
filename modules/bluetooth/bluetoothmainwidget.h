#ifndef BLUETOOTHMAINWIDGET_H
#define BLUETOOTHMAINWIDGET_H

#include <QFrame>
#include <QVBoxLayout>

#include <libdui/dlistwidget.h>

#include "dbus/dbusbluetooth.h"

DUI_USE_NAMESPACE

class AdapterWidget;
class BluetoothListItem;
class BluetoothMainWidget : public QFrame
{
    Q_OBJECT
public:
    struct DeviceInfo;
    ///本机的蓝牙适配器的信息
    struct AdapterInfo{
        bool powered;
        bool discovering;
        bool discoverable;
        uint discoverableTimeout;
        QString path;
        QString name;
        QList<DeviceInfo*> deviceInfoList;
        AdapterWidget *listWidget = nullptr;///显示蓝牙适配器搜到的设备列表的list
        DBusBluetooth *bluetoothDbus = nullptr;
    };
    ///搜到的蓝牙设备信息
    struct DeviceInfo{
        bool trusted;
        bool paired;
        int state;
        QString path;
        QString name;
        QString icon;
        QString computer;
        struct AdapterInfo *adapterInfo = nullptr;
        BluetoothListItem *listItem = nullptr;
    };

    explicit BluetoothMainWidget(QWidget *parent = 0);

private slots:
    void addAdapter(AdapterInfo *info);
    void removeAdapter(const AdapterInfo *info);

protected:
    void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;

private:
    QVBoxLayout *m_mainLayout;
    DListWidget *m_adapterList;
    DBusBluetooth *m_bluetoothDbus;
    QList<AdapterInfo*> m_adapterInfoList;
    QMap<QString, AdapterInfo*> m_pathToAdapterInfoMap;
    QMap<QString, DeviceInfo*> m_pathToDeviceInfoMap;

    AdapterInfo* newAdapterInfoByMap(const QVariantMap &map);
    DeviceInfo* newDeviceInfoByMap(const QVariantMap &map) const;
    BluetoothListItem *newDeviceListItem(DeviceInfo* device_info) const;

    void intiBackend();
    void initUI();
};

#endif // BLUETOOTHMAINWIDGET_H