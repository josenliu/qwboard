#ifndef DRAWSCENE_H
#define DRAWSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>
#include <QList>
#include <QPointF>
#include <QDebug>
#include "drect.h"
#include "dline.h"

class DrawScene : public QGraphicsScene
{
    Q_OBJECT
public:
    DrawScene(QObject *parent = nullptr);
    ~DrawScene();

Q_SIGNALS:
    void sceneMousePositionChanged(QPoint mousePost);

public Q_SLOTS:
    void onDrawCodeChanged(qint16 code);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    void drawShape(QGraphicsSceneMouseEvent *event);
    void drawText(QGraphicsSceneMouseEvent *event);
    void drawTable(QGraphicsSceneMouseEvent *event);

private:
    int m_drawCode;
    int m_opraCode;

    bool m_msMoveEnable;

    DrawShape *m_cuItem;
    // QList<QGraphicsItem *> m_drawItems;
};

#endif // DRAWSCENE_H
