#ifndef DRAWSHAPE_H
#define DRAWSHAPE_H

#include <QObject>
#include <QGraphicsSceneMouseEvent>

class DrawShape: public QObject
{
    Q_OBJECT
public:
    explicit DrawShape(QObject *parent = nullptr);
    virtual ~DrawShape();

public:
    virtual void drawStart(QGraphicsSceneMouseEvent * event) = 0;
    virtual void drawing(QGraphicsSceneMouseEvent * event) = 0;
};

#endif // DRAWSHAPE_H
