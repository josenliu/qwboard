#include "consdefine.h"
#include "dline.h"
#include <QCursor>

DLine::DLine(QGraphicsItem *parent) :
    DrawShape ((QObject *)parent),
    QGraphicsLineItem (parent),
    m_hlLength(20),
    m_mkRadius(4),
    m_op(drawOpraMode::DRAW_OPRA_NONE)
{
    setFlags(QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
}

void DLine::drawStart(QGraphicsSceneMouseEvent *event)
{
    setLine(QLineF(event->scenePos(), event->scenePos()));
}

void DLine::drawing(QGraphicsSceneMouseEvent *event)
{
    QLineF newLine(line().p1(), event->scenePos());
    setLine(newLine);

    updateGeometryData();
}

void DLine::updateGeometryData()
{
    qreal x = line().p1().x() + (line().p2().x() - line().p1().x()) / 2;
    qreal y = line().p1().y() + (line().p2().y() - line().p1().y()) / 2;

    m_ctPointF.setX(x);
    m_ctPointF.setY(y);

    QLineF cLineF = QLineF(m_ctPointF, line().p1()).normalVector();
    cLineF.setLength(m_hlLength);
    m_hlPointF.setX(cLineF.p2().x());
    m_hlPointF.setY(cLineF.p2().y());
}

QPainterPath DLine::shape() const
{
    qreal w = 8 * 8.5;

    QPainterPath path = QGraphicsLineItem::shape();
    QPainterPathStroker stroker;
    stroker.setWidth(w);

    path = stroker.createStroke(path);

    return path;
}

void DLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QLineF linef = line();

    painter->setPen(pen());
    painter->drawLine(linef);
    // painter->drawRect(boundingRect());
    // painter->drawPath(shape());

    if (isSelected()) {
        painter->save();
        painter->setPen(QPen(Qt::blue));
        painter->setBrush(QBrush(Qt::blue));
        painter->drawEllipse(linef.p1(), m_mkRadius, m_mkRadius);
        painter->drawEllipse(linef.p2(), m_mkRadius, m_mkRadius);
        painter->drawEllipse(m_ctPointF, m_mkRadius, m_mkRadius);
        painter->drawLine(m_ctPointF, m_hlPointF);
        painter->drawEllipse(m_hlPointF, m_mkRadius, m_mkRadius);
        painter->restore();
    }
}

void DLine::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (isSelected()) {
        if (m_op == drawOpraMode::DRAW_OPRA_MOVE) {
            m_stPointF = event->scenePos();
            m_ltPointF = event->scenePos();
        }
        else if (m_op == drawOpraMode::DRAW_OPRA_RESIZE)
        {
            m_stPointF = line().p2();
            m_ltPointF = event->pos();
            if (!m_bBegin) {
                m_stPointF = line().p1();
                m_ltPointF = event->pos();
            }

            setLine(QLineF(m_stPointF, m_ltPointF));
            updateGeometryData();
        }
        else if (m_op == drawOpraMode::DRAW_OPRA_ROTATE) {
            QLineF cLineF = QLineF(m_ctPointF, event->pos());
            cLineF.setLength(m_hlLength);
            m_hlPointF = cLineF.p2();
        }
    }

    QGraphicsItem::mousePressEvent(event);
    event->accept();
}

void DLine::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (!isSelected()) return;

    if (m_op == drawOpraMode::DRAW_OPRA_MOVE) {
        m_ltPointF = event->scenePos();
        QGraphicsItem::mouseMoveEvent(event);
    }
    else if (m_op == drawOpraMode::DRAW_OPRA_RESIZE) {
        m_ltPointF = event->pos();
        setLine(QLineF(m_stPointF, m_ltPointF));
        updateGeometryData();

        qDebug() << "line resize";
    }
    else if (m_op == drawOpraMode::DRAW_OPRA_ROTATE) {
        QLineF cLineF = QLineF(m_ctPointF, event->pos());
        cLineF.setLength(m_hlLength);
        QLineF tLineF = cLineF.normalVector();
        qreal len = line().length();
        tLineF.setLength(len/2);
        m_stPointF = tLineF.p2();
        m_ltPointF = tLineF.p1();
        tLineF = QLineF(m_stPointF, m_ltPointF);
        tLineF.setLength(len);
        setLine(tLineF);
        m_hlPointF = cLineF.p2();
    }
}

void DLine::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (!isSelected()) return;
    if (m_op == drawOpraMode::DRAW_OPRA_MOVE) {
    }

    QGraphicsItem::mouseReleaseEvent(event);
}

void DLine::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QPen hPen;
    hPen.setColor(Qt::green);
    hPen.setWidth(2);

    m_pen = pen();

    setPen(hPen);
    update(boundingRect());
}

void DLine::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if (!isSelected()) return;

    QPointF cPointF = event->pos();
    cPointF = mapToItem(this, cPointF);

    QPointF tPointF;
    tPointF.setX(m_ctPointF.x() - m_mkRadius);
    tPointF.setY(m_ctPointF.y() - m_mkRadius);

    QRectF rect1 = QRectF(tPointF, QSize(m_mkRadius*2, m_mkRadius*2));

    tPointF.setX(line().p1().x() - m_mkRadius);
    tPointF.setY(line().p1().y() - m_mkRadius);
    QRectF rect2 = QRectF(tPointF, QSize(m_mkRadius*2, m_mkRadius*2));

    tPointF.setX(line().p2().x() - m_mkRadius);
    tPointF.setY(line().p2().y() - m_mkRadius);
    QRectF rect3 = QRectF(tPointF, QSize(m_mkRadius*2, m_mkRadius*2));

    tPointF.setX(m_hlPointF.x() - m_mkRadius);
    tPointF.setY(m_hlPointF.y() - m_mkRadius);
    QRectF rect4 = QRectF(tPointF, QSize(m_mkRadius*2, m_mkRadius*2));

    if (rect1.contains(cPointF)) {
        setCursor(Qt::OpenHandCursor);
        m_op = drawOpraMode::DRAW_OPRA_MOVE;
        qDebug() << "move";
    }
    else if (rect2.contains(cPointF)) {
        setCursor(Qt::CrossCursor);
        m_op = drawOpraMode::DRAW_OPRA_RESIZE;
        m_bBegin = true;
        qDebug() << "scale1";
    }
    else if (rect3.contains(cPointF)) {
        setCursor(Qt::CrossCursor);
        m_op = drawOpraMode::DRAW_OPRA_RESIZE;
        m_bBegin = false;
        qDebug() << "scale2";
    }
    else if (rect4.contains(cPointF)) {
        setCursor((Qt::SizeAllCursor));
        m_op = drawOpraMode::DRAW_OPRA_ROTATE;
        qDebug("rotation");
    }
    else {
        setCursor(Qt::ArrowCursor);
        m_op = drawOpraMode::DRAW_OPRA_NONE;
    }

    QGraphicsItem::hoverEnterEvent(event);
}

void DLine::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setPen(m_pen);
    setCursor(Qt::ArrowCursor);
}

DLine::~DLine()
{

}
