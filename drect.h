#ifndef DRECT_H
#define DRECT_H
#include <QGraphicsRectItem>
#include <QGraphicsSceneEvent>
#include <QPainter>
#include <QPointF>
#include <QDebug>

#include "drawshape.h"

class DRect: public DrawShape, public QGraphicsRectItem
{
public:
    explicit DRect(QGraphicsItem *parent = nullptr);
    ~DRect();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;
    QPainterPath path() const;
    QRectF boundingRect() const;

    void setDRect(QRectF rect);
    void setRotation(qreal angle);

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
    QList<QPointF> m_ctPointF;
    qreal m_rtAngle;

    QRectF m_cuRectF;
    QPointF m_transOrgPointF;

    qreal m_mkRadius;
    qreal m_hlLength;
    QPen m_pen;

    quint8 m_op;

    const qint8 m_cpIndex;
    const qint8 m_hlIndex;

    QLineF m_refLine;

};

#endif // DRECT_H
