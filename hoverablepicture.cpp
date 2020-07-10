#include "hoverablepicture.h"

#include <memory>

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>

HoverablePicture::HoverablePicture(const QString &filename, QGraphicsItem *parent):
    QGraphicsPixmapItem(filename, parent),
    m_colour(new QGraphicsEllipseItem{this})
{
    setAcceptHoverEvents(true);
    m_colour->setRect(10, 10, 10, 10);
}

HoverablePicture::HoverablePicture(const QPixmap &filename, QGraphicsItem *parent):
    QGraphicsPixmapItem(filename, parent),
    m_colour(new QGraphicsEllipseItem{this})
{
    setAcceptHoverEvents(true);
    m_colour->setRect(10, 10, 10, 10);
}

void HoverablePicture::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    m_colour->setPos(event->scenePos());
    //m_colour->setPen(pixmap().toImage().pixelColor(mapFromScene(mapToScene(event->pos())).toPoint()));
    scene()->addItem(m_colour);
}

void HoverablePicture::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    m_colour->setPos(event->scenePos());
    //m_colour->setPen(pixmap().toImage().pixelColor(mapFromScene(mapToScene(event->pos())).toPoint()));
    scene()->addItem(m_colour);
}
