#ifndef GRAPHICHEX_HH
#define GRAPHICHEX_HH

#include <hex.hh>
#include <math.h>
#include <QGraphicsItem>
#include <QPainterPath>
#include <QPoint>
#include <QPolygon>
#include <QPen>
#include <QPainter>

#define PI 3.14159265


class GraphicHex : public QGraphicsItem
{
public:
    GraphicHex();

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QRectF boundingRect() const;

private:


};

#endif // GRAPHICHEX_HH