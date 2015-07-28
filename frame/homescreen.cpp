#include <QDebug>
#include <QGridLayout>
#include <QPixmap>
#include <QLabel>
#include <QEvent>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "homescreen.h"
#include "constants.h"
#include "dclickablelabel.h"

HomeScreen::HomeScreen(QList<ModuleMetaData> modules, QWidget *parent) :
    QFrame(parent)
{
    m_grid = new QGridLayout;
    foreach (ModuleMetaData meta, modules) {
        ModuleButton * button = new ModuleButton(meta, this);

        m_grid->addWidget(button, m_moduleCount / 3, m_moduleCount % 3);
        ++m_moduleCount;

        connect(button, &ModuleButton::clicked, this, &HomeScreen::buttonClicked);
    }

#if 1 // just test more buttons
    for (int i(0); i != 3; ++i)
        foreach (ModuleMetaData meta, modules) {
            ModuleButton * button = new ModuleButton(meta, this);

            m_grid->addWidget(button, m_moduleCount / 3, m_moduleCount % 3);
            ++m_moduleCount;

            connect(button, &ModuleButton::clicked, this, &HomeScreen::buttonClicked);
        }
#endif
    m_grid->setContentsMargins(0, 25, 0, 0);

    QVBoxLayout *centerVLayout = new QVBoxLayout;
    QSpacerItem *vSpace = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);
    centerVLayout->addLayout(m_grid);
    centerVLayout->addSpacerItem(vSpace);

    m_centerWidget = new QWidget(this);
    m_centerWidget->setLayout(centerVLayout);

    QWidget *topOuterWidget = new QWidget(this);
    topOuterWidget->setFixedHeight(DCC::HomeScreen_TopWidgetHeight);
    topOuterWidget->setFixedWidth(DCC::ControlCenterWidth);

    DClickablePictureLabel *topButton = new DClickablePictureLabel(0, "shutdown_normal.png", "", "");
    topButton->setAttribute(Qt::WA_TranslucentBackground);

    QLabel *topLabel = new QLabel();
    topLabel->setAlignment(Qt::AlignCenter);
    topLabel->setStyleSheet(QString("color:%1;").arg("white"));
#ifdef QT_DEBUG // for test username label
    topLabel->setText("TestUserName");
#endif

    QHBoxLayout *topHBox_top = new QHBoxLayout;
    topHBox_top->addStretch();
    topHBox_top->addWidget(topButton);
    topHBox_top->addStretch();
    topHBox_top->setContentsMargins(0, 20, 0, 0);

    QHBoxLayout *topHBox_bot = new QHBoxLayout;
    topHBox_bot->addStretch();
    topHBox_bot->addWidget(topLabel);
    topHBox_bot->addStretch();

    QVBoxLayout *topVBox = new QVBoxLayout;
    topVBox->addLayout(topHBox_top);
    topVBox->addLayout(topHBox_bot);

    m_topWidget = new QWidget(topOuterWidget);
    m_topWidget->setFixedSize(topOuterWidget->size());
    m_topWidget->setLayout(topVBox);
    m_topWidget->setStyleSheet(QString("background-color:%1;").arg(DCC::BgDarkColor.name()));

    DClickablePictureLabel *bottomButton = new DClickablePictureLabel(0, "shutdown_normal.png", "shutdown_hover.png", "");
    bottomButton->setAttribute(Qt::WA_TranslucentBackground);

    QLabel *bottomLabel = new QLabel(tr("电源"));
    bottomLabel->setAlignment(Qt::AlignCenter);
    bottomLabel->setStyleSheet(QString("color:%1;").arg(DCC::TextNormalColor.name()));

    QVBoxLayout *bottomVLayout = new QVBoxLayout;
    bottomVLayout->addWidget(bottomButton);
    bottomVLayout->addWidget(bottomLabel);
    bottomVLayout->setSpacing(0);
    bottomVLayout->setContentsMargins(0, 0, 0, 10);

    QHBoxLayout *bottomHLayout = new QHBoxLayout;
    bottomHLayout->addStretch();
    bottomHLayout->addLayout(bottomVLayout);
    bottomHLayout->addStretch();
    bottomHLayout->setSpacing(0);
    bottomHLayout->setMargin(0);

    QWidget *bottomOuterWidget = new QWidget(this);
    bottomOuterWidget->setFixedHeight(DCC::HomeScreen_BottomWidgetHeight);
    bottomOuterWidget->setFixedWidth(DCC::ControlCenterWidth);

    m_bottomWidget = new QWidget(bottomOuterWidget);
    m_bottomWidget->setStyleSheet("background-image:url(modules/icons/shutdown_bg.png);");
    m_bottomWidget->setLayout(bottomHLayout);
    m_bottomWidget->setFixedSize(bottomOuterWidget->size());

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(topOuterWidget);
    mainLayout->addWidget(m_centerWidget);
    mainLayout->addWidget(bottomOuterWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    this->setLayout(mainLayout);

    m_opacityEffect = new QGraphicsOpacityEffect;
    m_opacityEffect->setOpacity(1.0);

    m_centerWidget->setGraphicsEffect(m_opacityEffect);

    connect(bottomButton, SIGNAL(clicked()), this, SLOT(powerButtonClicked()));
    connect(topButton, SIGNAL(clicked()), this, SLOT(userAvatarClicked()));
}

void HomeScreen::hide()
{
    QPropertyAnimation *aniHideCenterWidget = new QPropertyAnimation(m_opacityEffect, "opacity");
    aniHideCenterWidget->setStartValue(1.0);
    aniHideCenterWidget->setEndValue(0.0);
    aniHideCenterWidget->setDuration(DCC::FrameAnimationDuration);

    QPropertyAnimation *aniHideBottomWidget = new QPropertyAnimation(m_bottomWidget, "geometry");
    aniHideBottomWidget->setStartValue(QRect(0, 0, m_bottomWidget->width(), m_bottomWidget->height()));
    aniHideBottomWidget->setEndValue(QRect(0, m_bottomWidget->height(), m_bottomWidget->width(), m_bottomWidget->height()));
    aniHideBottomWidget->setDuration(DCC::FrameAnimationDuration);
    aniHideBottomWidget->setEasingCurve(QEasingCurve::OutQuart);

    QPropertyAnimation *aniHideTopWidget = new QPropertyAnimation(m_topWidget, "geometry");
    aniHideTopWidget->setStartValue(QRect(0, 0, m_topWidget->width(), m_topWidget->height()));
    aniHideTopWidget->setEndValue(QRect(0, -m_topWidget->height(), m_topWidget->width(), m_topWidget->height()));
    aniHideTopWidget->setDuration(DCC::FrameAnimationDuration);
    aniHideTopWidget->setEasingCurve(QEasingCurve::OutQuart);

    connect(aniHideCenterWidget, &QPropertyAnimation::finished, [this] () -> void {QFrame::hide();});

    aniHideCenterWidget->start();
    aniHideBottomWidget->start();
    aniHideTopWidget->start();
}

void HomeScreen::show()
{
    QPropertyAnimation *aniShowCenterWidget = new QPropertyAnimation(m_opacityEffect, "opacity");
    aniShowCenterWidget->setStartValue(0.0);
    aniShowCenterWidget->setEndValue(1.0);
    aniShowCenterWidget->setDuration(DCC::FrameAnimationDuration);

    QPropertyAnimation *aniShowBottomWidget = new QPropertyAnimation(m_bottomWidget, "geometry");
    aniShowBottomWidget->setEndValue(QRect(0, 0, m_bottomWidget->width(), m_bottomWidget->height()));
    aniShowBottomWidget->setStartValue(QRect(0, m_bottomWidget->height(), m_bottomWidget->width(), m_bottomWidget->height()));
    aniShowBottomWidget->setDuration(DCC::FrameAnimationDuration);
    aniShowBottomWidget->setEasingCurve(QEasingCurve::InQuad);

    QPropertyAnimation *aniShowTopWidget = new QPropertyAnimation(m_topWidget, "geometry");
    aniShowTopWidget->setEndValue(QRect(0, 0, m_topWidget->width(), m_topWidget->height()));
    aniShowTopWidget->setStartValue(QRect(0, -m_topWidget->height(), m_topWidget->width(), m_topWidget->height()));
    aniShowTopWidget->setDuration(DCC::FrameAnimationDuration);
    aniShowTopWidget->setEasingCurve(QEasingCurve::InQuad);

    aniShowCenterWidget->start();
    aniShowBottomWidget->start();
    aniShowTopWidget->start();
    QFrame::show();
}

void HomeScreen::buttonClicked()
{
    ModuleButton * btn = qobject_cast<ModuleButton*>(sender());
    this->moduleSelected(btn->metaData());
}

void HomeScreen::powerButtonClicked()
{
    qDebug() << "power button clicked";
}

void HomeScreen::userAvatarClicked()
{
    qDebug() << "user avatar clicked";
}

// class ModuleButton
ModuleButton::ModuleButton(ModuleMetaData metaData, QWidget * parent) :
    QFrame(parent),
    m_meta(metaData)
{
    setFixedSize(96, 96);
    setMouseTracking(true);

    m_icon = new QLabel(this);
    m_text = new QLabel(this);
    m_text->setText(m_meta.name);
    m_text->setAlignment(Qt::AlignCenter);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addStretch();
    hLayout->addWidget(m_icon);
    hLayout->addStretch();

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayout);
    vLayout->addWidget(m_text);

    this->setLayout(vLayout);

    setState(Normal);
}

ModuleMetaData ModuleButton::metaData()
{
    return m_meta;
}

void ModuleButton::enterEvent(QEvent *)
{
    this->setState(Hover);
}

void ModuleButton::leaveEvent(QEvent *)
{
    this->setState(Normal);
}

void ModuleButton::mousePressEvent(QMouseEvent *)
{
    this->clicked();
}

void ModuleButton::mouseReleaseEvent(QMouseEvent *)
{
//    this->setState(Hover);
}

void ModuleButton::setState(State state)
{
    switch (state) {
    case Normal:
        this->setStyleSheet("QFrame { background-color: transparent; border-radius: 3 }");
        m_icon->setPixmap(QPixmap(QString("modules/icons/%1").arg(m_meta.normalIcon)));
        m_text->setStyleSheet(QString("QLabel { color: %1 }").arg(DCC::TextNormalColor.name()));
        break;
    case Hover:
        this->setStyleSheet(QString("QFrame { background-color: %1; border-radius: 3 }").arg(DCC::BgDarkColor.name()));
        m_icon->setPixmap(QPixmap(QString("modules/icons/%1").arg(m_meta.hoverIcon)));
        m_text->setStyleSheet(QString("QLabel { color: %1 }").arg(DCC::TextHoverColor.name()));
        break;
    default:
        break;
    }
}