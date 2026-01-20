#ifndef MENU_H
#define MENU_H

#include <QtGui>
#include <QPushButton>
#include <QLineEdit>
#include <QDialog>
#include <QMessageBox>
#include "widget.h"

class QLineEdit;
class menu : public QDialog {
    Q_OBJECT
private:
   int diff;
    int mode;

    QString name;
    QLineEdit* line;
public:
    menu(QWidget* pwgt = 0);
   public slots:
    void slotButtonClicked();
    void slotButtonClicked1();

    void slotButtonClicked_d1();
    void slotButtonClicked_d2();



signals:
    void b_c(const int& diff,const int& mode);

};
#endif // MENU_H
