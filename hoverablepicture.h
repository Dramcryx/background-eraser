#ifndef HOVERABLEPICTURE_H
#define HOVERABLEPICTURE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneHoverEvent>

class HoverablePicture: public QGraphicsPixmapItem
{
public:
    HoverablePicture(const QString & filename, QGraphicsItem * parent = nullptr);
    HoverablePicture(const QPixmap & filename, QGraphicsItem * parent = nullptr);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;

private:
    QGraphicsEllipseItem * m_colour;
};

#endif // HOVERABLEPICTURE_H
