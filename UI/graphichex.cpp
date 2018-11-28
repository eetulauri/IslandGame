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
        std::string transportType = transport->getTransportType();

        QImage image;
        image.load(getImagePath(transportType));
        QRectF imageArea;
        double imageX = -size_*(3.0/5.0);
        double imageY = -size_*(3.0/5.0);
        imageArea.setRect(imageX, imageY, (6.0/5.0) * size_, (6.0 /5.0) * size_);
        painter->drawImage(imageArea, image);

    }
}

void GraphicHex::drawActor(QPainter *painter)
{

    std::vector<std::shared_ptr<Common::Actor> > actors = hex_->getActors();

    if (actors.size() != 0) {

        std::shared_ptr<Common::Actor> actor = actors.at(0);
        std::string actorType = actor->getActorType();

        QImage image;
        image.load(getImagePath(actorType));
        QRectF imageArea;
        double imageX = -size_*(3.0/5.0);
        double imageY = -size_*(3.0/5.0);
        imageArea.setRect(imageX, imageY, (6.0/5.0) * size_, (6.0 /5.0) * size_);
        painter->drawImage(imageArea, image);

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

QString GraphicHex::getImagePath(std::string name)
{
    std::unordered_map<std::string, std::string> imageMap = {{"boat", ":/images/boat.png"},
                                                        {"dolphin", ":/images/dolphin.png"},
                                                        {"shark", ":/images/shark.png"},
                                                        {"kraken", ":/images/kraken.png"},
                                                        {"seamunster", ":/images/seamunster.png"},
                                                        {"vortex", ":/images/vortex.png"}};


    for (auto &type : imageMap)
    {
        if (type.first == name)
        {
            return QString::fromStdString(type.second);
        }
    }
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







