#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QDebug>

#include <triangle.h>
#include <customscene.h>
#include <bullet.h>
#include <target.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(int diff,QString name,QWidget *parent = 0);
    ~Widget();
    void timerEvent(QTimerEvent *e);
private:
    int number;
    Ui::Widget *ui;
    CustomScene  *scene;        /// Объявляем графическую сцену
    Triangle *triangle;         /// Объявляем треугольник
    QTimer *timerTarget;        /// Таймер для создания мишеней
    QTimer *timer_copy;
    QTimer *timer_help;
    bool in_game;
    static QList<QGraphicsItem *> targets;  /// Список мишеней
    int diff; ///сложность
    static void slotHitTarget(QGraphicsItem *item); /// CallBack Функция
    int record;
    QString name;
void record_plus(int n);
int timerId;///таймер
private slots:
    void slotBullet(QPointF start, QPointF end); /// Слот для создания пули
    void slotCreateTarget(); /// Слот для создания мишеней
    void gameOver();
    void updateTime();
    void record_update();
};

#endif // WIDGET_H
