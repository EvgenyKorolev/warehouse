#include "filtr.h"
#include <QPushButton>
#include <QGridLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QLabel>

filtr::filtr(QWidget* par) : QDialog (par)
{
    QGridLayout* main_lay = new QGridLayout();
    QPushButton* push_ok = new QPushButton("Применить");
    QPushButton* push_cancel = new QPushButton("Отмена");
    QObject::connect(push_ok, SIGNAL(clicked()), this, SLOT(slot_fltr()));
    QObject::connect(push_cancel, SIGNAL(clicked()), this, SLOT(reject()));


    main_lay->addWidget(push_ok, 0, 0);
    main_lay->addWidget(push_cancel, 0, 1);
    this->setLayout(main_lay);
}
void filtr::slot_fltr()
{
    emit accept();
}
