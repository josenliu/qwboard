#ifndef DLINE_H
#define DLINE_H
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsSceneEvent>
#include <QPainter>
#include <QPointF>
#include <QDebug>

#include "drawshape.h"

class DLine: public DrawShape, public QGraphicsLineItem
{
    Q_OBJECT
public:
    explicit DLine(QGraphicsItem *parent = nullptr);
    ~DLine();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;

protected:
    void drawStart(QGraphicsSceneMouseEvent * event);
    void drawing(QGraphicsSceneMouseEvent * event);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);

private:
    void updateGeometryData();

private:
    QPointF m_stPointF;
    QPointF m_ltPointF;
    QPointF m_hlPointF;
    QPointF m_ctPointF;
    const int m_hlLength;
    const int m_mkRadius;

    QPen m_pen;
    bool m_bBegin;

    quint8 m_op;
};

#endif // DLINE_H
