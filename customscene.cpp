#include "customscene.h"

CustomScene::CustomScene(QObject *parent) :
    QGraphicsScene()
{
    Q_UNUSED(parent);
}

CustomScene::~CustomScene()
{

}

void CustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalTargetCoordinate(event->scenePos());
}

void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalShot(true); /// Когда клавиша мыши нажата, то можно стрелять
    Q_UNUSED(event);
}

void CustomScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalShot(false); /// Когда клавишу мыши отпустили, то стрелять нельзя
    Q_UNUSED(event);
}
