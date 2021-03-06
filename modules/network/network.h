/**
 * Copyright (C) 2015 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QtPlugin>

#include "interfaces.h"

class QLabel;
class NetworkMainWidget;

class Network: public QObject, ModuleInterface
{
    Q_OBJECT

public:
    Network(QObject *parent=0);
    ~Network();
    QFrame *getContent();

    ControlCenterProxyInterface *getInterface() const;
    void setProxy(ControlCenterProxyInterface *proxy) Q_DECL_OVERRIDE;

signals:
    void dccVisibleChanged(bool visible);

private:
    NetworkMainWidget *m_mainWidget;
};

class NetworkModule: public QObject, ModuleInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.deepin.ControlCenter.ModuleInterface" FILE "network.json")
    Q_INTERFACES(ModuleInterface)

public:
    QFrame *getContent() Q_DECL_OVERRIDE;
    void setProxy(ControlCenterProxyInterface *proxy) Q_DECL_OVERRIDE;

private:
    Network *m_network = NULL;
};

#endif
