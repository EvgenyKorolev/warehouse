#include "mainwindow.h"
#include "yes_no.h"
#include "lst_view.h"
#include "lst_model.h"
#include "editor_hollydays.h"
#include <QCloseEvent>
#include <QPushButton>
#include <QSortFilterProxyModel>
#include <QDockWidget>
#include <QHeaderView>
#include <QLabel>
#include <QToolBar>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(900, 600);
    this->setWindowTitle("Учёт и хранение");
    this->setWindowIcon(QIcon(":/images/w.png"));

    QToolBar* main_tb = new QToolBar(this);
    this->addToolBar(Qt::ToolBarArea::TopToolBarArea, main_tb);
    QAction* add_push = new QAction("Добавить запись");
    QAction* sort_push = new QAction("Сортировать");
    QAction* serch_push = new QAction("Поиск");
    QAction* reset_push = new QAction("Сброс");
    QAction* hollyday_push = new QAction("Праздники");
    QAction* about_push = new QAction("О программе");

    main_tb->addAction(add_push);
    main_tb->addAction(sort_push);
    main_tb->addAction(serch_push);
    main_tb->addAction(reset_push);
    main_tb->addAction(hollyday_push);
    main_tb->addAction(about_push);
    view = new lst_view(this);
    QObject::connect(add_push, SIGNAL(triggered(bool)), view, SLOT(slot_add()));
    QObject::connect(hollyday_push, SIGNAL(triggered(bool)), this, SLOT(slot_hol()));
    QObject::connect(about_push, SIGNAL(triggered(bool)), this, SLOT(slot_about()));
    QObject::connect(reset_push, SIGNAL(triggered(bool)), this, SLOT(slot_def_filtr()));
    view->setColumnWidth(0, 200);
    view->setColumnWidth(1, 200);
    view->setColumnWidth(2, 200);
    view->setColumnWidth(3, 50);
    view->horizontalHeader()->setStretchLastSection(true);
    view->setSortingEnabled(true);
    model = new lst_model();
    slot_def_filtr();

    PicLabel = new QLabel();

    // Для представления
    QDockWidget *view_area = new QDockWidget("Клиеты", this);
    view_area->setWidget(view);
    view_area->setAllowedAreas(Qt::LeftDockWidgetArea);
    view_area->setFeatures(QDockWidget::NoDockWidgetFeatures);
    addDockWidget(Qt::LeftDockWidgetArea, view_area);
    view_area->setMinimumWidth(450);
    this->setCentralWidget(PicLabel);
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
void MainWindow::slot_hol()
{
    editor_hollydays* edhol = new editor_hollydays();
    if(edhol->exec() == QDialog::Accepted){

    }
}
void MainWindow::slot_def_filtr()
{
    QSortFilterProxyModel* smod = new QSortFilterProxyModel();
    view->setModel(smod);
    smod->setFilterKeyColumn(3);
    smod->setDynamicSortFilter(true);
    smod->setSourceModel(model);
   // smod->setFilterFixedString("-");
    view->setColumnHidden(0, true);
}
void MainWindow::slot_about()
{
    QMessageBox about;
    about.setText("<table><tr><th>"
                  "<img src=\":/images/w2.png\"> </th> <th><br><br>Программа для учёта хранимых объектов <br>"
                  "Программу разработал Евгений Королёв <br> "
                  "Cайт: <a href = 'http://kyrych.ru'>kyrych.ru</a><br> "
                  "E-mail: <a href = 'mailto:root@kyrych.ru'>root@kyrych.ru</a> <br> "
                  "XMPP: kyrych@xmpp.ru "
                  "</th></tr></table>");
    about.setWindowIcon(QIcon(":/images/w.png"));
    about.setWindowTitle("О программе:");
    about.exec();
}
