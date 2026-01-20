#include "widget.h"
#include "ui_widget.h"
#include <QLabel>
#include "sprite.h"
#include <QFile>
/** Функция для получения рандомного числа
 * в диапазоне от минимального до максимального
 * */
static int randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}

Widget::Widget(int diff,QString name,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    /// Устанавливаем параметры окна приложения
    this->diff=diff;
    this->name=name;
    this->resize(600,600);
    this->setFixedSize(600,600);

    ui->setupUi(this);
    scene   = new CustomScene();    /// Инициализируем кастомизированную сцену

    ui->graphicsView->setScene(scene);  /// Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    /// Устанавливаем сглаживание
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по горизонтали

    scene->setSceneRect(0,0,520,520);   /// Устанавливаем размеры графической сцены

    /// Создаем кастомизированный курсор из ресурсного файла
    QCursor cursor = QCursor(QPixmap(":/cursor/cursorTarget.png"));
    ui->graphicsView->setCursor(cursor);    /// Устанавливаем курсор в QGraphicsView
    triangle = new Triangle();  /// Инициализируем треугольник
    triangle->setPos(60,60);  /// Устанавливаем стартовую позицию треугольника
    triangle->setZValue(2);
    scene->addItem(triangle);   /// Добавляем треугольник на графическую сцену

    /** � азрешаем отслеживание положение курсора мыши
     * без необходимости нажатия на кнопки мыши
     * Применяем это свойство именно для QGraphicsView,
     * в котором установлена графическая сцена
     * */
    ui->graphicsView->setMouseTracking(true);

    /// Подключаем сигнал от графической сцены к слоту треугольника
    connect(scene, SIGNAL(signalTargetCoordinate(QPointF)), triangle, SLOT(slotTarget(QPointF)));
    /// Соединяем сигнала стрельбы с графической сцены со слотом разрешения стрельбы треугольника
    connect(scene, SIGNAL(signalShot(bool)), triangle, SLOT(slotShot(bool)));
    /// Соединяем сигнал на создание пули со слотом, создающим пули в игре
            connect(triangle, SIGNAL(signalBullet(QPointF,QPointF)), this, SLOT(slotBullet(QPointF,QPointF)));

    // Поставим стены
    scene->addRect(0,0,520,20,QPen(Qt::NoPen),QBrush(Qt::darkGray));
    scene->addRect(0,0,20,520,QPen(Qt::NoPen),QBrush(Qt::darkGray));
    scene->addRect(0,500,520,20,QPen(Qt::NoPen),QBrush(Qt::darkGray));
    scene->addRect(500,0,20,520,QPen(Qt::NoPen),QBrush(Qt::darkGray));
    scene->addRect(170,250,180,20,QPen(Qt::NoPen),QBrush(Qt::darkGray));
    scene->addRect(250,170,20,180,QPen(Qt::NoPen),QBrush(Qt::darkGray));

    /// Инициализируем таймер для создания мишеней
    timerTarget = new QTimer();
    connect(timerTarget, SIGNAL(timeout()), this, SLOT(slotCreateTarget()));
    timerTarget->start(1500);
    timerId = startTimer(1000*60*(5-diff));
    timer_copy = new QTimer();
    timer_help = new QTimer();
    connect(timer_help, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer_copy->start(1000*60*(5-diff));
    timer_help->start(1000);
    in_game=true;
    number=0;
record=0;
}
void Widget::updateTime()
{


    //qDebug()<<record;

    scene->addRect(0,0,520,20,QPen(Qt::NoPen),QBrush(Qt::darkGray));
     scene->addText(QString::number((timer_copy->remainingTime())/1000)+" seconds remain");
}
void Widget::timerEvent(QTimerEvent *e) {

    Q_UNUSED(e);

   in_game=false;
   gameOver();
   repaint();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slotBullet(QPointF start, QPointF end)
{
    /// Добавляем на сцену пулю
    Bullet *bullet = new Bullet(start, end, triangle);
    bullet->setCallbackFunc(slotHitTarget);
    scene->addItem(bullet);
}

void Widget::slotCreateTarget()
{
    Target *target = new Target();
    /// Создаём цель
    scene->addItem(target);         /// Помещаем цель в сцену со случайной позицией
    connect(target,SIGNAL(death()),SLOT(record_update()));
    target->setPos(qrand() % ((500 - 40 + 1) - 40) + 40,
                  qrand() % ((500 - 40 + 1) - 40) + 40);
    target->setZValue(-1);          /// Помещаем цель ниже Героя
    targets.append(target);         /// Добавляем цель в список
number++;
}

void Widget::slotHitTarget(QGraphicsItem *item)
{
    /** Получив сигнал от Пули
     * Перебираем весь список целей и наносим ему случайный урон
     * */
    foreach (QGraphicsItem *targ, targets) {
        if(targ == item){
            /// Кастуем объект из списка в класс Target
            Target *t = qgraphicsitem_cast <Target *> (targ);
            t->hit(randomBetween(1,3)); /// Наносим урон
        }
    }
}
void Widget::record_update()
{
    record++;
}
QList<QGraphicsItem *> Widget::targets; /// реализация списка

void Widget::gameOver() {
    QString message = "Game over. Result: "+QString::number(record);
    //QFont font("Courier", 150, QFont::DemiBold);

QVBoxLayout* l=new QVBoxLayout;
timerId=0;
QLabel* lbl=new QLabel(message);
l->addWidget(lbl);
QWidget* w=new QWidget;
w->setLayout (l);
w->show();
this->close();
  /// Устанавливаем размеры графической сцены
QFile file("C:/Igra/file.txt");
file.open(QIODevice::Append);

QByteArray nom;
for(int i=0;i<name.size();i++)
nom.append(name[i].toLatin1());
QByteArray num;
for(int i=0;i<QString::number(record).size();i++)
num.append(QString::number(record)[i].toLatin1());


file.write(nom); ///добавляем имя и записываем в файл
file.write(":");
file.write(num);
file.write("\n");
file.close();

timerTarget->stop();


}
