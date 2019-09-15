#include "consdefine.h"
#include "drect.h"
#include <QCursor>

DRect::DRect(QGraphicsItem *parent) :
    DrawShape ((QObject *)parent),
    QGraphicsRectItem (parent),
    m_rtAngle(0),
    m_mkRadius(4),
    m_hlLength(20),
    m_cpIndex(4),
    m_hlIndex(5)
{
    setFlags(QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
}

void DRect::setDRect(QRectF rect)
{
    QGraphicsRectItem::setRect(rect);

    m_rtAngle = 0;
    m_cuRectF = rect;
    updateGeometryData();
    m_transOrgPointF = m_ctPointF.at(m_cpIndex);
}

void DRect::drawStart(QGraphicsSceneMouseEvent *event)
{
    QPointF cp = event->scenePos();
    QRectF r = QRectF(QPointF(0, 0), QSizeF(0, 0));
    setRect(r);
    m_cuRectF = rect();

    qreal x = 0; // cp.x();
    qreal y = 0; // cp.y();
    QTransform trans;
    trans.translate(cp.x(), cp.y()).translate(x, y); //.translate(-cp.x(), -cp.y());
    setTransform(trans);
}

void DRect::drawing(QGraphicsSceneMouseEvent *event)
{
    QRectF r = rect();
    qreal x = event->scenePos().x() - mapToScene(m_cuRectF.topLeft()).x();
    qreal y = event->scenePos().y() - mapToScene(m_cuRectF.topLeft()).y();
    qreal w = x - m_cuRectF.x();
    qreal h = y - m_cuRectF.y();

    if (w < 0) {
        r.setX(x);
        w = -w;
    }

    if (h < 0) {
        r.setY(y);
        h = -h;
    }

    r.setWidth(w);
    r.setHeight(h);
    setRect(r);

    updateGeometryData();
}

void DRect::updateGeometryData()
{
    qreal x = rect().x();
    qreal y = rect().y();
    qreal w = rect().width();
    qreal h = rect().height();
    m_ctPointF.clear();

    m_ctPointF.append(QPointF(x, y+h/2));
    m_ctPointF.append(QPointF(x+w, y+h/2));
    m_ctPointF.append(QPointF(x+w/2, y));
    m_ctPointF.append(QPointF(x+w/2, y+h));
    m_ctPointF.append(rect().center());
    m_ctPointF.append(QPointF(x+w/2, y+h/2-m_hlLength));
}

void DRect::setRotation(qreal angle)
{
    QPointF cp = m_ctPointF.at(m_cpIndex);

    QTransform trans = transform();
    trans.translate(cp.x(), cp.y()).rotate(angle).translate(-cp.x(), -cp.y());
    setTransform(trans);

    m_rtAngle += angle;
    if (m_rtAngle >= 360) m_rtAngle -= 360;
}

void DRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->setPen(pen());
    painter->setBrush(QBrush(Qt::cyan));
    painter->drawRect(rect());
    painter->restore();

    if (isSelected()) {
        painter->save();
        painter->setPen(QPen(Qt::blue));
        painter->setBrush(QBrush(Qt::blue));
        for (int i = 0; i < m_ctPointF.count(); i++)
        {
            painter->drawEllipse(m_ctPointF.at(i), m_mkRadius, m_mkRadius);
        }

        QPointF cp = m_ctPointF.at(m_cpIndex);
        painter->drawLine(QPointF(cp.x()-m_mkRadius*1.5, cp.y()), QPointF(cp.x()+m_mkRadius*1.5, cp.y()));
        painter->drawLine(QPointF(cp.x(), cp.y()-m_mkRadius*1.5), QPointF(cp.x(), cp.y()+m_mkRadius*1.5));

        QLineF cLineF = QLineF(m_ctPointF.at(m_cpIndex), m_ctPointF.at(m_hlIndex));
        painter->drawLine(cLineF);
        painter->restore();
    }
}

QPainterPath DRect::shape() const
{
    qreal w = 8 * 1.5;

    QPainterPath path = QGraphicsRectItem::shape();
    QVector<QPointF> points;
    QPointF cPointF, ctPointF,hlPointF;

    if (m_ctPointF.size() < m_cpIndex) return path;

    ctPointF = m_ctPointF.at(m_cpIndex);
    hlPointF = m_ctPointF.at(m_hlIndex);

    cPointF = QPointF(ctPointF.x(), ctPointF.y() - w/2);
    points.append(cPointF);

    cPointF = QPointF(ctPointF.x() - w/2, ctPointF.y() + w/2);
    points.append(cPointF);

    cPointF = QPointF(hlPointF.x() - w/2, hlPointF.y() - w/2);
    points.append(cPointF);

    cPointF = QPointF(hlPointF.x() + w/2, hlPointF.y() - w/2);
    points.append(cPointF);

    cPointF = QPointF(ctPointF.x() + w/2, cPointF.y() + w / 2);
    points.append(cPointF);

    cPointF = QPointF(ctPointF.x(), cPointF.y() + w/2);
    points.append(cPointF);

    QPolygonF polyF = QPolygonF(points);
    path.addPolygon(polyF);

    QPainterPathStroker stroker;
    stroker.setWidth(w);
    path = stroker.createStroke(path);

    return path;
}

QRectF DRect::boundingRect() const
{

    QRectF bdRectF = QGraphicsRectItem::boundingRect();

    qreal x = bdRectF.x() - m_mkRadius/2 - 1;
    qreal y = bdRectF.y() - m_mkRadius/2 - 1;
    qreal w = bdRectF.width() + m_mkRadius + 2;
    qreal h = bdRectF.height() + m_mkRadius + 2;
    bdRectF = QRectF(x, y, w, h);

    return bdRectF;
}

void DRect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!isSelected()) return;

    if (m_op == drawOpraMode::DRAW_OPRA_RESIZE || m_op == drawOpraMode::DRAW_OPRA_RRESIZE ||
            m_op == drawOpraMode::DRAW_OPRA_URESIZE || m_op == drawOpraMode::DRAW_OPRA_DRESIZE ||
            m_op == drawOpraMode::DRAW_OPRA_ROTATE || m_op == drawOpraMode::DRAW_OPRA_MOVE) {
        m_cuRectF = rect();
    }

    QGraphicsItem::mousePressEvent(event);
}

void DRect::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (!isSelected()) return;

    QPointF cp = event->pos();
    QRectF cRectF = m_cuRectF;

    if (m_op == drawOpraMode::DRAW_OPRA_RESIZE) {
        cRectF.setLeft(cp.x());
    } else if (m_op == drawOpraMode::DRAW_OPRA_RRESIZE) {
        cRectF.setRight(cp.x());
    } else if (m_op == drawOpraMode::DRAW_OPRA_URESIZE) {
        cRectF.setTop(cp.y());
    } else if (m_op == drawOpraMode::DRAW_OPRA_DRESIZE) {
        cRectF.setBottom(cp.y());
    } else if (m_op == drawOpraMode::DRAW_OPRA_MOVE) {
        qreal w, h;
        w = cRectF.width();
        h = cRectF.height();
        qreal x = cp.x() - w/2;
        qreal y = cp.y() - h/2;

        cRectF.setTopLeft(QPointF(x, y));
        cRectF.setWidth(w);
        cRectF.setHeight(h);

        QTransform trans = transform();
        trans.translate(cp.x(), cp.y()).translate(x, y).translate(-cp.x(), -cp.y());
        setTransform(trans);

    } else if (m_op == drawOpraMode::DRAW_OPRA_ROTATE) {
        // cp = event->scenePos();
        QLineF vLineF = QLineF(m_ctPointF.at(m_cpIndex), cp);
        vLineF.setLength(m_hlLength);
        qreal angle = vLineF.angleTo(m_refLine);

        qreal r = m_rtAngle + angle;
        qDebug() << "rt: " << r;

        if (r > 87 && r < 93) {
            r = 90;
        }
        else if (r > 357 || r < 3) {
            r = 0;
        }
        else if (r > 177 && r < 183) {
            r = 180;
        }
        else if (r > 267 && r < 273) {
            r = 270;
        }
        else if (r > 42 && r < 48) {
            r = 45;
        }
        else if (r > 132 && r < 138) {
            r = 135;
        }
        else if (r > 222 && r < 228) {
            r = 225;
        }
        else if (r > 312 && r < 318) {
            r = 315;
        }

        if (r >= m_rtAngle) angle = r - m_rtAngle;
        // else angle = 360 + (r - m_rtAngle);

        qDebug() << "ANGLE: " << angle << "r: " << r;
        setRotation(angle);
    }

    cRectF = cRectF.normalized();
    setRect(cRectF);
    updateGeometryData();

    event->accept();
}

void DRect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF cp = (m_ctPointF.at(m_cpIndex));
    QPointF hp = (m_ctPointF.at(m_hlIndex));

    m_refLine.setP1(cp);
    m_refLine.setP2(hp);

    m_cuRectF = rect();

    QGraphicsItem::mouseReleaseEvent(event);
}

void DRect::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QPen hPen;
    hPen.setColor(Qt::green);
    hPen.setWidth(2);

    m_pen = pen();
    setPen(hPen);

    m_cuRectF = rect();
    update(boundingRect());
}

void DRect::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if (!isSelected()) return;

    QList<QRectF> cRectF;

    QPointF cPointF = event->pos();    // scenePos will not work after rectangle rotated.

    int i = 0;
    for (i = 0; i < m_ctPointF.count(); i++) {
        QPointF tPointF;
        tPointF.setX(m_ctPointF.at(i).x() - m_mkRadius);
        tPointF.setY(m_ctPointF.at(i).y() - m_mkRadius);

        QRectF xRectF = QRectF(tPointF, QSizeF(m_mkRadius*2, m_mkRadius*2));

        if (xRectF.contains(cPointF)) break;
    }

    if (i == 0) {
        m_op = drawOpraMode::DRAW_OPRA_RESIZE;      // left resize
        setCursor(Qt::SizeHorCursor);
    }
    else if (i == 1) {
        m_op = drawOpraMode::DRAW_OPRA_RRESIZE;      // right resize
        setCursor(Qt::SizeHorCursor);
    } else if (i == 2) {
        m_op = drawOpraMode::DRAW_OPRA_URESIZE;      // up resize
        setCursor(Qt::SizeVerCursor);
    } else if (i == 3) {
        m_op = drawOpraMode::DRAW_OPRA_DRESIZE;      // down resize
        setCursor(Qt::SizeVerCursor);
    } else if (i == 4) {
        m_op = drawOpraMode::DRAW_OPRA_MOVE;        // move
        setCursor(Qt::OpenHandCursor);
    } else if (i == 5) {
        m_op = drawOpraMode::DRAW_OPRA_ROTATE;
        setCursor(Qt::SizeAllCursor);
    }
    else {
        setCursor(Qt::ArrowCursor);
        m_op = drawOpraMode::DRAW_OPRA_NONE;
    }

    QGraphicsItem::hoverEnterEvent(event);
}

void DRect::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setPen(m_pen);
    setCursor(Qt::ArrowCursor);
}

DRect::~DRect()
{

}
