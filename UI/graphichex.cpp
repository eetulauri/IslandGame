#include "graphichex.hh"



GraphicHex::GraphicHex(int size, std::string type, QPointF pixelPoint) :
    size_(size),
    type_(type),
    pixelPoint_(pixelPoint)
<<<<<<< HEAD
=======

>>>>>>> master
{
    setFlag(ItemIsSelectable);

    clicked_ = false;
}



void GraphicHex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygonF hex_points;
    painter->setRenderHint(QPainter::Antialiasing);

    double angle_deg;
    double angle_rad;

    for (int i = 0; i < 6; i++)
    {
        angle_deg = 60 * i - 30;
        angle_rad = PI / 180 * angle_deg;
        hex_points << QPoint(size_ * cos(angle_rad),
                             size_ * sin(angle_rad));
    }

    //QPainterPath path;
    //path.addPolygon(hex_points);

    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color(type_));
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawPolygon(hex_points);
    setPos(pixelPoint_);
    //painter->drawPath(path);


}




QRectF GraphicHex::boundingRect() const
{
    return QRectF(-28, -28, 100, 100);
}

QColor GraphicHex::color(std::string pieceType)
{
    std::unordered_map<std::string, QColor> colorMap = {{"Peak", Qt::black},
                                                        {"Mountain", Qt::gray},
                                                        {"Forest", Qt::green},
                                                        {"Beach", Qt::yellow},
                                                        {"Water", QColor(0, 119, 190)},
                                                        {"Coral", Qt::magenta}};

    if(clicked_ == true)
    {
        return Qt::cyan;
    }
    else
    {
        for (auto &type : colorMap)
        {
            if (type.first == pieceType)
            {
                return type.second;
            }
        }

        return Qt::cyan;
    }

}

void GraphicHex::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPen pen(Qt::red);
    QBrush brush(Qt::red);
    clicked_ = true;
    update();
    QGraphicsItem::mousePressEvent(event);


}

void GraphicHex::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    clicked_ = false;
    update();
    QGraphicsItem::mousePressEvent(event);
}







