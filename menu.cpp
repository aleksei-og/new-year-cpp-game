
#include <QtGui>
#include <QApplication>
#include <QMenu>
#include <QtWidgets>
#include <QMenuBar>
#include <QObject>
#include "menu.h"


menu::menu(QWidget* pwgt/*= 0*/)
: QDialog(pwgt, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
    diff=1;
    mode=2;
    QLabel* plbl1= new QLabel("Сложность:  ");
    QLabel* plbl2= new QLabel("Имя:  ");
    line = new QLineEdit;
    QRadioButton* easy=new QRadioButton("Низкая (4 минуты)");
    QRadioButton* hard=new QRadioButton("Высокая (3 минуты)");
    QPushButton* play = new QPushButton("&Играть");
    QPushButton* record = new QPushButton("&Рекорды");
    connect(play, SIGNAL(clicked()), SLOT(slotButtonClicked()));
    connect(record, SIGNAL(clicked()), SLOT(slotButtonClicked1()));
    connect(easy, SIGNAL(clicked()), SLOT(slotButtonClicked_d1()));
    connect(hard, SIGNAL(clicked()), SLOT(slotButtonClicked_d2()));

    //Layout setup
    QVBoxLayout* Layout = new QVBoxLayout;
    QWidget* w1=new QWidget;

    QHBoxLayout* l1=new QHBoxLayout;

    l1->addWidget(easy);

    l1->addWidget(hard);
    w1->setLayout(l1);
     Layout->addWidget(plbl2);
      Layout->addWidget(line);
    Layout->addWidget(plbl1);
    Layout->addWidget(w1);
    Layout->addWidget(play);
    Layout->addWidget(record);
    setLayout(Layout);

}


void menu::slotButtonClicked()
{
  Widget* w=new Widget(diff,line->text());
  w->show();
}
void menu::slotButtonClicked1()
{
    QFile file("C:/Igra/file.txt");
    file.open(QIODevice::ReadOnly);
    QWidget* r=new QWidget;
    QVBoxLayout* l=new QVBoxLayout;
   while(!file.atEnd())
   {
       QLabel* lbl=new QLabel(file.readLine());
       l->addWidget(lbl);
   }
   r->setLayout(l);
   r->show();
    file.close();

}
void menu::slotButtonClicked_d1()
{
    diff=1;
}
void menu::slotButtonClicked_d2()
{
    diff=2;
}
