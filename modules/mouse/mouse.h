/**
 * Copyright (C) 2015 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#ifndef MOUSE_H
#define MOUSE_H

#include <QObject>
#include <QtPlugin>
#include <QLabel>
#include <QTimer>

#include <dtextbutton.h>
#include <dheaderline.h>
#include <dbaseline.h>
#include <dseparatorhorizontal.h>
#include <dslider.h>
#include <dsegmentedcontrol.h>
#include <dswitchbutton.h>

#include "interfaces.h"
#include "dbus/dbusmouse.h"
#include "dbus/dbustouchpad.h"
#include "dbus/dbustrackpoint.h"

DWIDGET_USE_NAMESPACE

class ContainerWidget;
class ModuleHeader;
class QLabel;
class QFrame;
class Mouse: public QObject
{
    Q_OBJECT

public:
    Mouse(QObject *parent = NULL);
    ~Mouse();
    QFrame *getContent();

public slots:
    void setMousePrimaryButton(int index);
    void setMousePointSpeed();
    void setMouseDoubleClickInterval();
    void disableTouchpadWhenMousePluggedIn(bool flag);

    void enableTouchpad(bool flag);
    void setTouchpadPointSpeed();
    void enableTouchpadNatureScroll(bool flag);
    void enableTouchpadTapToClick(bool flag);
    void enableTouchpadTwoFingerScroll(bool flag);
    void enableTouchpadEdgeScroll(bool flag);
    void onTouchPadExistChanged();
    void onTrackpointExistChanged();

    void setTrackpointSpeed();

    void reset();
private:
    QLabel *m_label;

    ComDeepinDaemonInputDeviceMouseInterface *m_mouseInterface;
    ComDeepinDaemonInputDeviceTouchPadInterface *m_touchpadInterface;
    TrackPointInterface *m_trackpointInterface;

    ModuleHeader *m_topHeaderLine;
    DSeparatorHorizontal *m_firstHSeparator;
    QWidget *m_mouseSettingPanel;
    QVBoxLayout *m_mouseSettingPanelLayout;
    QWidget *m_primaryButtonContainer;
    QHBoxLayout *m_primaryButtonContainerLayout;
    QLabel *m_primaryButtonSetting;
    DSegmentedControl *m_mousePrimaryButtonSetting;
    QWidget *m_pointSpeedContainer;
    QHBoxLayout *m_pointSpeedContainerLayout;
    QLabel *m_pointSpeedLabel;
    DSlider *m_mousePointSpeedSlider;
    QTimer *m_mousePointSpeedSetTimer;
    QWidget *m_doubleClickSpeedContainer;
    QHBoxLayout *m_doubleClickContainerLayout;
    QLabel *m_doubleClickSpeedLabel;
    DSlider *m_doubleClickIntervalSlider;
    QTimer *m_doubleClickIntervalTimer;
    QWidget *m_forbiddenTouchpadWhenMouseContainer;
    QHBoxLayout *m_forbiddenTouchpadWhenMouseLayout;
    QLabel *m_forbiddenTouchpadWhenMouseLabel;
    DSwitchButton *m_forbiddenTouchpadWhenMouseSwitchButton;
    DSeparatorHorizontal *m_secondHSeparator;
    DHeaderLine *m_touchpadHeaderLine;
    DSwitchButton *m_touchpadSwitchButton;
    DSeparatorHorizontal *m_thirdHSeparator;
    ContainerWidget *m_touchpadSettingPanel;
    DSegmentedControl *m_touchpadPrimaryButtonSetting;
    DSlider *m_touchpadPointSpeedSlider;
    QTimer *m_touchpadPointSpeedSetTimer;
    DSlider *m_touchpadDragThreshold;
    QTimer *m_touchpadDragThresholdSetTimer;
    DSwitchButton *m_touchpadNatureScrollSwitch;
    DSwitchButton *m_touchpadTapToClickSwitch;
    DSwitchButton *m_touchpadTwoFingerScrollSwitch;
    DSwitchButton *m_touchpadEdgeScrollSwitch ;
    DSeparatorHorizontal *m_fourthHSeparator;
    DSeparatorHorizontal *m_fifthHSeparator;
    double m_mousePointSpeed;
    double m_touchpadPointSpeed;
    double m_trackpointSpeed;

    DHeaderLine *m_trackpointHeaderLine;
    DSlider *m_trackpointSpeedSlider;
    QTimer *m_trackpointSpeedSetTimer;
    ContainerWidget *m_trackpointSettingPanel;

    void setWidgetsValue();
};


class ContainerWidget: public QWidget
{
    Q_OBJECT
public:
    ContainerWidget(QWidget *parent = 0);
    ~ContainerWidget();

    void addRow(const QString &text, QWidget *widget);
    void addRow(const QString &test, int stretch, QWidget *widget, int spacing = 5);

private:
    int m_labelWidth;
    int m_rowHeight;
};


class MouseModule: public QObject, ModuleInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.deepin.ControlCenter.ModuleInterface" FILE "mouse.json")
    Q_INTERFACES(ModuleInterface)

public:
    QFrame *getContent() Q_DECL_OVERRIDE;

private:
    Mouse   *m_mouse = NULL;
};

#endif // MOUSE_H
