#include <QEvent>

#include <libdui/dthememanager.h>

#include "listwidget.h"

ListWidget::ListWidget(CheckMode checkMode, QWidget *parent) :
    DScrollArea(parent),
    m_itemWidth(-1),
    m_itemHeight(-1),
    m_layout(new QVBoxLayout),
    m_checkMode(checkMode),
    m_mainWidget(new QWidget),
    m_visibleCount(0),
    m_checkable(false)
{
    D_THEME_INIT_WIDGET(ListWidget);

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);

    m_layout->setMargin(0);
    m_layout->setSpacing(0);
    m_layout->addStretch(1);

    m_mainWidget->setObjectName("MainWidget");
    m_mainWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_mainWidget->setLayout(m_layout);
    m_mainWidget->setFixedHeight(0);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setAlignment(Qt::AlignHCenter);
    setWidget(m_mainWidget);
    setMaximumHeight(0);
}

int ListWidget::addWidget(QWidget *w)
{
    insertWidget(count(), w);

    return count()-1;
}

void ListWidget::addWidgets(const QList<QWidget*> &ws)
{
    insertWidgets(count(), ws);
}

void ListWidget::insertWidget(int index, QWidget *w)
{
    if(w==NULL || m_widgetList.contains(w))
        return;

    m_widgetList.insert(index, w);

    if(m_itemWidth>0)
        w->setFixedWidth(m_itemWidth);
    if(m_itemHeight>0){
        w->setFixedHeight(m_itemHeight);
    }

    m_layout->insertWidget(index, w, 0, Qt::AlignCenter);
    if(m_checkable)
        w->installEventFilter(this);

    m_mapVisible[index] = true;

    setHeight(m_mainWidget->height() + w->height() + m_layout->spacing());
    setVisibleCount(m_visibleCount + 1);

    emit countChanged();
}

void ListWidget::insertWidgets(int index, const QList<QWidget*> &ws)
{
    foreach (QWidget *w, ws) {
        insertWidget(index++, w);
    }
}

void ListWidget::setItemSize(int w, int h)
{
    m_itemWidth = w;
    m_itemHeight = h;

    m_mainWidget->setFixedWidth(w);

    foreach (QWidget *w, m_widgetList) {
        if(m_itemWidth>0)
            w->setFixedWidth(m_itemWidth);
        if(m_itemHeight>0){
            w->setFixedHeight(m_itemHeight);
        }
    }
}

void ListWidget::clear()
{
    for(int i=0;i<count();++i){
        m_layout->removeItem(m_layout->takeAt(i));
        m_widgetList[i]->removeEventFilter(this);
        m_widgetList[i]->deleteLater();
    }

    m_mapVisible.clear();
    m_widgetList.clear();
    m_checkedList.clear();
    m_mainWidget->setFixedHeight(0);

    setMaximumHeight(0);
    setVisibleCount(0);

    emit countChanged();
}

void ListWidget::removeWidget(int index)
{
    QWidget *w = getWidget(index);

    m_widgetList.removeAt(index);
    m_layout->removeItem(m_layout->takeAt(index));
    m_checkedList.removeOne(index);

    if(m_mapVisible.value(index, false)){
        m_mapVisible.remove(index);
        setHeight(m_mainWidget->height() - w->height() - m_layout->spacing());
        setVisibleCount(m_visibleCount -1);
    }

    w->removeEventFilter(this);
    w->deleteLater();

    emit countChanged();
}

void ListWidget::showWidget(int index)
{
    QWidget *w = getWidget(index);

    if(!m_mapVisible.value(index, true)){
        w->show();
        m_mapVisible[index] = true;
        setVisibleCount(m_visibleCount+1);
        setHeight(m_mainWidget->height() + w->height() + m_layout->spacing());
    }
}

void ListWidget::hideWidget(int index)
{
    QWidget *w = getWidget(index);

    if(m_mapVisible.value(index, false)){
        w->hide();
        m_mapVisible[index] = false;
        setVisibleCount(m_visibleCount-1);
        setHeight(m_mainWidget->height() - w->height() - m_layout->spacing());
    }
}

void ListWidget::setChecked(int index, bool checked)
{
    if (!m_checkable || (checked && m_checkedList.contains(index))
            || (!checked && !m_checkedList.contains(index)))
        return;

    if(m_checkMode == Radio && checked){
        int checkedWidget = firstChecked();
        if(checkedWidget>=0){
            getWidget(checkedWidget)->setProperty("checked", false);
            m_checkedList.removeOne(checkedWidget);
        }
    }

    if(index>=0 && index < count()){
        QWidget *w = getWidget(index);
        w->setProperty("checked", checked);
    }

    if(checked){
        m_checkedList << index;
    }else{
        m_checkedList.removeOne(index);
    }

    if(m_checkMode == Radio && checked){
        emit firstCheckedChanged(index);
    }

    emit checkedChanged(index, checked);
}

void ListWidget::setCheckable(bool checkable)
{
    m_checkable = checkable;

    if (m_checkable == checkable)
        return;

    if(checkable){
        foreach (QWidget *w, m_widgetList) {
            w->installEventFilter(this);
        }
    }else{
        foreach (QWidget *w, m_widgetList) {
            w->removeEventFilter(this);
        }
    }
}

int ListWidget::count() const
{
    return m_widgetList.count();
}

int ListWidget::indexOf(const QWidget* w)
{
    return m_widgetList.indexOf(const_cast<QWidget*>(w));
}

QWidget *ListWidget::getWidget(int index) const
{
    return m_widgetList[index];
}

int ListWidget::firstChecked() const
{
    return m_checkedList.count()>0 ? m_checkedList.first() : -1;
}

bool ListWidget::checkable() const
{
    return m_checkable;
}

int ListWidget::visibleCount() const
{
    return m_visibleCount;
}

ListWidget::CheckMode ListWidget::checkMode() const
{
    return m_checkMode;
}

bool ListWidget::eventFilter(QObject *obj, QEvent *e)
{
    if(e->type() != QEvent::MouseButtonRelease)
        return false;

    QWidget *w = qobject_cast<QWidget*>(obj);

    if(w){
        int index = indexOf(w);
        if(index>=0){
            setChecked(index, true);
        }
    }

    return false;
}

void ListWidget::setVisibleCount(int count)
{
    if(m_visibleCount == count)
        return;

    m_visibleCount = count;

    emit visibleCountChanged(count);
}

void ListWidget::setHeight(int height)
{
    m_mainWidget->setFixedHeight(height);
    if(verticalScrollBarPolicy() == Qt::ScrollBarAlwaysOff){
        setFixedHeight(m_mainWidget->height());
    }else{
        setMaximumHeight(m_mainWidget->height());
    }
}

QList<QWidget*> ListWidget::widgetList() const
{
    return m_widgetList;
}

QSize ListWidget::itemSize() const
{
    return QSize(m_itemWidth, m_itemHeight);
}
