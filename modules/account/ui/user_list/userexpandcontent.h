/**
 * Copyright (C) 2015 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#ifndef USEREXPANDCONTENT_H
#define USEREXPANDCONTENT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QStackedWidget>
#include <QFileDialog>
#include <QDir>
#include "dbus/dbusaccountuser.h"
#include "dsegmentedcontrol.h"
#include "dswitchlineexpand.h"
#include "webcamavatarpanel.h"
#include "passwordframe.h"
#include "avatargrid.h"
#include "../controlline.h"

DWIDGET_USE_NAMESPACE

class UserExpandContent : public QWidget
{
    Q_OBJECT
public:
    explicit UserExpandContent(const QString &userPath = "", QWidget *parent = 0);
    ~UserExpandContent();

public slots:
    void onRequestPreDestroy();

signals:
    void sizeChanged();
    void changeToSetting(bool value);

private slots:
    void initDBusData();
    void changeControlCenterHideable(bool hideable);

private:
    void initAvatarPanel();
    void initAutoLogin();
    void initUserEnable();
    void initPassword();

    void onAvatarSelected(const QString &avatar);
    void onAccountEnableChanged(bool enabled);

    void updateSize(bool note = true);
    void updatemAvatarGridSize();

private:
    QVBoxLayout *m_mainLayout = NULL;
    DBusAccountUser *m_accountUser = NULL;
    AvatarGrid *m_allAvatarGrid = NULL;
    QStackedWidget *m_stackWidget = NULL;
    PasswordFrame *m_passwordFrame = NULL;
    AccountSwitchLine *m_autoLoginLine = NULL;
    AccountSwitchLine *m_lockLine = NULL;

    QString m_userPath = "";
    bool m_isCurrentUser = false;

    const int LAYOUT_SPACING = 10;
    const QString ADD_AVATAR_ICON = ":/images/dark/images/avatar_add.png";
};

#endif // USEREXPANDCONTENT_H
