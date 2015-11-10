/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -c Power -p dbuspower com.deepin.daemon.Power.xml
 *
 * qdbusxml2cpp is Copyright (C) 2015 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef DBUSPOWER_H_1436931115
#define DBUSPOWER_H_1436931115

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface com.deepin.daemon.Power
 */
class DBusPower: public QDBusAbstractInterface
{
    Q_OBJECT

    Q_SLOT void __propertyChanged__(const QDBusMessage& msg)
    {
        QList<QVariant> arguments = msg.arguments();
        if (3 != arguments.count())
            return;
        QString interfaceName = msg.arguments().at(0).toString();
        if (interfaceName !="com.deepin.daemon.Power")
            return;
        QVariantMap changedProps = qdbus_cast<QVariantMap>(arguments.at(1).value<QDBusArgument>());
        QStringList keys = changedProps.keys();
        foreach(const QString &prop, keys) {
        const QMetaObject* self = metaObject();
            for (int i=self->propertyOffset(); i < self->propertyCount(); ++i) {
                QMetaProperty p = self->property(i);
                if (p.name() == prop) {
 	            Q_EMIT p.notifySignal().invoke(this);
                }
            }
        }
   }
public:
    static inline const char *staticInterfaceName()
    { return "com.deepin.daemon.Power"; }

public:
    DBusPower(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~DBusPower();

    Q_PROPERTY(int BatteryIdleDelay READ batteryIdleDelay WRITE setBatteryIdleDelay NOTIFY BatteryIdleDelayChanged)
    inline int batteryIdleDelay() const
    { return qvariant_cast< int >(property("BatteryIdleDelay")); }
    inline void setBatteryIdleDelay(int value)
    { setProperty("BatteryIdleDelay", QVariant::fromValue(value)); }

    Q_PROPERTY(bool BatteryIsPresent READ batteryIsPresent NOTIFY BatteryIsPresentChanged)
    inline bool batteryIsPresent() const
    { return qvariant_cast< bool >(property("BatteryIsPresent")); }

    Q_PROPERTY(double BatteryPercentage READ batteryPercentage NOTIFY BatteryPercentageChanged)
    inline double batteryPercentage() const
    { return qvariant_cast< double >(property("BatteryPercentage")); }

    Q_PROPERTY(int BatteryPlan READ batteryPlan WRITE setBatteryPlan NOTIFY BatteryPlanChanged)
    inline int batteryPlan() const
    { return qvariant_cast< int >(property("BatteryPlan")); }
    inline void setBatteryPlan(int value)
    { setProperty("BatteryPlan", QVariant::fromValue(value)); }

    Q_PROPERTY(uint BatteryState READ batteryState NOTIFY BatteryStateChanged)
    inline uint batteryState() const
    { return qvariant_cast< uint >(property("BatteryState")); }

    Q_PROPERTY(int BatterySuspendDelay READ batterySuspendDelay WRITE setBatterySuspendDelay NOTIFY BatterySuspendDelayChanged)
    inline int batterySuspendDelay() const
    { return qvariant_cast< int >(property("BatterySuspendDelay")); }
    inline void setBatterySuspendDelay(int value)
    { setProperty("BatterySuspendDelay", QVariant::fromValue(value)); }

    Q_PROPERTY(int LidClosedAction READ lidClosedAction WRITE setLidClosedAction NOTIFY LidClosedActionChanged)
    inline int lidClosedAction() const
    { return qvariant_cast< int >(property("LidClosedAction")); }
    inline void setLidClosedAction(int value)
    { setProperty("LidClosedAction", QVariant::fromValue(value)); }

    Q_PROPERTY(bool LidIsPresent READ lidIsPresent NOTIFY LidIsPresentChanged)
    inline bool lidIsPresent() const
    { return qvariant_cast< bool >(property("LidIsPresent")); }

    Q_PROPERTY(int LinePowerIdleDelay READ linePowerIdleDelay WRITE setLinePowerIdleDelay NOTIFY LinePowerIdleDelayChanged)
    inline int linePowerIdleDelay() const
    { return qvariant_cast< int >(property("LinePowerIdleDelay")); }
    inline void setLinePowerIdleDelay(int value)
    { setProperty("LinePowerIdleDelay", QVariant::fromValue(value)); }

    Q_PROPERTY(int LinePowerPlan READ linePowerPlan WRITE setLinePowerPlan NOTIFY LinePowerPlanChanged)
    inline int linePowerPlan() const
    { return qvariant_cast< int >(property("LinePowerPlan")); }
    inline void setLinePowerPlan(int value)
    { setProperty("LinePowerPlan", QVariant::fromValue(value)); }

    Q_PROPERTY(int LinePowerSuspendDelay READ linePowerSuspendDelay WRITE setLinePowerSuspendDelay NOTIFY LinePowerSuspendDelayChanged)
    inline int linePowerSuspendDelay() const
    { return qvariant_cast< int >(property("LinePowerSuspendDelay")); }
    inline void setLinePowerSuspendDelay(int value)
    { setProperty("LinePowerSuspendDelay", QVariant::fromValue(value)); }

    Q_PROPERTY(bool LockWhenActive READ lockWhenActive WRITE setLockWhenActive NOTIFY LockWhenActiveChanged)
    inline bool lockWhenActive() const
    { return qvariant_cast< bool >(property("LockWhenActive")); }
    inline void setLockWhenActive(bool value)
    { setProperty("LockWhenActive", QVariant::fromValue(value)); }

    Q_PROPERTY(bool OnBattery READ onBattery NOTIFY OnBatteryChanged)
    inline bool onBattery() const
    { return qvariant_cast< bool >(property("OnBattery")); }

    Q_PROPERTY(QString PlanInfo READ planInfo NOTIFY PlanInfoChanged)
    inline QString planInfo() const
    { return qvariant_cast< QString >(property("PlanInfo")); }

    Q_PROPERTY(int PowerButtonAction READ powerButtonAction WRITE setPowerButtonAction NOTIFY PowerButtonActionChanged)
    inline int powerButtonAction() const
    { return qvariant_cast< int >(property("PowerButtonAction")); }
    inline void setPowerButtonAction(int value)
    { setProperty("PowerButtonAction", QVariant::fromValue(value)); }

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> Reset()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("Reset"), argumentList);
    }

Q_SIGNALS: // SIGNALS
// begin property changed signals
void BatteryIdleDelayChanged();
void BatteryIsPresentChanged();
void BatteryPercentageChanged();
void BatteryPlanChanged();
void BatteryStateChanged();
void BatterySuspendDelayChanged();
void LidClosedActionChanged();
void LidIsPresentChanged();
void LinePowerIdleDelayChanged();
void LinePowerPlanChanged();
void LinePowerSuspendDelayChanged();
void LockWhenActiveChanged();
void OnBatteryChanged();
void PlanInfoChanged();
void PowerButtonActionChanged();
};

namespace com {
  namespace deepin {
    namespace daemon {
      typedef ::DBusPower DBusPower;
    }
  }
}
#endif