#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QStatusBar>
#include <QResizeEvent>
#include <QDebug>

#include "consdefine.h"

namespace Ui {
class StatusBar;
}

class StatusBar : public QStatusBar
{
    Q_OBJECT

public:
    explicit StatusBar(QWidget *parent = nullptr);
    ~StatusBar();

protected:
    void resizeEvent(QResizeEvent *size);

public Q_SLOTS:
    void zoomValueChanged(int value);
    void zoomPlusPressed();
    void zoomMinusPressed();
    void onOperaCodeChanged(qint16 opCode);
    void onPositionChanged(QPoint pos);

Q_SIGNALS:
    void zoomChanged(int value);

private:
    Ui::StatusBar *ui;
};

#endif // STATUSBAR_H
