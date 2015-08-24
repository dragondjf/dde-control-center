#include <QLabel>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include "constants.h"

#include "moduleheader.h"

#include "mouse.h"

DUI_USE_NAMESPACE


/// as long as the qslider can't have float value,
/// 	here , we have some value expanded. So pay attention.


Mouse::Mouse()
{
    m_label = new QLabel();
    m_label->setStyleSheet(QString("QLabel{color: %1;font-size:12px;}").arg(DCC::TextNormalColor.name()));
    QVBoxLayout * layout = new QVBoxLayout(m_label);
    layout->setMargin(0);
    layout->setSpacing(0);

    m_mouseInterface = new ComDeepinDaemonInputDeviceMouseInterface("com.deepin.daemon.InputDevices",
                                                                    "/com/deepin/daemon/InputDevice/Mouse", QDBusConnection::sessionBus(), this);
    m_touchpadInterface = new ComDeepinDaemonInputDeviceTouchPadInterface("com.deepin.daemon.InputDevices",
                                                                          "/com/deepin/daemon/InputDevice/TouchPad", QDBusConnection::sessionBus(), this);
    //////////////////////////////////////////////////////////////-- top header
    m_topHeaderLine = new ModuleHeader(tr("Mouse And Touchpad"));

    //////////////////////////////////////////////////////////////-- horizontal separator
    m_firstHSeparator = new DSeparatorHorizontal(m_label);

    //////////////////////////////////////////////////////////////-- mouse setting panel
    m_mouseSettingPanel = new QWidget(m_label);
    m_mouseSettingPanelLayout = new QVBoxLayout(m_mouseSettingPanel);
    m_mouseSettingPanel->setLayout(m_mouseSettingPanelLayout);

    /// primary button setting part
    m_primaryButtonContainer = new QWidget(m_mouseSettingPanel);
    m_primaryButtonContainerLayout = new QHBoxLayout(m_primaryButtonContainer);
    m_primaryButtonContainer->setLayout(m_primaryButtonContainerLayout);
    m_primaryButtonContainerLayout->setMargin(0);

    m_primaryButtonSetting = new QLabel(tr("Primary Button"));

    m_mousePrimaryButtonSetting = new DSegmentedControl(m_primaryButtonContainer);
    m_mousePrimaryButtonSetting->addSegmented(tr("Left Button"));
    m_mousePrimaryButtonSetting->addSegmented(tr("Right Button"));

    m_primaryButtonContainerLayout->addWidget(m_primaryButtonSetting);
    m_primaryButtonContainerLayout->addWidget(m_mousePrimaryButtonSetting);
    /// point speed setting part
    m_pointSpeedContainer = new QWidget(m_mouseSettingPanel);
    m_pointSpeedContainerLayout = new QHBoxLayout(m_pointSpeedContainer);
    m_pointSpeedContainer->setLayout(m_pointSpeedContainerLayout);
    m_pointSpeedContainerLayout->setMargin(0);

    m_pointSpeedLabel = new QLabel(tr("Point Speed"));
    m_mousePointSpeedSlider = new DSlider(Qt::Horizontal);
    m_mousePointSpeedSlider->setMinimumSize(180, 20);

    m_pointSpeedContainerLayout->addWidget(m_pointSpeedLabel);
    m_pointSpeedContainerLayout->addWidget(m_mousePointSpeedSlider);

    /// double click setting part
    m_doubleClickSpeedContainer = new QWidget(m_mouseSettingPanel);
    m_doubleClickContainerLayout = new QHBoxLayout(m_doubleClickSpeedContainer);
    m_doubleClickSpeedContainer->setLayout(m_doubleClickContainerLayout);
    m_doubleClickContainerLayout->setMargin(0);

    m_doubleClickSpeedLabel = new QLabel(tr("Double Click Speed"));
    m_mouseDoubleClickIntervalSlider = new DSlider(Qt::Horizontal);
    m_mouseDoubleClickIntervalSlider->setMinimumSize(180, 20);

    m_doubleClickContainerLayout->addWidget(m_doubleClickSpeedLabel);
    m_doubleClickContainerLayout->addWidget(m_mouseDoubleClickIntervalSlider);


    //////////////////////////////////////////////////////////////-- mouse or touchpad
    m_forbiddenTouchpadWhenMouseContainer = new QWidget(m_mouseSettingPanel);
    m_forbiddenTouchpadWhenMouseLayout = new QHBoxLayout(m_forbiddenTouchpadWhenMouseContainer);
    m_forbiddenTouchpadWhenMouseContainer->setLayout(m_forbiddenTouchpadWhenMouseLayout);
    // TODO: label has too much text, font may need to be set
    m_forbiddenTouchpadWhenMouseLabel = new QLabel(tr("Disable touchpad when"
                                                             " the mouse is plugged in"));
    m_forbiddenTouchpadWhenMouseSwitchButton = new DSwitchButton(m_forbiddenTouchpadWhenMouseContainer);
    m_forbiddenTouchpadWhenMouseSwitchButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_forbiddenTouchpadWhenMouseLayout->addWidget(m_forbiddenTouchpadWhenMouseLabel);
    m_forbiddenTouchpadWhenMouseLayout->addStretch(0);
    m_forbiddenTouchpadWhenMouseLayout->addWidget(m_forbiddenTouchpadWhenMouseSwitchButton);
    m_forbiddenTouchpadWhenMouseLayout->addSpacing(4);
    m_forbiddenTouchpadWhenMouseLayout->setMargin(0);

    ///
    m_mouseSettingPanelLayout->addWidget(m_primaryButtonContainer);
    m_mouseSettingPanelLayout->addSpacing(10);
    m_mouseSettingPanelLayout->addWidget(m_pointSpeedContainer);
    m_mouseSettingPanelLayout->addSpacing(10);
    m_mouseSettingPanelLayout->addWidget(m_doubleClickSpeedContainer);
    m_mouseSettingPanelLayout->addSpacing(10);
    m_mouseSettingPanelLayout->addWidget(m_forbiddenTouchpadWhenMouseContainer);
    m_mouseSettingPanelLayout->addSpacing(10);

    //////////////////////////////////////////////////////////////-- horizontal separator
    m_secondHSeparator = new DSeparatorHorizontal(m_label);

    //////////////////////////////////////////////////////////////-- touchpad header line
    m_touchpadHeaderLine = new DHeaderLine(m_label);
    m_touchpadSwitchButton = new DSwitchButton(m_touchpadHeaderLine);
    m_touchpadHeaderLine->setTitle(tr("Touchpad"));
    m_touchpadHeaderLine->setContent(m_touchpadSwitchButton);
    m_touchpadSwitchButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //////////////////////////////////////////////////////////////-- horizontal separator
    m_thirdHSeparator = new DSeparatorHorizontal(m_label);

    //////////////////////////////////////////////////////////////-- touchpad setting panel
    m_touchpadSettingPanel = new ContainerWidget(m_label);

    m_touchpadPrimaryButtonSetting = new DSegmentedControl(m_touchpadSettingPanel);
    m_touchpadPrimaryButtonSetting->addSegmented(tr("Left Button"));
    m_touchpadPrimaryButtonSetting->addSegmented(tr("Right Button"));

    m_touchpadPointSpeedSlider = new DSlider(Qt::Horizontal);
    m_touchpadDoubleClickSpeed = new DSlider(Qt::Horizontal);
    m_touchpadDragThreshold = new DSlider(Qt::Horizontal);

    m_touchpadPointSpeedSlider->setMinimumSize(180, 20);
    m_touchpadDoubleClickSpeed->setMinimumSize(180, 20);
    m_touchpadDragThreshold->setMinimumSize(180, 20);

    m_touchpadNatureScrollSwitch = new DSwitchButton();
    m_touchpadTapToClickSwitch = new DSwitchButton();
    m_touchpadTwoFingerScrollSwitch = new DSwitchButton();
    m_touchpadEdgeScrollSwitch = new DSwitchButton();

    m_touchpadNatureScrollSwitch->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_touchpadTapToClickSwitch->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_touchpadTwoFingerScrollSwitch->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_touchpadEdgeScrollSwitch->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_touchpadSettingPanel->addRow(tr("Primary Button"), 0, m_touchpadPrimaryButtonSetting);
    m_touchpadSettingPanel->addRow(tr("Tracking Speed"), m_touchpadPointSpeedSlider);
    m_touchpadSettingPanel->addRow(tr("Double Click Speed"), m_touchpadDoubleClickSpeed);
    m_touchpadSettingPanel->addRow(tr("Drag Thredshold"), m_touchpadDragThreshold);
    m_touchpadSettingPanel->addRow(tr("Nature Scroll"), 0, m_touchpadNatureScrollSwitch);
    m_touchpadSettingPanel->addRow(tr("Tap To Click"), 0, m_touchpadTapToClickSwitch);
    m_touchpadSettingPanel->addRow(tr("Two Finger Scroll"), 0, m_touchpadTwoFingerScrollSwitch);
    m_touchpadSettingPanel->addRow(tr("Edge Scroll"), 0, m_touchpadEdgeScrollSwitch);

    //////////////////////////////////////////////////////////////-- horizontal separator
    m_fourthHSeparator = new DSeparatorHorizontal(m_label);

    //////////////////////////////////////////////////////////////
    // normalize the style of those labels , buttons
    // TODO: maybe we can make this kind of label a single class, and so as container

    int labelWidth = 100;
    m_primaryButtonSetting->setFixedWidth(labelWidth);
    m_pointSpeedLabel->setFixedWidth(labelWidth);
    m_doubleClickSpeedLabel->setFixedWidth(labelWidth);
    m_forbiddenTouchpadWhenMouseLabel->setFixedWidth(labelWidth);

    m_primaryButtonSetting->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    m_pointSpeedLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    m_doubleClickSpeedLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    m_forbiddenTouchpadWhenMouseLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

    m_doubleClickSpeedLabel->setWordWrap(true);
    m_forbiddenTouchpadWhenMouseLabel->setWordWrap(true);

    onTouchPadExistChanged();////update widgets visible property
    m_mouseSettingPanel->setVisible(m_mouseInterface->exist());

    layout->addWidget(m_topHeaderLine);
    layout->addWidget(m_firstHSeparator);
    layout->addWidget(m_mouseSettingPanel);
    layout->addWidget(m_secondHSeparator);
    layout->addWidget(m_touchpadHeaderLine);
    layout->addWidget(m_thirdHSeparator);
    layout->addWidget(m_touchpadSettingPanel);
    layout->addWidget(m_fourthHSeparator);
    layout->addStretch(1);


    ////////////////////////////////////////////////////////////// init those widgets state
    setWidgetsValue();
    ////////////////////////////////////////////////////////////// init those widgets state
    connect(m_topHeaderLine, &ModuleHeader::resetButtonClicked, this, &Mouse::reset);
    connect(m_mousePrimaryButtonSetting, SIGNAL(currentChanged(int)), this, SLOT(setMousePrimaryButton(int)));
    connect(m_mouseInterface, &ComDeepinDaemonInputDeviceMouseInterface::leftHandedChanged,
            [&](bool arg){
            m_mousePrimaryButtonSetting->setCurrentIndex((int)arg);
    });
    connect(m_mousePointSpeedSlider, SIGNAL(valueChanged(int)), this, SLOT(setMousePointSpeed(int)));
    connect(m_mouseInterface, &ComDeepinDaemonInputDeviceMouseInterface::motionAccelerationChanged,
            [&](double value){
        if(value != m_mousePointSpeed){
            m_mousePointSpeedSlider->setValue((3.2-value) *1000);
            m_mousePointSpeed = value;
        }
    });
    connect(m_mouseDoubleClickIntervalSlider, SIGNAL(valueChanged(int)), this, SLOT(setMouseDoubleClickInterval(int)));
    connect(m_mouseInterface, &ComDeepinDaemonInputDeviceMouseInterface::doubleClickChanged,
            [&](int value){
        m_mouseDoubleClickIntervalSlider->setValue(1000 - value);
    });
    connect(m_forbiddenTouchpadWhenMouseSwitchButton, SIGNAL(checkedChanged(bool)),
            this, SLOT(disableTouchpadWhenMousePluggedIn(bool)));
    connect(m_mouseInterface, &ComDeepinDaemonInputDeviceMouseInterface::disableTpadChanged,
            m_forbiddenTouchpadWhenMouseSwitchButton, &DSwitchButton::setChecked);
    connect(m_forbiddenTouchpadWhenMouseSwitchButton, SIGNAL(checkedChanged(bool)),
            m_touchpadSwitchButton, SLOT(setHidden(bool)));
    connect(m_touchpadSwitchButton, SIGNAL(checkedChanged(bool)), this, SLOT(enableTouchpad(bool)));
    connect(m_touchpadInterface, &ComDeepinDaemonInputDeviceTouchPadInterface::tpadEnableChanged,
            m_touchpadSwitchButton, &DSwitchButton::setChecked);
    connect(m_touchpadSwitchButton, SIGNAL(checkedChanged(bool)),
            m_touchpadSettingPanel, SLOT(setVisible(bool)));
    connect(m_touchpadSwitchButton, SIGNAL(checkedChanged(bool)),
            m_fourthHSeparator, SLOT(setVisible(bool)));
    connect(m_touchpadPointSpeedSlider, SIGNAL(valueChanged(int)), this, SLOT(setTouchpadPointSpeed(int)));
    connect(m_touchpadInterface, &ComDeepinDaemonInputDeviceTouchPadInterface::motionAccelerationChanged,
            [&](double value){
        if(value != m_touchpadPointSpeed){
            m_touchpadPointSpeedSlider->setValue((3.2-value)*1000);
            m_touchpadPointSpeed = value;
        }
    });
    connect(m_touchpadDoubleClickSpeed, SIGNAL(valueChanged(int)), this, SLOT(setTouchpadDoubleClickInterval(int)));
    connect(m_touchpadInterface, &ComDeepinDaemonInputDeviceTouchPadInterface::doubleClickChanged,
            [&](int value){
        m_touchpadDoubleClickSpeed->setValue(1000 - value);
    });
    connect(m_touchpadNatureScrollSwitch, SIGNAL(checkedChanged(bool)), this, SLOT(enableTouchpadNatureScroll(bool)));
    connect(m_touchpadInterface, &ComDeepinDaemonInputDeviceTouchPadInterface::naturalScrollChanged,
            m_touchpadNatureScrollSwitch, &DSwitchButton::setChecked);
    connect(m_touchpadTapToClickSwitch, SIGNAL(checkedChanged(bool)), this, SLOT(enableTouchpadTapToClick(bool)));
    connect(m_touchpadInterface, &ComDeepinDaemonInputDeviceTouchPadInterface::tapClickChanged,
            m_touchpadTapToClickSwitch, &DSwitchButton::setChecked);
    connect(m_touchpadTwoFingerScrollSwitch, SIGNAL(checkedChanged(bool)), this, SLOT(enableTouchpadTwoFingerScroll(bool)));
    connect(m_touchpadInterface, &ComDeepinDaemonInputDeviceTouchPadInterface::vertScrollChanged,
            m_touchpadTwoFingerScrollSwitch, &DSwitchButton::setChecked);
    connect(m_touchpadEdgeScrollSwitch, SIGNAL(checkedChanged(bool)), this, SLOT(enableTouchpadEdgeScroll(bool)));
    connect(m_touchpadInterface, &ComDeepinDaemonInputDeviceTouchPadInterface::edgeScrollChanged,
            m_touchpadEdgeScrollSwitch, &DSwitchButton::setChecked);
    connect(m_touchpadDragThreshold, &DSlider::valueChanged,
            m_touchpadInterface, &ComDeepinDaemonInputDeviceTouchPadInterface::setDragThreshold);
    connect(m_touchpadInterface, &ComDeepinDaemonInputDeviceTouchPadInterface::dragThresholdChanged,
            m_touchpadDragThreshold, &DSlider::setValue);
    connect(m_touchpadPrimaryButtonSetting, &DSegmentedControl::currentChanged,
            [&](int arg){
        m_touchpadInterface->setLeftHanded(arg);
    });
    connect(m_touchpadInterface, &ComDeepinDaemonInputDeviceTouchPadInterface::leftHandedChanged,
            [&](bool arg){
        m_touchpadPrimaryButtonSetting->setCurrentIndex((int)arg);
    });
    connect(m_mouseInterface, &ComDeepinDaemonInputDeviceMouseInterface::existChanged,
            [&](bool arg){
        m_mouseSettingPanel->setVisible(arg);
        m_secondHSeparator->setVisible(arg);
    });
    connect(m_touchpadInterface, &ComDeepinDaemonInputDeviceTouchPadInterface::existChanged,
            this, &Mouse::onTouchPadExistChanged);
}

void Mouse::reset() {
    QDBusPendingCall reply = m_mouseInterface->Reset();
    reply.waitForFinished();
}

void Mouse::setWidgetsValue() {
    m_mouseInterface->deviceList().printValue();
    if (m_mouseInterface->leftHanded() == true){
        m_mousePrimaryButtonSetting->setCurrentIndex(1);
    } else {
        m_mousePrimaryButtonSetting->setCurrentIndex(0);
    }

    m_mousePointSpeed = m_mouseInterface->motionAcceleration();
    m_mousePointSpeedSlider->setRange(200, 3000);	// 3 ~ 0.2
    m_mousePointSpeedSlider->setValue((3.2-m_mousePointSpeed) * 1000);

    m_mouseDoubleClickIntervalSlider->setRange(0, 900);	// 100 ~ 1000
    m_mouseDoubleClickIntervalSlider->setValue(1000 - m_mouseInterface->doubleClick());

    m_forbiddenTouchpadWhenMouseSwitchButton->setChecked(m_mouseInterface->disableTpad());

    if (m_touchpadInterface->tPadEnable()){
        m_touchpadSwitchButton->setChecked(true);
    } else {
        m_touchpadSwitchButton->setChecked(false);
    }

    m_touchpadPrimaryButtonSetting->setCurrentIndex((int)m_touchpadInterface->leftHanded());

    m_touchpadPointSpeed = m_touchpadInterface->motionAcceleration();
    m_touchpadPointSpeedSlider->setRange(200, 3000);	// 3 ~ 0.2
    m_touchpadPointSpeedSlider->setValue((3.2-m_touchpadPointSpeed) * 1000);

    m_touchpadDoubleClickSpeed->setRange(0, 900);	// not sure
    m_touchpadDoubleClickSpeed->setValue(1000 - m_touchpadInterface->doubleClick());

    m_touchpadDragThreshold->setRange(1, 10);	// not sure
    m_touchpadDragThreshold->setValue(m_touchpadInterface->dragThreshold());

    m_touchpadNatureScrollSwitch->setChecked(m_touchpadInterface->naturalScroll());
    m_touchpadTapToClickSwitch->setChecked(m_touchpadInterface->tapClick());
    m_touchpadTwoFingerScrollSwitch->setChecked(m_touchpadInterface->vertScroll());
    m_touchpadEdgeScrollSwitch->setChecked(m_touchpadInterface->edgeScroll());

}

void Mouse::setMousePrimaryButton(int index)
{
    if (index == 0){
        m_mouseInterface->setLeftHanded(false);
    } else {
        m_mouseInterface->setLeftHanded(true);
    }
}

void Mouse::setMousePointSpeed(int speed)
{
    // the value should be scaled
    m_mouseInterface->setMotionAcceleration((3200 - speed)/1000.0);
}

void Mouse::setMouseDoubleClickInterval(int interval)
{
    m_mouseInterface->setDoubleClick(1000 - interval);
}

void Mouse::disableTouchpadWhenMousePluggedIn(bool flag)
{
    m_mouseInterface->setDisableTpad(flag);
}

void Mouse::enableTouchpad(bool flag)
{
    m_touchpadInterface->setTPadEnable(flag);
}

void Mouse::setTouchpadPointSpeed(int speed)
{
    m_touchpadInterface->setMotionAcceleration((3200 - speed)/1000.0);
}

void Mouse::setTouchpadDoubleClickInterval(int interval)
{
    m_touchpadInterface->setDoubleClick(1000 - interval);
}

void Mouse::enableTouchpadNatureScroll(bool flag)
{
    m_touchpadInterface->setNaturalScroll(flag);
}

void Mouse::enableTouchpadTapToClick(bool flag)
{
    m_touchpadInterface->setTapClick(flag);
}

void Mouse::enableTouchpadTwoFingerScroll(bool flag)
{
    m_touchpadInterface->setVertScroll(flag);
}

void Mouse::enableTouchpadEdgeScroll(bool flag)
{
    m_touchpadInterface->setEdgeScroll(flag);
}

void Mouse::onTouchPadExistChanged()
{
    bool touchpadExist = m_touchpadInterface->exist();

    m_forbiddenTouchpadWhenMouseSwitchButton->setVisible(touchpadExist);
    m_forbiddenTouchpadWhenMouseLabel->setVisible(touchpadExist);
    m_touchpadHeaderLine->setVisible(touchpadExist);
    m_thirdHSeparator->setVisible(touchpadExist);
    m_touchpadSettingPanel->setVisible(touchpadExist);
    m_fourthHSeparator->setVisible(touchpadExist);
}

Mouse::~Mouse()
{
    qDebug() << "~Mouse()";

    m_label->deleteLater();
}

QFrame* Mouse::getContent()
{
    return m_label;
}


ContainerWidget::ContainerWidget(QWidget *parent)
    :QWidget(parent)
{
    QVBoxLayout * layout = new QVBoxLayout(this);
    setLayout(layout);

    m_labelWidth = 100;
    m_rowHeight = 35;
}

ContainerWidget::~ContainerWidget()
{
}

void ContainerWidget::addRow(const QString & text, QWidget * widget)
{
    QWidget * container = new QWidget(this);
    layout()->addWidget(container);
    container->setMinimumHeight(m_rowHeight);

    QHBoxLayout * containerLayout = new QHBoxLayout(container);
    container->setLayout(containerLayout);

    QLabel * label = new QLabel(text);
    label->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    label->setWordWrap(true);
    label->setFixedWidth(m_labelWidth);

    containerLayout->addWidget(label);
    containerLayout->addWidget(widget);
}

void ContainerWidget::addRow(const QString & text, int stretch, QWidget * widget, int spacing)
{
    QWidget * container = new QWidget(this);
    layout()->addWidget(container);
    container->setMinimumHeight(m_rowHeight);

    QHBoxLayout * containerLayout = new QHBoxLayout(container);
    container->setLayout(containerLayout);

    QLabel * label = new QLabel(text);
    label->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    label->setFixedWidth(m_labelWidth);
    label->setWordWrap(true);

    containerLayout->addWidget(label);
    containerLayout->addStretch(stretch);
    containerLayout->addWidget(widget);
    containerLayout->addSpacing(spacing);

    containerLayout->setMargin(0);
}