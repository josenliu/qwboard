#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  <QtOpenGL>

#include <QScreen>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_statusBar = new StatusBar(this);
    m_leftPanel = new LeftPanel(this);
    m_toolBar = new ToolBar(this);
    m_pageView = new PageView(this);
    m_propertyView = new PropertyView(this);
    m_drawView = new DrawView(this);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect r = screen->availableGeometry();
    setGeometry(r);

    connect(m_leftPanel, SIGNAL(expButtonPressed()), m_pageView, SLOT(pageAnimationShow()));
    connect(m_leftPanel, SIGNAL(optButtonPressed()), m_propertyView, SLOT(optionAnimationShow()));
    connect(m_leftPanel, SIGNAL(expButtonPressed()), this, SLOT(resizeDrawView()));
    connect(m_leftPanel, SIGNAL(optButtonPressed()), this, SLOT(resizeDrawView()));

    connect(m_statusBar, SIGNAL(zoomChanged(int)), m_drawView, SLOT(onZoomChanged(int)));

    connect(m_toolBar, SIGNAL(shapeModeChanged(qint16)), m_drawView, SIGNAL(drawCodeChanged(qint16)));
    connect(m_toolBar, SIGNAL(selectModeChanged(qint16)), m_drawView, SIGNAL(drawCodeChanged(qint16)));

    connect(m_toolBar, SIGNAL(shapeModeChanged(qint16)), m_statusBar, SLOT(onOperaCodeChanged(qint16)));
    connect(m_toolBar, SIGNAL(pasteModeChanged(qint16)), m_statusBar, SLOT(onOperaCodeChanged(qint16)));
    connect(m_toolBar, SIGNAL(cutModeChanged(qint16)), m_statusBar, SLOT(onOperaCodeChanged(qint16)));
    connect(m_toolBar, SIGNAL(copyModeChanged(qint16)), m_statusBar, SLOT(onOperaCodeChanged(qint16)));
    connect(m_toolBar, SIGNAL(textModeChanged(qint16)), m_statusBar, SLOT(onOperaCodeChanged(qint16)));
    connect(m_toolBar, SIGNAL(tableModeChanged(qint16)), m_statusBar, SLOT(onOperaCodeChanged(qint16)));
    connect(m_toolBar, SIGNAL(selectModeChanged(qint16)), m_statusBar, SLOT(onOperaCodeChanged(qint16)));
    connect(m_drawView, SIGNAL(mousePositionChanged(QPoint)), m_statusBar, SLOT(onPositionChanged(QPoint)));

}

void MainWindow::resizeEvent(QResizeEvent *size)
{
    if (size->size().height() <= (50 * 8 + 20)) {
        return;
    }

    double w, h;
    double tmp1, tmp2;

    QRect rect = m_statusBar->geometry();
    rect.setX(0);
    rect.setY(size->size().height() - STATUS_BAR_HEIGHT);
    rect.setWidth(size->size().width());
    rect.setHeight(STATUS_BAR_HEIGHT);
    m_statusBar->setGeometry(rect);

    rect = m_leftPanel->geometry();
    rect.setWidth(LEFT_PANEL_WIDTH);
    rect.setHeight(size->size().height() - STATUS_BAR_HEIGHT);
    m_leftPanel->setGeometry(rect);

    rect = m_toolBar->geometry();
    rect.setWidth(size->size().width() - LEFT_PANEL_WIDTH);
    rect.setHeight(TOOL_BAR_HEIGHT);
    m_toolBar->setGeometry(rect);

    rect = m_pageView->geometry();
    w = (size->size().width() - LEFT_PANEL_WIDTH) * PAGE_VIEW_COEF;
    if (w <= PAGE_VIEW_WIDTH) w = PAGE_VIEW_WIDTH;
    m_pageView->m_pageWidth = int(w);
    if (!m_pageView->m_pageVisible) w = rect.width();

    rect.setWidth(int(w));
    rect.setHeight(size->size().height() - TOOL_BAR_HEIGHT - STATUS_BAR_HEIGHT);
    m_pageView->setGeometry(rect);

    rect = m_propertyView->geometry();
    if (m_propertyView->m_optionVisible) {
        rect.setX(size->size().width() - PROPERTY_VIEW_WIDTH);
        rect.setWidth(PROPERTY_VIEW_WIDTH);
    }
    rect.setHeight(size->size().height() - TOOL_BAR_HEIGHT - STATUS_BAR_HEIGHT);
    m_propertyView->setGeometry(rect);

    w = size->size().width() - m_pageView->width() - m_propertyView->width() - LEFT_PANEL_WIDTH - 1;
    h = size->size().height() - TOOL_BAR_HEIGHT - STATUS_BAR_HEIGHT;
    int xpos = PAGE_VIEW_STARTX + m_pageView->width();
    int ypos = TOOL_BAR_STARTY + TOOL_BAR_HEIGHT; // rect.y();

    if (m_drawView->m_drawStyle == QWBAORD_PAGE_SIZE_169) {
        tmp1 = w * 9 / 16;  // new height;
        tmp2 = h * 16 / 9;  // new width;
        if (tmp1 > h) {
            xpos += (w - tmp2) / 2;
            w = tmp2;
        }

        if (tmp2 > w) {
            ypos += (h - tmp1) / 2;
            h = tmp1;
        }
    }

    rect.setX(xpos);
    rect.setY(ypos);
    rect.setWidth(int(w));
    rect.setHeight(int(h));
    m_drawView->setGeometry(rect);

    QMainWindow::resizeEvent(size);
}

void MainWindow::resizeDrawView()
{
    m_drawView->drawAnimationResize(m_pageView, m_propertyView);
}

void MainWindow::repaint()
{
    qDebug() << "repainted!";
}

MainWindow::~MainWindow()
{
    if (m_statusBar) delete m_statusBar;
    if (m_leftPanel) delete m_leftPanel;
    if (m_toolBar) delete m_toolBar;
    if (m_pageView) delete m_pageView;
    if (m_propertyView) delete m_propertyView;
    if (m_drawView) delete m_drawView;

    delete ui;
}
