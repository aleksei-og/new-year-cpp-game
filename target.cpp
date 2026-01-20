#include "target.h"

/// Функция для получения рандомного числа
 /// в диапазоне от минимального до максимального

static int randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}

Target::Target(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    health = randomBetween(1,15);   /// Задаём случайное значение здоровья
    maxHealth = health;             /// Устанавливаем максимальное здоровье равным текущему
}

Target::~Target()
{

}

QRectF Target::boundingRect() const
{
    return QRectF(-20,-20,40,40);   /// Ограничиваем область, в которой лежит цель
}

void Target::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /// Отрисовываем квадрат

    painter->setPen(Qt::black);
    painter->setBrush(Qt::green);
   // painter->drawRect(-20,-10,40,30);
    QPixmap s;
    s.load("C:/Igra/gift.png");
    painter->drawPixmap(-20,-10,s.scaled(40,30,Qt::IgnoreAspectRatio));
    /// Отрисовываем полоску жизни
     /// соизмеримо текущему здоровью
     /// относительно максимального здоровья

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    painter->drawRect(-20,-20, (int) 40*health/maxHealth,3);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Target::hit(int damage)
{
    health -= damage;   /// Уменьшаем здоровье мишени
    this->update(QRectF(-20,-20,40,40));    /// Перерисовываем мишень
    /// Если здоровье закончилось, то инициируем смерть мишени
    if(health <= 0)
    {
        this->deleteLater();
        emit death();
    }
}
