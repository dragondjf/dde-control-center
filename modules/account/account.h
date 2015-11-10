#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <QObject>
#include <QtPlugin>
#include "interfaces.h"
#include "ui/accountmainwidget.h"

class QLabel;
class QFrame;
class Account: public QObject, ModuleInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.deepin.ControlCenter.ModuleInterface" FILE "account.json")
    Q_INTERFACES(ModuleInterface)

public:
    Account();
    ~Account() Q_DECL_OVERRIDE;
    QFrame* getContent() Q_DECL_OVERRIDE;

private slots:
    void preUnload();

private:
    QLabel * m_label;
    AccountMainWidget*m_mainWidget;
};

#endif