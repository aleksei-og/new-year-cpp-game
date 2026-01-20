#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QPainter>
#include <QDebug>

#include <sprite.h>

class Bullet : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Bullet(QPointF start, QPointF end, QGraphicsItem *hero, QObject *parent = 0);
    ~Bullet();
    /// Установка CallBack функции
    void setCallbackFunc(void (*func) (QGraphicsItem * item));

signals:


public slots:

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /// Объявляем CallBack функцию
    void (*callbackFunc)(QGraphicsItem * item);

private:
    QTimer *timerBullet;    /// Слот для обработки таймера пули
    /** Чтобы пуля игнорировала героя,
     * поскольку появляется в данном случае внутри самого героя
     *
     * */
    QGraphicsItem *hero;
private slots:
    void slotTimerBullet(); /// Слот для обработки полёта пули
};

#endif // BULLET_H
