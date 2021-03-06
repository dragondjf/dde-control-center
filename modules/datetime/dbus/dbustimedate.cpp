/**
 * Copyright (C) 2015 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -c DBusTimedate -p dbustimedate com.deepin.daemon.Timedate.xml
 *
 * qdbusxml2cpp is Copyright (C) 2015 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#include "dbustimedate.h"

/*
 * Implementation of interface class DBusTimedate
 */

DBusTimedate::DBusTimedate(QObject *parent)
    : QDBusAbstractInterface("com.deepin.daemon.Timedate", "/com/deepin/daemon/Timedate", staticInterfaceName(), QDBusConnection::sessionBus(), parent)
{
    ZoneInfo::registerMetaType();
    QDBusConnection::sessionBus().connect(this->service(), this->path(), "org.freedesktop.DBus.Properties",  "PropertiesChanged", "sa{sv}as", this, SLOT(__propertyChanged__(QDBusMessage)));
}

DBusTimedate::~DBusTimedate()
{
    QDBusConnection::sessionBus().disconnect(service(), path(), "org.freedesktop.DBus.Properties",  "PropertiesChanged",  "sa{sv}as", this, SLOT(propertyChanged(QDBusMessage)));
}

ZoneInfo::ZoneInfo()
{

}

void ZoneInfo::registerMetaType()
{
    qRegisterMetaType<ZoneInfo>();
    qDBusRegisterMetaType<ZoneInfo>();
}

bool ZoneInfo::operator ==(const ZoneInfo &what) const
{
    // TODO: 这里只判断这两个成员应该就可以了
    return m_zoneName == what.m_zoneName &&
            m_utcOffset == what.m_utcOffset;
}

QDebug operator<<(QDebug argument, const ZoneInfo & info)
{
    argument << info.m_zoneName << ',' << info.m_zoneCity << ',' << info.m_utcOffset << ',';
    argument << info.i2 << ',' << info.i3 << ',' << info.i4 << endl;

    return argument;
}

QDBusArgument &operator<<(QDBusArgument & argument, const ZoneInfo & info)
{
    argument.beginStructure();
    argument << info.m_zoneName << info.m_zoneCity << info.m_utcOffset;
    argument.beginStructure();
    argument << info.i2 << info.i3 << info.i4;
    argument.endStructure();
    argument.endStructure();

    return argument;
}

QDataStream &operator<<(QDataStream & argument, const ZoneInfo & info)
{
    argument << info.m_zoneName << info.m_zoneCity << info.m_utcOffset;
    argument << info.i2 << info.i3 << info.i4;

    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument & argument, ZoneInfo & info)
{
    argument.beginStructure();
    argument >> info.m_zoneName >> info.m_zoneCity >> info.m_utcOffset;
    argument.beginStructure();
    argument >> info.i2 >> info.i3 >> info.i4;
    argument.endStructure();
    argument.endStructure();

    return argument;
}

const QDataStream &operator>>(QDataStream & argument, ZoneInfo & info)
{
    argument >> info.m_zoneName >> info.m_zoneCity >> info.m_utcOffset;
    argument >> info.i2 >> info.i3 >> info.i4;

    return argument;
}
