#include "filtr.h"
#include <QPushButton>
#include <QGridLayout>
#include <QFormLayout>
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
    this->setWindowTitle("Настройка ячейки");
    this->setWindowIcon(QIcon(":/images/w.png"));
    ed_weidth = new QLineEdit();
    ed_heidth = new QLineEdit();
    ed_weidth->setInputMask("0000");
    ed_heidth->setInputMask("0000");
    ed_heidth->setText(QString::number(heidth));
    ed_weidth->setText(QString::number(weidth));
    QVBoxLayout* main_lay = new QVBoxLayout();
    QPushButton* push_ok = new QPushButton("Применить");
    QPushButton* push_cancel = new QPushButton("Отмена");
    QObject::connect(push_ok, SIGNAL(clicked()), this, SLOT(slot_set()));
    QObject::connect(push_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    QLabel* titl = new QLabel();
    titl->setText("Настройка размеров ячейки");
    main_lay->addWidget(titl);
    QFormLayout* fl = new QFormLayout();
    fl->addRow(tr("&Ширина: "), ed_weidth);
    fl->addRow(tr("Высота: "), ed_heidth);
    QHBoxLayout* push_lay = new QHBoxLayout();
    push_lay->addWidget(push_ok);
    push_lay->addWidget(push_cancel);
    main_lay->addLayout(fl);
    main_lay->addLayout(push_lay);
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
// Меню настройки номера порта сервера и пароля для доступа;
server_set::server_set(quint16 port_, const QString& pass_, QWidget* par) : QDialog(par)
{
    this->setWindowTitle("Настройка сети");
    this->setWindowIcon(QIcon(":/images/w.png"));
    ed_pass = new QLineEdit();
    ed_port = new QLineEdit();
    ed_port->setInputMask("00000000");
    ed_pass->setInputMask("nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn");
    ed_port->setText(QString::number(port_));
    ed_pass->setText(pass_);
    QVBoxLayout* main_lay = new QVBoxLayout();
    QPushButton* push_ok = new QPushButton("Применить");
    QPushButton* push_cancel = new QPushButton("Отмена");
    QObject::connect(push_ok, SIGNAL(clicked()), this, SLOT(slot_set()));
    QObject::connect(push_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    QLabel* titl = new QLabel();
    titl->setText("Настройка размеров ячейки");
    main_lay->addWidget(titl);
    QFormLayout* fl = new QFormLayout();
    fl->addRow(tr("&TCP порт: "), ed_port);
    fl->addRow(tr("Пароль: "), ed_pass);
    QHBoxLayout* push_lay = new QHBoxLayout();
    push_lay->addWidget(push_ok);
    push_lay->addWidget(push_cancel);
    main_lay->addLayout(fl);
    main_lay->addLayout(push_lay);
    this->setLayout(main_lay);
}
server_set::~server_set()
{
    delete ed_port;
    delete ed_pass;
}
std::pair<quint16, QString> server_set::result() const
{
    return std::make_pair(ed_port->text().toInt(), ed_pass->text());
}
void server_set::slot_set()
{
    emit accept();
}
