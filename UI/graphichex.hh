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
#include <QString>
#include <string>
#include <memory>
#include <QLabel>
#include <QPixmap>

const double PI = 3.14159265;

class GraphicHex : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    GraphicHex(int size, std::string type, QPointF pixelPoint,
               std::shared_ptr<Common::Hex> hex, Common::CubeCoordinate coord);


    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void drawPawn(QPainter *painter);
    void drawTransport(QPainter *painter);
    void drawActor(QPainter *painter);

    QRectF boundingRect() const;

    QPainterPath shape() const;

    QColor color(std::string pieceType);

    void resetClicked();
    Common::CubeCoordinate getCoordinates();
    std::shared_ptr<Common::Hex> getHex();
    void changeType(std::string type);

signals:
    void hexOnClick(std::shared_ptr<Common::Hex> hex);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);


private:


    int size_;
    std::string type_;
    QPointF pixelPoint_;
    QPolygonF hexPoints_;
    std::shared_ptr<Common::Hex> hex_;
    Common::CubeCoordinate coord_;


    bool clicked_;
    QPen pen;
    QBrush brush;

};

#endif // GRAPHICHEX_HH
