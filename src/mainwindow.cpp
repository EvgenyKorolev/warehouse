#include <QHeaderView>
#include "mainwindow.h"
#include "yes_no.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(900, 600);
    this->setWindowTitle("Учёт и хранение");
    this->setWindowIcon(QIcon(":/images/w.png"));
    QWidget* central_widget = new QWidget();
    this->setCentralWidget(central_widget);
    QGridLayout* main_layout = new QGridLayout(central_widget);
    central_widget->setLayout(main_layout);

    QPushButton* add_push = new QPushButton("Добавить запись");
    QPushButton* sort_push = new QPushButton("Сортировать");
    QPushButton* serch_push = new QPushButton("Поиск");
    QPushButton* reset_push = new QPushButton("Сброс");
    QPushButton* hollyday_push = new QPushButton("Праздники");
    QPushButton* about_push = new QPushButton("О программе");
    view = new lst_view();
    QObject::connect(add_push, SIGNAL(clicked()), view, SLOT(slot_add()));
    view->setColumnWidth(0, 200);
    view->setColumnWidth(1, 200);
    view->setColumnWidth(2, 200);
    view->setColumnWidth(3, 50);
    view->horizontalHeader()->setStretchLastSection(true);
    view->setSortingEnabled(true);
    model = new lst_model();
    QSortFilterProxyModel* smod = new QSortFilterProxyModel();
    smod->setFilterKeyColumn(3);
    smod->setDynamicSortFilter(true);
    smod->setSourceModel(model);
    smod->setFilterFixedString("-");
    view->setModel(smod);

    main_layout->addWidget(add_push, 0, 0);
    main_layout->addWidget(sort_push, 0, 1);
    main_layout->addWidget(serch_push, 0, 2);
    main_layout->addWidget(reset_push, 1, 0);
    main_layout->addWidget(hollyday_push, 1, 1);
    main_layout->addWidget(about_push, 1, 2);
    main_layout->addWidget(view, 2, 0, 1, 3)

;}
MainWindow::~MainWindow()
{

}
void MainWindow::closeEvent(QCloseEvent *event)
{
    yes_no* pmbx = new yes_no("Вы действительно хотите выйти?");
    if (pmbx->exec() == QDialog::Accepted){
       event->accept();
       QMainWindow::closeEvent(event);
       return;
    }
    delete pmbx;
    event->ignore();
}
