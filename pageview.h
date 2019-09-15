#ifndef PAGEVIEW_H
#define PAGEVIEW_H

#include <QFrame>
#include <QResizeEvent>
#include <QDebug>

namespace Ui {
class PageView;
}

class PageView : public QFrame
{
    Q_OBJECT

public:
    explicit PageView(QWidget *parent = nullptr);
    ~PageView();

protected:
    void resizeEvent(QResizeEvent *size);

public Q_SLOTS:
    void pageAnimationShow();

public:
    bool m_pageVisible;
    int m_pageWidth;

private:
    Ui::PageView *ui;
};

#endif // PAGEVIEW_H
