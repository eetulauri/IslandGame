#include "graphichex.hh"



GraphicHex::GraphicHex()
{
    setFlag(ItemIsMovable);
}

void GraphicHex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon hex_points;

    double angle_deg;
    double angle_rad;
    int size = 50;

    for (int i = 0; i < 6; i++)
    {
        angle_deg = 60 * i - 30;
        angle_rad = PI / 180 * angle_deg;
        hex_points << QPoint(size * cos(angle_rad),
                             size * sin(angle_rad));
    }

    QPen pen(Qt::black, 1);

    painter->setPen(pen);
    painter->drawPolygon(hex_points);


}

QRectF GraphicHex::boundingRect() const
{
    return QRectF(-50, -50, 100, 100);
}





