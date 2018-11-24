#include "editor_object.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
editor_object::editor_object(QWidget* par) : QDialog(par)
{
    data = persisted_object();
    init();
}
editor_object::editor_object(const persisted_object &arg, QWidget *par) : QDialog(par)
{
    data = arg;
    init();
}
void editor_object::init()
{
    this->resize(500, 800);
    this->setWindowTitle("Добавить объект");
    this->setWindowIcon(QIcon(":/images/w.png"));
    ed_name = new QLineEdit();
    ed_name->setText(data.get_name());
    ed_surname = new QLineEdit();
    ed_surname->setText(data.get_surname());
    ed_fname = new QLineEdit();
    ed_fname->setText(data.get_fname());
    ed_start_data = new QDateEdit();
    ed_start_data->setDate(data.get_start_data());
    ed_info = new QTextEdit();
    ed_info->setText(data.get_info());
    ed_info->setFixedHeight(100);
    cost = new QSpinBox();
    dop_cost = new QSpinBox();
    cost->setSuffix(" руб.");
    dop_cost->setSuffix(" руб.");
    cost->setMinimum(0);
    cost->setMaximum(1000000000);
    dop_cost->setMinimum(0);
    dop_cost->setMaximum(1000000000);
    cost->setValue(static_cast<int>(data.get_cost()));
    dop_cost->setValue(static_cast<int>(data.get_dop_cost()));

    QPushButton* push_ok = new QPushButton("Готово");
    QObject::connect(push_ok, SIGNAL(clicked()), this, SLOT(slot_save()));
    QPushButton* push_cancel = new QPushButton("Отмена");
    QObject::connect(push_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    QPushButton* image_push = new QPushButton("Загрузить фото");

    QLabel* lab_name = new QLabel();
    lab_name->setText("Имя клиента: ");
    QLabel* lab_surname = new QLabel();
    lab_surname->setText("Фамилия клиента: ");
    QLabel* lab_fname = new QLabel();
    lab_fname->setText("Отчество клиента: ");
    QLabel* lab_start_data = new QLabel();
    lab_start_data->setText("Дата сдачи на хранение: ");
    QLabel* lab_info = new QLabel();
    lab_info->setText("Дополнительные сведения: ");
    QLabel* lab_cost = new QLabel();
    lab_cost->setText("Стоимость за сутки: ");
    QLabel* lab_dop_cost = new QLabel();
    lab_dop_cost->setText("Стоиморсть допролнительных услуг: ");

    main_scene = new QGraphicsScene();
    main_view = new QGraphicsView();
    main_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    main_view->setRenderHint(QPainter::Antialiasing);
    main_view->setCacheMode(QGraphicsView::CacheBackground);
    main_view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    main_view->setScene(main_scene);

    QGridLayout* main_lay = new QGridLayout();
    QHBoxLayout* push_lay = new QHBoxLayout();
    push_lay->addWidget(push_ok);
    push_lay->addWidget(push_cancel);

    main_lay->addWidget(main_view, 0, 0, 1, 2);
    main_lay->addWidget(image_push, 1, 0, 1, 2);
    main_lay->addWidget(lab_name, 2, 0);
    main_lay->addWidget(ed_name, 2, 1);
    main_lay->addWidget(lab_surname, 3, 0);
    main_lay->addWidget(ed_surname, 3, 1);
    main_lay->addWidget(lab_fname, 4, 0);
    main_lay->addWidget(ed_fname, 4, 1);
    main_lay->addWidget(lab_start_data, 5, 0);
    main_lay->addWidget(ed_start_data, 5, 1);
    main_lay->addWidget(lab_info, 6, 0, 1, 2);
    main_lay->addWidget(ed_info, 7, 0, 1, 2);
    main_lay->addWidget(lab_cost, 8, 0);
    main_lay->addWidget(cost, 8, 1);
    main_lay->addWidget(lab_dop_cost, 9, 0);
    main_lay->addWidget(dop_cost, 9, 1);
    main_lay->addLayout(push_lay, 10, 0, 1, 2);
    this->setLayout(main_lay);
}
editor_object::~editor_object()
{
    delete ed_name;
    delete ed_surname;
    delete ed_fname;
    delete ed_start_data;
    delete ed_info;
    delete cost;
    delete dop_cost;
    delete main_scene;
    delete main_view;
}
void editor_object::slot_save()
{
    data.set_person(std::make_tuple(ed_name->text(), ed_surname->text(), ed_fname->text()));
    data.set_start_data(ed_start_data->date());
    data.set_info(ed_info->toPlainText());
    data.set_cost(static_cast<unsigned>(cost->value()));
    data.set_dop_cost(static_cast<unsigned>(dop_cost->value()));
    data.add_photo(actual_img);
    emit accept();
}
persisted_object editor_object::result()
{
    return  data;
}
