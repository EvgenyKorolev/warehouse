#include "yes_no.h"

yes_no::yes_no(QString arg, QWidget *parent) : QDialog(parent)
{
    this->setWindowIcon(QIcon(":pic/images/w.png"));
    this->setWindowTitle("Внимание");
    QBoxLayout *main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QLabel *my_lab = new QLabel();
    my_lab->setText(arg);

    QBoxLayout *but_lay =new QBoxLayout(QBoxLayout::LeftToRight);
    QPushButton *my_ok = new QPushButton("Да");
    QPushButton *my_cancel = new QPushButton("Нет");
    QObject::connect(my_ok, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(my_cancel, SIGNAL(clicked()), this, SLOT(reject()));

    but_lay->addWidget(my_ok);
    but_lay->addWidget(my_cancel);
    main_lay->addSpacing(10);
    main_lay->addWidget(my_lab);
    main_lay->addSpacing(20);
    main_lay->addLayout(but_lay);
    this->setLayout(main_lay);
}
