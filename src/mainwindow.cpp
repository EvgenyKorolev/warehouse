#include "mainwindow.h"
#include "yes_no.h"
#include "lst_view.h"
#include "lst_model.h"
#include "delegats.h"
#include "editor_hollydays.h"
#include "filtr.h"
#include <QCloseEvent>
#include <QPushButton>
#include <QSortFilterProxyModel>
#include <QAbstractItemView>
#include <QDockWidget>
#include <QHeaderView>
#include <QPixmap>
#include <QLabel>
#include <QToolBar>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(1100, 700);
    this->setWindowTitle("Учёт и хранение");
    this->setWindowIcon(QIcon(":/images/w.png"));

    QMenuBar* main_tb = new QMenuBar(this);
    this->setMenuBar(main_tb);
    QAction* add_push = new QAction("Добавить запись");
    QAction* serch_push = new QAction("Поиск");
    QAction* reset_push = new QAction("Сброс");
    QAction* hollyday_push = new QAction("Праздники");
    QAction* about_push = new QAction("О программе");
    QMenu* sort_menu = new QMenu("Показать");
        QAction* act_all = new QAction("Все");
        QAction* act_no = new QAction("Неоплаченные");
        QAction* act_opl = new QAction("Оплаченные");
    QObject::connect(act_all, SIGNAL(triggered(bool)), this, SLOT(slot_all()));
    QObject::connect(act_opl, SIGNAL(triggered(bool)), this, SLOT(slot_opl()));
    QObject::connect(act_no, SIGNAL(triggered(bool)), this, SLOT(slot_def_filtr()));
    sort_menu->addAction(act_no);
    sort_menu->addAction(act_all);
    sort_menu->addAction(act_opl);
    main_tb->addAction(add_push);
    main_tb->addSeparator();
    main_tb->addMenu(sort_menu);
    main_tb->addSeparator();
    main_tb->addAction(serch_push);
    main_tb->addSeparator();
    main_tb->addAction(reset_push);
    main_tb->addSeparator();
    main_tb->addAction(hollyday_push);
    main_tb->addSeparator();
    main_tb->addAction(about_push);
    main_tb->addSeparator();
    view = new lst_view(this);
    QObject::connect(add_push, SIGNAL(triggered(bool)), view, SLOT(slot_add()));
    QObject::connect(hollyday_push, SIGNAL(triggered(bool)), this, SLOT(slot_hol()));
    QObject::connect(about_push, SIGNAL(triggered(bool)), this, SLOT(slot_about()));
    QObject::connect(reset_push, SIGNAL(triggered(bool)), this, SLOT(slot_def_filtr()));
    QObject::connect(serch_push, SIGNAL(triggered(bool)), this, SLOT(slot_search()));
    view->verticalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    view->verticalHeader()->setDefaultSectionSize(150);
    view->setSelectionMode(QAbstractItemView::ExtendedSelection);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    model = new lst_model();
    view->setItemDelegateForColumn(3, new show_delegat());
    view->setColumnWidth(3, settings::get_wight());
    view->setItemDelegateForColumn(5, new pic_delegat());
    QSortFilterProxyModel* smod = new QSortFilterProxyModel();
    view->setModel(smod);
    slot_filtr_reg("-", 0);
    PicLabel = new QLabel();
    connect(view->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(slot_set_pic()));
    // Для представления
    QDockWidget *view_area = new QDockWidget("Клиеты", this);
    view_area->setWidget(view);
    view_area->setAllowedAreas(Qt::LeftDockWidgetArea);
    view_area->setFeatures(QDockWidget::NoDockWidgetFeatures);
    addDockWidget(Qt::LeftDockWidgetArea, view_area);
    view_area->setMinimumWidth(700);
    this->setCentralWidget(PicLabel);
}
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
    if(edhol->exec() == QDialog::Accepted){}
    delete edhol;
}
void MainWindow::slot_def_filtr()
{
    slot_filtr_reg("-", 0);
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
void MainWindow::slot_set_pic()
{
    PicLabel->setAlignment(Qt::AlignHCenter);
    PicLabel->setPixmap(QPixmap::fromImage(view->model()->data(view->currentIndex(), Qt::UserRole).value<QImage>()));
}
void MainWindow::slot_search()
{
    filtr* edflt = new filtr(this);
    if (edflt->exec() == QDialog::Accepted){
         slot_filtr_reg(".*" + edflt->result() + ".*", 4);
         view->setColumnHidden(0, false);
         view->setColumnWidth(3, settings::get_wight());
         view->scrollToBottom();
    }
    delete edflt;
}
void MainWindow::slot_filtr_reg(const QString& arg, int col)
{
    QSortFilterProxyModel* smod = new QSortFilterProxyModel();
    QAbstractItemModel* dmod = view->model();
    view->setModel(smod);
    delete dmod;
    smod->setFilterKeyColumn(col);
    smod->setDynamicSortFilter(true);
    smod->setSourceModel(model);
    QRegExp reg;
    reg.setPattern(arg);
    smod->setFilterRegExp(reg);
    view->setColumnHidden(4, true);
    view->setColumnHidden(0, true);
    view->setColumnWidth(1, 90);
    view->setColumnWidth(2, 90);
    view->horizontalHeader()->setStretchLastSection(true);
    view->setSortingEnabled(true);
    //view->resizeRowsToContents();
    view->setColumnWidth(3, settings::get_wight());
    connect(view->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(slot_set_pic()));
}
void MainWindow::slot_filtr_str(const QString& arg, int col)
{
    QSortFilterProxyModel* smod = new QSortFilterProxyModel();
    QAbstractItemModel* dmod = view->model();
    view->setModel(smod);
    delete dmod;
    smod->setFilterKeyColumn(col);
    smod->setDynamicSortFilter(true);
    smod->setSourceModel(model);
    smod->setFilterFixedString(arg);
    view->setColumnHidden(4, true);
    view->setColumnHidden(0, true);
    view->setColumnWidth(1, 90);
    view->setColumnWidth(2, 90);
    view->horizontalHeader()->setStretchLastSection(true);
    view->setSortingEnabled(true);
    view->setColumnWidth(3, settings::get_wight());
    connect(view->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(slot_set_pic()));
}
void MainWindow::slot_all()
{
    slot_filtr_str("", 0);
    view->setColumnHidden(0, false);
    view->setColumnWidth(3, settings::get_wight() - 50);
    view->setColumnWidth(0, 50);
    view->scrollToBottom();
}
void MainWindow::slot_opl()
{
    slot_filtr_str("Да", 0);
    view->setColumnWidth(3, settings::get_wight());
    view->scrollToBottom();
}

