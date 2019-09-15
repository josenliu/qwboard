#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QGraphicsScene>
#include <QPropertyAnimation>
#include <QtDebug>

#include "leftpanel.h"
#include "toolbar.h"
#include "pageview.h"
#include "propertyview.h"
#include "drawview.h"
#include "statusbar.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *size);
    void repaint();

public Q_SLOTS:
    void resizeDrawView();

private:
    Ui::MainWindow *ui;
    LeftPanel *m_leftPanel;
    ToolBar *m_toolBar;
    PageView *m_pageView;
    PropertyView *m_propertyView;
    StatusBar *m_statusBar;

    DrawView *m_drawView;
};

#endif // MAINWINDOW_H
