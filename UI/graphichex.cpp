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

    QPen pen(Qt::black, 1.1);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::blue);
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
    std::map<std::string, QColor> colorMap = {{"Peak", Qt::black},
                                              {"Mountain", Qt::gray},
                                              {"Forest", Qt::green},
                                               {"Beach", Qt::yellow},
                                               {"Water", Qt::darkBlue},
                                               {"Coral", Qt::darkMagenta}};


}







