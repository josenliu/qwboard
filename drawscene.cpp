#include "consdefine.h"
#include "drawscene.h"

DrawScene::DrawScene(QObject *parent) :
    QGraphicsScene (parent)
{
    m_opraCode = opCode::OP_CODE_SHAPE;
    m_drawCode = drawMode::DRAW_CODE_LINE;
    m_msMoveEnable = false;
}

void DrawScene::onDrawCodeChanged(qint16 mode)
{
    m_opraCode = mode&opCode::OP_CODE_MASK;
    m_drawCode = mode&0x00ff;
}

void DrawScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_opraCode == opCode::OP_CODE_SHAPE) {
        drawShape(event);
        return;
    }

    if (m_opraCode == opCode::OP_CODE_TEXT) {
        drawText(event);
        return;
    }

    if (m_opraCode == opCode::OP_CODE_TABLE) {
        drawTable(event);
        return;
    }

    QGraphicsScene::mousePressEvent(event);
}

void DrawScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qreal x = event->scenePos().x();
    qreal y = event->scenePos().y();

    QPoint sp = QPoint(int(x), int(y));
    emit sceneMousePositionChanged(sp);

    if (m_opraCode == opCode::OP_CODE_SHAPE) {
         if (m_cuItem && m_msMoveEnable) m_cuItem->drawing(event);
         return;
    }

    QGraphicsScene::mouseMoveEvent(event);
}

void DrawScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_cuItem && m_msMoveEnable) {
        m_cuItem = nullptr;
        m_msMoveEnable = false;
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

void DrawScene::drawShape(QGraphicsSceneMouseEvent *event)
{
    if (m_drawCode == drawMode::DRAW_CODE_CIRCLE) {
    }

    if (m_drawCode == drawMode::DRAW_CODE_RECT) {
        DRect *drect = new DRect();
        m_cuItem = drect;
        addItem(drect);
    }

    if (m_drawCode == drawMode::DRAW_CODE_LINE) {
        DLine *dline = new DLine();
        m_cuItem = dline;
        addItem(dline);
    }

    if (m_cuItem)
    {
        m_cuItem->drawStart(event);
        m_msMoveEnable = true;
    }
}

void DrawScene::drawText(QGraphicsSceneMouseEvent *event)
{

}

void DrawScene::drawTable(QGraphicsSceneMouseEvent *event)
{

}

DrawScene::~DrawScene()
{

}
