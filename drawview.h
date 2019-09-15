#ifndef DRAWVIEW_H
#define DRAWVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPropertyAnimation>
#include <QDebug>
#include "pageview.h"
#include "propertyview.h"
#include "leftpanel.h"

#include "dline.h"
#include "drawscene.h"

namespace Ui {
class DrawView;
}

class DrawView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit DrawView(QWidget *parent = nullptr);
    ~DrawView();

protected:
#ifdef DRAW_VIEW_EVENT
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
#endif
    void mouseMoveEvent(QMouseEvent *event);

Q_SIGNALS:
    void drawCodeChanged(qint16);
    void mousePositionChanged(QPoint);


public Q_SLOTS:
    void drawAnimationResize(PageView *page, PropertyView *option);
    void onZoomChanged(int value);

public:
    int m_drawStyle;

private:
    Ui::DrawView *ui;

    DrawScene *m_scene;
    qreal m_sceneScale;

    // QList<QGraphicsItem *> m_drawItems;
};

#endif // DRAWVIEW_H
