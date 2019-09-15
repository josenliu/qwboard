#ifndef LEFTPANEL_H
#define LEFTPANEL_H

#include <QFrame>
#include <QResizeEvent>
#include <QDebug>

namespace Ui {
class LeftPanel;
}

class LeftPanel : public QFrame
{
    Q_OBJECT

public:
    explicit LeftPanel(QWidget *parent = nullptr);
    ~LeftPanel();

protected:
    void resizeEvent(QResizeEvent *size);

Q_SIGNALS:
    void expButtonPressed();
    void optButtonPressed();

public Q_SLOTS:
    void onExpButtonPressed();
    void onOptButtonPressed();

private:
    Ui::LeftPanel *ui;
};

#endif // LEFTPANEL_H
