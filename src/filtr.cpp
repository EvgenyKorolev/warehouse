#include "filtr.h"
#include <QPushButton>
#include <QGridLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QLabel>
// Собственно фильтр
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
filtr::~filtr()
{
    delete kli;
}
void filtr::slot_fltr()
{
    emit accept();
}
QString filtr::result() const
{
    return kli->text();
}
// ====================--------------- Меню выбора высоты и ширины ячейки с фото ------------------=============================

size_select::size_select(int weidth, int heidth, QWidget* par) : QDialog(par)
{
    this->resize(500, 100);
    this->setWindowTitle("Настройка ячейки");
    this->setWindowIcon(QIcon(":/images/w.png"));
    ed_weidth = new QLineEdit();
    ed_heidth = new QLineEdit();
    ed_weidth->setInputMask("0000");
    ed_heidth->setInputMask("0000");
    ed_heidth->setText(QString::number(heidth));
    ed_weidth->setText(QString::number(weidth));
    QLabel* wlab = new QLabel();
    wlab->setText("Ширина: ");
    QLabel* hlab = new QLabel();
    hlab->setText("Высота: ");
    QGridLayout* main_lay = new QGridLayout();
    QPushButton* push_ok = new QPushButton("Применить");
    QPushButton* push_cancel = new QPushButton("Отмена");
    QObject::connect(push_ok, SIGNAL(clicked()), this, SLOT(slot_set()));
    QObject::connect(push_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    main_lay->addWidget(wlab, 0, 0);
    main_lay->addWidget(ed_weidth, 0, 1);
    main_lay->addWidget(hlab, 1, 0);
    main_lay->addWidget(ed_heidth, 1, 1);
    main_lay->addWidget(push_ok, 2, 0);
    main_lay->addWidget(push_cancel, 2, 1);
    this->setLayout(main_lay);
}
size_select::~size_select()
{
    delete ed_weidth;
    delete ed_heidth;
}
std::pair<int, int> size_select::result() const
{
    return std::make_pair(ed_weidth->text().toInt(), ed_heidth->text().toInt());
}
void size_select::slot_set()
{
    emit accept();
}
