#include "consdefine.h"
#include "propertyview.h"
#include "ui_propertyview.h"
#include <QPropertyAnimation>

PropertyView::PropertyView(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PropertyView)
{
    ui->setupUi(this);

    QRect rect = geometry();
    QRect parentRect = parent->geometry();

    rect.setY(PROPERTY_VIEW_STARTY);
    rect.setX(parentRect.width() - PROPERTY_VIEW_WIDTH);
    rect.setSize(QSize(PROPERTY_VIEW_WIDTH, parentRect.height()));
    setGeometry(rect);

    m_optionWidth = PROPERTY_VIEW_WIDTH;
    m_optionVisible = true;
}

void PropertyView::resizeEvent(QResizeEvent *size)
{
    if (m_optionVisible)
        m_optionWidth = size->size().width();
    ui->tabWidget->resize(size->size());
}

void PropertyView::optionAnimationShow()
{
    QRect rect = geometry();

    QWidget *parent = (QWidget *)(this->parent());
    int parentWidth = parent->width();

    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    if (m_optionVisible) {
        rect.setWidth(m_optionWidth);
        animation->setStartValue(rect);

        rect.setX(parentWidth);
        rect.setWidth(0);
        animation->setEndValue(rect);
    }
    else {
        rect.setWidth(0);
        animation->setStartValue(rect);

        rect.setX(parentWidth - m_optionWidth);
        rect.setWidth(m_optionWidth);
        animation->setEndValue(rect);
    }

    m_optionVisible = !m_optionVisible;
    animation->setDuration(100);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

PropertyView::~PropertyView()
{
    delete ui;
}
