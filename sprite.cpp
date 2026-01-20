#include "sprite.h"

Sprite::Sprite(QPointF point, QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    this->setPos(point);    // Устанавливаем позицию взрыва
    currentFrame = 0;       /// Координату X начала взрыва пули
    spriteImage = new QPixmap(":/sprites/sprite_sheet.png");

    timer = new QTimer();   /// Инициализируем таймер анимации взрыва
    /// Подключаем сигнал от таймера к слоту анимации взрыва
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(25);   /// Стартуем таймер с частотой 25 милисекунд
}

QRectF Sprite::boundingRect() const
{
    return QRectF(-10,-10,20,20);
}

void Sprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Отрисовываем один из кадров взрыва
    painter->drawPixmap(-10,-10, *spriteImage, currentFrame, 0, 20,20);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Sprite::nextFrame()
{
    currentFrame += 20; // Продвигаем координату X для выбора следующего кадра
    if (currentFrame >= 300 ) {
        this->deleteLater();    // Если кадры закончились, то удаляем объект взрыва
    } else {
        this->update(-10,-10,20,20);    // В противном случае обновляем графический объект
    }
}

int Sprite::type() const {
    // Возвращаем тип объекта
    return Type;
}
