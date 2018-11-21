#include "graphichex.hh"



GraphicHex::GraphicHex(int size, std::string type, QPointF pixelPoints) :
    size_(size),
    type_(type),
    pixelPoints_(pixelPoints)
{
    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable);

    pressed_ = false;

}



void GraphicHex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QPolygonF hex_points = hex_po;
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

    QPen pen(Qt::black, 0);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color(type_));
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawPolygon(hex_points);
    setPos(pixelPoints_);
    //painter->drawPath(path);


}




QRectF GraphicHex::boundingRect() const
{
    return QRectF(-50, -50, 100, 100);
}

QColor GraphicHex::color(std::string pieceType)
{
    std::unordered_map<std::string, QColor> colorMap = {{"Peak", Qt::black},
                                                        {"Mountain", Qt::gray},
                                                        {"Forest", Qt::green},
                                                        {"Beach", Qt::yellow},
                                                        {"Water", QColor(0, 119, 190)},
                                                        {"Coral", Qt::darkMagenta}};

    for (auto &type : colorMap)
    {
        if (type.first == pieceType)
        {
            return type.second;
        }
    }

    return Qt::cyan;

}

void GraphicHex::paintOnClick(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF polygon = boundingRect();
    QBrush brush(Qt::blue);

    if(pressed_)
    {
        brush.setColor(Qt::red);
    }
    else
    {
        brush.setColor(Qt::green);
    }
    painter->fillRect(polygon,brush);
    painter->drawRect(polygon);
}

void GraphicHex::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed_ = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void GraphicHex::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed_ = false;
    update();
    QGraphicsItem::mousePressEvent(event);
}







