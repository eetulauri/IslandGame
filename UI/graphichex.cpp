#include "graphichex.hh"



GraphicHex::GraphicHex(int size, std::string type) :
    size_(size),
    type_(type)
{
    setFlag(ItemIsMovable);

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

    QPen pen(Qt::black, 2);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color(type_));
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawPolygon(hex_points);


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
                                                        {"Water", QColor(38, 82, 202)},
                                                        {"Coral", Qt::darkMagenta}};
    QColor color;
    for (auto &type : colorMap)
    {
        if (type.first == pieceType)
        {
            return type.second;
        }
    }

    return Qt::cyan;

}







