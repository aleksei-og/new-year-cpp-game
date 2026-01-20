#include "bullet.h"
#include <math.h>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}

Bullet::Bullet(QPointF start, QPointF end, QGraphicsItem * hero, QObject *parent)
    : QObject(parent), QGraphicsItem()
{
    this->hero = hero;      /// Запоминаем героя
    this->setRotation(0);   /// Устанавливаем начальный разворот
    this->setPos(start);    /// Устанавливаем стартовую позицию
    /// Определяем траекторию полёта пули
    QLineF lineToTarget(start, end);
    /// Угол поворота в направлении к цели
    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = TwoPi - angleToTarget;
    angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);

    ///Разворачиваем пули по траектории
    if (angleToTarget >= 0 && angleToTarget < Pi) {
        /// Rotate left
        setRotation(rotation() - angleToTarget * 180 /Pi);
    } else if (angleToTarget <= TwoPi && angleToTarget > Pi) {
        /// Rotate right
        setRotation(rotation() + (angleToTarget - TwoPi )* (-180) /Pi);
    }
    /// Инициализируем полётный таймер
    timerBullet = new QTimer();
    /// И подключаем его к слоту для обработки полёта пули
    connect(timerBullet, SIGNAL(timeout()), this, SLOT(slotTimerBullet()));
    timerBullet->start(7);
}

Bullet::~Bullet()
{

}

QRectF Bullet::boundingRect() const
{
    return QRectF(0,0,2,4);
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);
    painter->drawRect(0,0,2,4);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Bullet::slotTimerBullet()
{
    setPos(mapToParent(0, -10));

    /// Производим проверку на то, наткнулась ли пуля на какой-нибудь
     /// элемент на графической сцене.
     /// Для этого определяем небольшую область перед пулей,
     /// в которой будем искать элементы

    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                           << mapToScene(0, 0)
                                                           << mapToScene(-1, -1)
                                                           << mapToScene(1, -1));
    /// После чего проверяем все элементы.
     /// Одними из них будут сама Пуля и Герой - с ними ничего не делаем.
     /// А с остальными вызываем CallBack функцию

    foreach (QGraphicsItem *item, foundItems) {
        /// Добавляем в проверку ещё и сами взрывы,
         /// чтобы пули их игнорировали и не взрывались
         /// попав во взрвым от другой пули

        if (item == this || item == hero || item->type() == (UserType + 1))
            continue;
        /// При попадании по цели или препятствию, вызываем взрыв
        scene()->addItem(new Sprite(this->pos()));
        callbackFunc(item);     /// Вызываем CallBack функцию
        this->deleteLater();    /// Уничтожаем пулю
    }

    /// Проверка выхода за границы поля
     /// Если пуля вылетает за заданные границы, то пулю необходимо уничтожить

    if(this->x() < 0){
        this->deleteLater();
    }
    if(this->x() > 500){
        this->deleteLater();
    }

    if(this->y() < 0){
        this->deleteLater();
    }
    if(this->y() > 500){
        this->deleteLater();
    }
}

void Bullet::setCallbackFunc(void (*func)(QGraphicsItem *))
{
    callbackFunc = func;
}
