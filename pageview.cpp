#include "consdefine.h"
#include "pageview.h"
#include "ui_pageview.h"
#include <QPropertyAnimation>

PageView::PageView(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PageView)
{
    ui->setupUi(this);

    QRect rect = geometry();
    rect.setX(PAGE_VIEW_STARTX);
    rect.setY(PAGE_VIEW_STARTY);
    rect.setWidth(PAGE_VIEW_WIDTH);
    setGeometry(rect);

    m_pageVisible = true;
    m_pageWidth = PAGE_VIEW_WIDTH;
}

void PageView::resizeEvent(QResizeEvent *size)
{
    QRect rect = ui->addButton->geometry();
    rect.setSize(QSize(ADD_BUTTON_WIDTH, ADD_BUTTON_HEIGHT));
    ui->addButton->setGeometry(rect);

    rect = ui->listView->geometry();
    rect.setWidth(size->size().width());
    rect.setHeight(size->size().height() - 32);
    ui->listView->setGeometry(rect);

    //if (m_pageVisible)
    //    m_pageWidth = size->size().width();
}

void PageView::pageAnimationShow()
{
    QRect rect = geometry();
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    if (m_pageVisible) {
        rect.setWidth(m_pageWidth);
        animation->setStartValue(rect);
        rect.setWidth(0);
        animation->setEndValue(rect);
    }
    else {
        rect.setWidth(0);
        animation->setStartValue(rect);
        rect.setWidth(m_pageWidth);
        animation->setEndValue(rect);
    }

    m_pageVisible = !m_pageVisible;
    animation->setDuration(100);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

PageView::~PageView()
{
    delete ui;
}
