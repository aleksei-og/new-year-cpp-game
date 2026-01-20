#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

class CustomScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CustomScene(QObject *parent = 0);
    ~CustomScene();

signals:
    /// Сигнал для передачи координат положения курсора мыши
    void signalTargetCoordinate(QPointF point);
    void signalShot(bool shot); /// Сигнал на стрельбу

public slots:

private:
    /// Функция, в которой производится отслеживание положения мыши
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CUSTOMSCENE_H
