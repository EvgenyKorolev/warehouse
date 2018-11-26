#include "filtr.h"
#include <QPushButton>
#include <QGridLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QLabel>

filtr::filtr(QWidget* par) : QDialog (par)
{
    this->resize(500, 100);
    this->setWindowTitle("Найти");
    this->setWindowIcon(QIcon(":/images/w.png"));
    QGridLayout* main_lay = new QGridLayout();
    QPushButton* push_ok = new QPushButton("Применить");
    QPushButton* push_cancel = new QPushButton("Отмена");
    QObject::connect(push_ok, SIGNAL(clicked()), this, SLOT(slot_fltr()));
    QObject::connect(push_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    kli = new QLineEdit();
    QLabel* lab_kli = new QLabel();
    lab_kli->setText("ФИО клиента: ");
    main_lay->addWidget(lab_kli, 0, 0);
    main_lay->addWidget(kli, 0, 1, 1, 3);
    main_lay->addWidget(push_ok, 1, 0, 1, 2);
    main_lay->addWidget(push_cancel, 1, 2, 1, 2);
    this->setLayout(main_lay);
}
void filtr::slot_fltr()
{
    emit accept();
}
QString filtr::result()
{
    return kli->text();
}
