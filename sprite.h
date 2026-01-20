#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

class Sprite : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Sprite(QPointF point, QObject *parent = 0);

    /// Переопределяем тип Графического объекта взрыва,
      ///чтобы пуля могла данный объект игнорировать
    enum { Type = UserType + 1 };

    /// Также переопределяем функцию для получения типа объекта
    int type() const;

signals:

public slots:

private slots:
    void nextFrame();   /// Слот для перелистывания кадров

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:
    QTimer *timer;  /// Таймер для анимации взрыва
    QPixmap *spriteImage;   /// QPixmap для спрайта со взрывом
    int currentFrame;   /// Координата текущего кадра в спрайте
};

#endif // SPRITE_H
