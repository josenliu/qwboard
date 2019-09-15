#include "consdefine.h"
#include "drawview.h"
#include "ui_drawview.h"
#include <QtOpenGL>

DrawView::DrawView(QWidget *parent) :
    QGraphicsView(parent),
    ui(new Ui::DrawView)
{
    ui->setupUi(this);

    setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    setRenderHint(QPainter::Antialiasing, true);
    // setDragMode(QGraphicsView::RubberBandDrag);
    setOptimizationFlags(QGraphicsView::DontSavePainterState);

#ifdef DO_NOT_OPENGL
    QOpenGLWidget *myGLWidget = new QOpenGLWidget();
    myGLWidget->setAutoFillBackground(false);
    myGLWidget->makeCurrent();
    setViewport(myGLWidget);
#endif

    m_scene = new DrawScene(this);
    m_scene->setSceneRect(QRectF(0, 0, DRAW_BOARD_WIDTH, DRAW_BOARD_HEIGHT));

    int w, h;

    w = int(m_scene->sceneRect().width());
    h = int(m_scene->sceneRect().height());

    //m_scene->addLine(QLineF(0, 0, w, 0));
    //m_scene->addLine(0, 0, 0, h);
    // m_scene->addRect(QRectF(150, 100, 200, 100));

    setScene(m_scene);

    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    m_drawStyle = QWBAORD_PAGE_SIZE_169;
    m_sceneScale = 1.0;

    connect(this, SIGNAL(drawCodeChanged(qint16)), m_scene, SLOT(onDrawCodeChanged(qint16)));
    connect(m_scene, SIGNAL(sceneMousePositionChanged(QPoint)), this, SIGNAL(mousePositionChanged(QPoint)));
}

void DrawView::drawAnimationResize(PageView *page, PropertyView *option)
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    QRect rect = geometry();

    animation->setStartValue(rect);

    double w, h, tmp1, tmp2;
    int pageWidth;
    int optionWidth;

    pageWidth = 0;
    optionWidth = 0;
    if (page->m_pageVisible) pageWidth = page->m_pageWidth;
    if (option->m_optionVisible) optionWidth = option->m_optionWidth;

    w =  parentWidget()->width() - pageWidth - optionWidth - LEFT_PANEL_WIDTH - 1;
    h =  parentWidget()->height() - TOOL_BAR_HEIGHT - STATUS_BAR_HEIGHT;
    int xpos = page->x() + pageWidth;
    int ypos = TOOL_BAR_STARTY + STATUS_BAR_HEIGHT; // rect.y();

    if (m_drawStyle == QWBAORD_PAGE_SIZE_169) {
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

    animation->setEndValue(rect);
    animation->setDuration(100);
    animation->start();
}

#ifdef DRAW_VIEW_EVENT
void DrawView::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "drawView pressed!";

    // QGraphicsSceneMoveEvent *smEvent = new QGraphicsSceneMoveEvent();
}

void DrawView::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "drawView Released!";
}
#endif

void DrawView::mouseMoveEvent(QMouseEvent *event)
{
    // emit mousePositionChanged(event->pos());
    QGraphicsView::mouseMoveEvent(event);
}

void DrawView::onZoomChanged(int value)
{
    QTransform transfscale = QTransform(value/100.0, 0, 0, 0, value/100.0, 0, 0, 0, 1.0);
    setTransform(transfscale);
}

DrawView::~DrawView()
{
    delete ui;
}
