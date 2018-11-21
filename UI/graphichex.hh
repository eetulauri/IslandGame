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
#include <unordered_map>
#include <QDebug>

#define PI 3.14159265


class GraphicHex : public QGraphicsItem
{
public:
    GraphicHex(int size, std::string type, QPointF pixelPoints);


    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    QRectF boundingRect() const;

    QColor color(std::string pieceType);

    void paintOnClick(QPainter *painter, const QStyleOptionGraphicsItem *option,
                      QWidget *widget);


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:

    //ehkä pitää siirtää takas privatesta ulos
    bool pressed_;
    int size_;
    std::string type_;
    QPointF pixelPoints_;
};

#endif // GRAPHICHEX_HH
