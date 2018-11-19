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


class GraphicHex : public QGraphicsPolygonItem
{
public:
    GraphicHex(int size, std::string type);

    /*
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    */
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    QRectF boundingRect() const;

    QColor color(std::string pieceType);



private:


    int size_;
    std::string type_;
};

#endif // GRAPHICHEX_HH
