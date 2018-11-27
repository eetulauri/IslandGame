#include "graphichex.hh"



GraphicHex::GraphicHex(int size, std::string type, QPointF pixelPoint,
                       std::shared_ptr<Common::Hex> hex, Common::CubeCoordinate coord) :
    size_(size),
    type_(type),
    pixelPoint_(pixelPoint),
    hex_(hex),
    coord_(coord)

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
    hexPoints_ = hex_points;

    //QPainterPath path;
    //path.addPolygon(hex_points);

    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color(type_));
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawPolygon(hex_points);
    setPos(pixelPoint_);
    drawActor(painter);
    drawTransport(painter);
    drawPawn(painter);
    //painter->drawPath(path);


}

void GraphicHex::drawPawn(QPainter *painter)
{
    std::vector<std::shared_ptr<Common::Pawn> > pawns = hex_->getPawns();

    if (pawns.size() != 0) {

        std::shared_ptr<Common::Pawn> pawn = pawns.at(0);
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::white);
        painter->setPen(pen);
        painter->setBrush(brush);
        double x = coord_.x;
        double y = coord_.y;

        std::shared_ptr<QRectF> pawnGraphical = std::make_shared<QRectF>();
        pawnGraphical->setCoords(x, y, x ,y);
        pawnGraphical->setWidth(20);
        pawnGraphical->setHeight(20);
        painter->drawRect(*pawnGraphical);
        QString str = "1";
        std::shared_ptr<QGraphicsSimpleTextItem> number = std::make_shared<QGraphicsSimpleTextItem>();
        //number->setParentItem(*pawnGraphical);
        number->setText(str);


    }



}

void GraphicHex::drawTransport(QPainter *painter)
{
    std::vector<std::shared_ptr<Common::Transport> > transports = hex_->getTransports();

    if (transports.size() != 0) {

        std::shared_ptr<Common::Transport> transport = transports.at(0);
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::darkRed);
        painter->setPen(pen);
        painter->setBrush(brush);
        double x = coord_.x;
        double y = coord_.y;

        std::shared_ptr<QRectF> transportGraphical = std::make_shared<QRectF>();
        transportGraphical->setCoords(x, y, x ,y);
        transportGraphical->setWidth(20);
        transportGraphical->setHeight(20);
        painter->drawRect(*transportGraphical);
        QString str = "1";
        std::shared_ptr<QGraphicsSimpleTextItem> number = std::make_shared<QGraphicsSimpleTextItem>();
        //number->setParentItem(*pawnGraphical);
        number->setText(str);


    }
}

void GraphicHex::drawActor(QPainter *painter)
{

    std::vector<std::shared_ptr<Common::Actor> > actors = hex_->getActors();

    if (actors.size() != 0) {

        std::shared_ptr<Common::Actor> actor = actors.at(0);
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::darkGreen);
        painter->setPen(pen);
        painter->setBrush(brush);
        double x = coord_.x;
        double y = coord_.y;

        std::shared_ptr<QRectF> actorGraphical = std::make_shared<QRectF>();
        actorGraphical->setCoords(x, y, x ,y);
        actorGraphical->setWidth(20);
        actorGraphical->setHeight(20);
        painter->drawRect(*actorGraphical);
        QString str = "1";
        std::shared_ptr<QGraphicsSimpleTextItem> number = std::make_shared<QGraphicsSimpleTextItem>();
        //number->setParentItem(*pawnGraphical);
        number->setText(str);


    }
}



QRectF GraphicHex::boundingRect() const
{
    return QRectF(-28, -28, 56, 56);
}

QPainterPath GraphicHex::shape() const
{
    QPainterPath path;
    path.addPolygon(hexPoints_);
    return path;
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

void GraphicHex::resetClicked()
{
    clicked_ = false;
}

Common::CubeCoordinate GraphicHex::getCoordinates()
{
    return coord_;
}

std::shared_ptr<Common::Hex> GraphicHex::getHex()
{
    return hex_;
}

void GraphicHex::changeType(std::string type)
{
    type_ = type;
}

void GraphicHex::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPen pen(Qt::red);
    QBrush brush(Qt::red);
    if (clicked_ == true) {
        clicked_ = false;
    } else {
        clicked_ = true;
    }
    emit hexOnClick(hex_);


    update();
    QGraphicsItem::mousePressEvent(event);


}

void GraphicHex::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    update();
    QGraphicsItem::mousePressEvent(event);
}







