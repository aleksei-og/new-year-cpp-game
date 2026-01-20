#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QPolygon>
#include <QTimer>
#include <QDebug>
#include <QCursor>

#include <windows.h>

class Triangle : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Triangle(QObject *parent = 0);
    ~Triangle();

signals:
    /// Сигнал для создания пули с параметрами траектории
    void signalBullet(QPointF start, QPointF end);

public slots:
    /// Слот для получения данных о положении курсора
    void slotTarget(QPointF point);
    /// слот для обработки разрешения стрельбы
    void slotShot(bool shot);

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;     /// Функция, возвращающая форму фигуры, необходимо для обработки коллизий

private slots:
    void slotGameTimer();   /// Игровой слот
    void slotBulletTimer(); /// Слот проверки пули

private:
    bool shot;              /// Переменная состояния стрельбы
    QTimer *bulletTimer;    /// Таймер пули
    QTimer *gameTimer;      /// Игровой таймер
    QPointF target;         /// Положение курсора
};

#endif // TRIANGLE_H
