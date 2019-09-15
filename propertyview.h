#ifndef PROPERTYVIEW_H
#define PROPERTYVIEW_H

#include <QFrame>
#include <QResizeEvent>
#include <QDebug>

namespace Ui {
class PropertyView;
}

class PropertyView : public QFrame
{
    Q_OBJECT

public:
    explicit PropertyView(QWidget *parent = nullptr);
    ~PropertyView();

protected:
    void resizeEvent(QResizeEvent *size);

public Q_SLOTS:
    void optionAnimationShow();

public:
    bool m_optionVisible;
    int m_optionWidth;

private:
    Ui::PropertyView *ui;
};

#endif // PROPERTYVIEW_H
