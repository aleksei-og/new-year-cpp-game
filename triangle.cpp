#include "triangle.h"
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

Triangle::Triangle(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    setRotation(0);      /// Устанавливаем исходный разворот треугольника

    target = QPointF(0,0);  /// Устанавливаем изначальное положение курсора
    shot = false;

    gameTimer = new QTimer();   /// Инициализируем игровой таймер
    /// Подключаем сигнал от таймера и слоту обработки игрового таймера
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(slotGameTimer()));
    gameTimer->start(5);   /// Стартуем таймер

    bulletTimer = new QTimer(); /// Инициализируем таймер создания пуль
    connect(bulletTimer, SIGNAL(timeout()), this, SLOT(slotBulletTimer()));
    bulletTimer->start(1000/6); /// Стреляем 6 раз в секунду


}

Triangle::~Triangle()
{

}

/// Изменены размеры героя
QRectF Triangle::boundingRect() const
{
    return QRectF(-12,-15,24,30);
}

/// Возвращаем форму героя
 /// В данном случае лучше использовать эллипс

QPainterPath Triangle::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /** Отрисовка треугольника
     * */
    QPolygon polygon;
   // polygon << QPoint(0,-15) << QPoint(12,15) << QPoint(-12,15);
    //painter->setBrush(Qt::red);
   // painter->drawPolygon(polygon);
    QPixmap s;
    s.load("C:/Igra/tree.png");
    painter->drawPixmap(-21.5,-21.5,s.scaled(33,42,Qt::IgnoreAspectRatio));
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Triangle::slotTarget(QPointF point)
{
    /// Определяем расстояние до цели
    target = point;
    QLineF lineToTarget(QPointF(0, 0), mapFromScene(target));
    /// Угол поворота в направлении к цели
    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = TwoPi - angleToTarget;
    angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);

     /// устанавливаем направление поворота героя в данном тике таймера
     /// Скорость разворота зависит от угла, на который необходимо повернуться треугольнику

    if (angleToTarget >= 0 && angleToTarget < Pi) {
        /// Rotate left
        setRotation(rotation() - angleToTarget * 180 /Pi);
    } else if (angleToTarget <= TwoPi && angleToTarget > Pi) {
        /// Rotate right
        setRotation(rotation() + (angleToTarget - TwoPi )* (-180) /Pi);
    }
}

void Triangle::slotGameTimer()
{
    /** Перемещаем треугольник в зависимости от нажатых кнопок
     * */
    if(GetAsyncKeyState('A')){
        this->setX(this->x() - 1);
        /** Проверяем на столкновение,
         * если столкновение произошло,
         * то возвращаем героя обратно в исходную точку
         * */
        if(!scene()->collidingItems(this).isEmpty()){
            this->setX(this->x() + 1);
        }
    }
    if(GetAsyncKeyState('D')){
        this->setX(this->x() + 1);
        /** Проверяем на столкновение,
         * если столкновение произошло,
         * то возвращаем героя обратно в исходную точку
         * */
        if(!scene()->collidingItems(this).isEmpty()){
            this->setX(this->x() - 1);
        }
    }
    if(GetAsyncKeyState('W')){
        this->setY(this->y() - 1);
        /** Проверяем на столкновение,
         * если столкновение произошло,
         * то возвращаем героя обратно в исходную точку
         * */
        if(!scene()->collidingItems(this).isEmpty()){
            this->setY(this->y() + 1);
        }
    }
    if(GetAsyncKeyState('S')){
        this->setY(this->y() + 1);
        /** Проверяем на столкновение,
         * если столкновение произошло,
         * то возвращаем героя обратно в исходную точку
         * */
        if(!scene()->collidingItems(this).isEmpty()){
            this->setY(this->y() - 1);
        }
    }

    /** Проверка выхода за границы поля
     * Если объект выходит за заданные границы, то возвращаем его назад
     * */
    if(this->x() - 30 < 0){
        this->setX(30);         /// слева
    }
    if(this->x() + 30 > 520){
        this->setX(520 - 30);   /// справа
    }

    if(this->y() - 30 < 0){
        this->setY(30);         /// сверху
    }
    if(this->y() + 30 > 520){
        this->setY(520 - 30);   /// снизу
    }

    QLineF lineToTarget(QPointF(0, 0), mapFromScene(target));
    /// Угол поворота в направлении к цели
    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = TwoPi - angleToTarget;
    angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);

    /**
     * устанавливаем направление поворота героя в данном тике таймера
     * Скорость разворота зависит от угла, на который необходимо повернуться герою
     * */
    if (angleToTarget >= 0 && angleToTarget < Pi) {
        /// Rotate left
        setRotation(rotation() - angleToTarget * 180 /Pi);
    } else if (angleToTarget <= TwoPi && angleToTarget > Pi) {
        /// Rotate right
        setRotation(rotation() + (angleToTarget - TwoPi )* (-180) /Pi);
    }
}

void Triangle::slotBulletTimer()
{
    /// Если стрельба разрешена, то вызываем сигнал на создание пули
    if(shot) emit signalBullet(mapToScene(0,-25), target);

}

void Triangle::slotShot(bool shot)
{
    this->shot = shot;  /// Получаем разрешение или запрет на стрельбу
}
