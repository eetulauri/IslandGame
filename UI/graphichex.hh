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
    GraphicHex(int size, std::string type, QPointF pixelPoint);


    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    QRectF boundingRect() const;

    QColor color(std::string pieceType);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);


private:


    int size_;
    std::string type_;
    QPointF pixelPoint_;
<<<<<<< HEAD
=======
    bool clicked_;
    QPen pen;
    QBrush brush;
>>>>>>> master
};

#endif // GRAPHICHEX_HH
