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
#include <QScrollArea>
#include <QDockWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QPixmap>
#include <QLabel>
#include <QToolBar>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), t_status{false, true, true, true, false, true, false, false, false, false}
{
    this->resize(1100, 700);
    this->setWindowTitle("Учёт и хранение");
    this->setWindowIcon(QIcon(":/images/w.png"));
    QMenu* show_column = new QMenu("Столбцы");
    column0 = show_column->addAction("Оплата");
    column0->setCheckable(true);
    column0->setChecked(t_status.at(0));
    column1 = show_column->addAction("Оставлено");
    column1->setCheckable(true);
    column1->setChecked(t_status.at(1));
    column2 = show_column->addAction("Стоимость");
    column2->setCheckable(true);
    column2->setChecked(t_status.at(2));
    column3 = show_column->addAction("Информация");
    column3->setCheckable(true);
    column3->setChecked(t_status.at(3));
    column4 = show_column->addAction("ФИО Клиента");
    column4->setCheckable(true);
    column4->setChecked(t_status.at(4));
    column5 = show_column->addAction("Фотография");
    column5->setCheckable(true);
    column5->setChecked(t_status.at(5));
    column6 = show_column->addAction("Доп. информация");
    column6->setCheckable(true);
    column6->setChecked(t_status.at(6));
    column7 = show_column->addAction("Доп. стоимость");
    column7->setCheckable(true);
    column7->setChecked(t_status.at(7));
    column8 = show_column->addAction("Cтоимость суток");
    column8->setCheckable(true);
    column8->setChecked(t_status.at(8));
    column9 = show_column->addAction("Дата оплаты");
    column9->setCheckable(true);
    column9->setChecked(t_status.at(9));
    QObject::connect(column0, SIGNAL(toggled(bool)), this, SLOT(slot_change_columns()));
    QObject::connect(column1, SIGNAL(toggled(bool)), this, SLOT(slot_change_columns()));
    QObject::connect(column2, SIGNAL(toggled(bool)), this, SLOT(slot_change_columns()));
    QObject::connect(column3, SIGNAL(toggled(bool)), this, SLOT(slot_change_columns()));
    QObject::connect(column4, SIGNAL(toggled(bool)), this, SLOT(slot_change_columns()));
    QObject::connect(column5, SIGNAL(toggled(bool)), this, SLOT(slot_change_columns()));
    QObject::connect(column6, SIGNAL(toggled(bool)), this, SLOT(slot_change_columns()));
    QObject::connect(column7, SIGNAL(toggled(bool)), this, SLOT(slot_change_columns()));
    QObject::connect(column8, SIGNAL(toggled(bool)), this, SLOT(slot_change_columns()));
    QObject::connect(column9, SIGNAL(toggled(bool)), this, SLOT(slot_change_columns()));
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
    QAction* resize_table = new QAction("Размер ячеек");
    QObject::connect(act_all, SIGNAL(triggered(bool)), this, SLOT(slot_all()));
    QObject::connect(act_opl, SIGNAL(triggered(bool)), this, SLOT(slot_opl()));
    QObject::connect(act_no, SIGNAL(triggered(bool)), this, SLOT(slot_def_filtr()));
    QObject::connect(resize_table, SIGNAL(triggered(bool)), this, SLOT(slot_size_chenge()));
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
    main_tb->addMenu(show_column);
    main_tb->addSeparator();
    view = new lst_view(this);
    QObject::connect(add_push, SIGNAL(triggered(bool)), view, SLOT(slot_add()));
    QObject::connect(hollyday_push, SIGNAL(triggered(bool)), this, SLOT(slot_hol()));
    QObject::connect(about_push, SIGNAL(triggered(bool)), this, SLOT(slot_about()));
    QObject::connect(reset_push, SIGNAL(triggered(bool)), this, SLOT(slot_def_filtr()));
    QObject::connect(serch_push, SIGNAL(triggered(bool)), this, SLOT(slot_search()));
    view->verticalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    view->verticalHeader()->setDefaultSectionSize(settings::getInatance().get_hight());
    view->setSelectionMode(QAbstractItemView::ExtendedSelection);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    model = new lst_model();
    view->setItemDelegateForColumn(5, new show_delegat());
    view->setItemDelegateForColumn(3, new pic_delegat());
    PicLabel = new QLabel();
    view_area = new QDockWidget("Клиеты", this);
    view_area->setWidget(PicLabel);
    PicLabel->setFixedSize(QSize(600,600));
    view_area->setFeatures(QDockWidget::AllDockWidgetFeatures	);
    addDockWidget(Qt::RightDockWidgetArea, view_area);
    QMenu* show_doc = new QMenu("Просмотр фото");
    doc = show_doc->addAction("Показать");
    doc->setCheckable(true);
    if (settings::getInatance().get_ws() == win::one){
        doc->setChecked(false);
        slot_reset_doc();
    } else {
        doc->setChecked(true);
        slot_reset_doc();
    }
    main_tb->addMenu(show_doc);
    main_tb->addSeparator();
    main_tb->addAction(resize_table);
    QObject::connect(doc, SIGNAL(toggled(bool)), this, SLOT(slot_reset_doc()));
    slot_filtr_reg("-", 0);
    this->setCentralWidget(view);
    centralWidget()->setMinimumWidth(700);
    hide_columns();
}
MainWindow::~MainWindow(){}
void MainWindow::slot_reset_doc()
{
    if (doc->isChecked()){
        view_area->show();
        settings::getInatance().set_ws(win::two);
    } else{
        view_area->hide();
        settings::getInatance().set_ws(win::one);
    }
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
         view->scrollToBottom();
    }
    delete edflt;
}
void MainWindow::slot_def_filtr()
{
    slot_filtr_reg("-", 0);
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
    view->setColumnWidth(1, 90);
    view->setColumnWidth(2, 90);
    view->horizontalHeader()->setStretchLastSection(true);
    view->setSortingEnabled(true);
    hide_columns();
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
    view->setColumnWidth(1, 90);
    view->setColumnWidth(2, 90);
    view->horizontalHeader()->setStretchLastSection(true);
    view->setSortingEnabled(true);
    hide_columns();
    connect(view->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(slot_set_pic()));
}
void MainWindow::slot_all()
{
    slot_filtr_str("", 0);
    set_flag(0, true);
    hide_columns();
    view->setColumnWidth(0, 50);
    view->scrollToBottom();
}
void MainWindow::slot_opl()
{
    slot_filtr_str("Да", 0);
    hide_columns();
    view->scrollToBottom();
}
void MainWindow::hide_columns()
{
    view->setColumnHidden(0, !t_status.at(0));
    view->setColumnHidden(1, !t_status.at(1));
    view->setColumnHidden(2, !t_status.at(2));
    view->setColumnHidden(3, !t_status.at(3));
    view->setColumnHidden(4, !t_status.at(4));
    view->setColumnHidden(5, !t_status.at(5));
    view->setColumnHidden(6, !t_status.at(6));
    view->setColumnHidden(7, !t_status.at(7));
    view->setColumnHidden(8, !t_status.at(8));
    view->setColumnHidden(9, !t_status.at(9));
    view->setColumnWidth(3, settings::getInatance().get_wight());
}
void MainWindow::slot_change_columns()
{
    t_status[0] = column0->isChecked();
    t_status[1] = column1->isChecked();
    t_status[2] = column2->isChecked();
    t_status[3] = column3->isChecked();
    t_status[4] = column4->isChecked();
    t_status[5] = column5->isChecked();
    t_status[6] = column6->isChecked();
    t_status[7] = column7->isChecked();
    t_status[8] = column8->isChecked();
    t_status[9] = column9->isChecked();
    hide_columns();
}
void MainWindow::set_flag(int arg, bool set)
{
    switch (arg) {
    case 0:
        t_status[0] = set;
        column0->setChecked(set);
        break;
    case 1:
        t_status[1] = set;
        column1->setChecked(set);
        break;
    case 2:
        t_status[2] = set;
        column2->setChecked(set);
        break;
    case 3:
        t_status[3] = set;
        column3->setChecked(set);
        break;
    case 4:
        t_status[4] = set;
        column4->setChecked(set);
        break;
    case 5:
        t_status[5] = set;
        column5->setChecked(set);
        break;
    case 6:
        t_status[6] = set;
        column6->setChecked(set);
        break;
    case 7:
        t_status[7] = set;
        column7->setChecked(set);
        break;
    case 8:
        t_status[8] = set;
        column8->setChecked(set);
        break;
    case 9:
        t_status[9] = set;
        column9->setChecked(set);
        break;
    }
}
void MainWindow::slot_size_chenge()
{
    size_select* sed = new size_select(settings::getInatance().get_wight(), settings::getInatance().get_hight());
    if (sed->exec() == QDialog::Accepted){
        std::pair<int, int> ret = sed->result();
        settings::getInatance().set_wight(ret.first);
        settings::getInatance().set_hight(ret.second);
        view->setColumnWidth(3, settings::getInatance().get_wight());
        view->verticalHeader()->setDefaultSectionSize(settings::getInatance().get_hight());
        settings::getInatance().save_ini();
    }
    delete sed;
}
