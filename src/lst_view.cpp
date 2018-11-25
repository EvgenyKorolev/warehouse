#include "lst_view.h"
#include "yes_no.h"
#include "editor_object.h"
#include "mainwindow.h"
#include <memory>
#include <QMessageBox>
#include <QMenu>

lst_view::lst_view(MainWindow *arg, QWidget *par) : QTableView (par)
{
    this->par = arg;
}
void lst_view::mousePressEvent(QMouseEvent *arg)
{
    if ((arg->buttons() == Qt::RightButton)){
        QMenu *mnu = new QMenu(this);
        mnu->setEnabled(true);
        if (this->indexAt(arg->pos()).isValid()) {
            curs = arg->pos();
            QAction *ed_obj = new QAction("Редактировать", this);
            QObject::connect(ed_obj, SIGNAL(triggered()), this, SLOT(slot_edit()));
            QAction *flt_obj = new QAction("Фильтр", this);
            QObject::connect(flt_obj, SIGNAL(triggered()), par, SLOT(slot_search()));
            QAction *add_obj = new QAction("Добавить объект", this);
            QObject::connect(add_obj, SIGNAL(triggered()), this, SLOT(slot_add()));
            QAction *del_obj = new QAction("Удалить объект", this);
            QObject::connect(del_obj, SIGNAL(triggered()), this, SLOT(slot_del()));
            mnu->addAction(ed_obj);
            mnu->addAction(flt_obj);
            mnu->addAction(add_obj);
            mnu->addAction(del_obj);
        } else {
            QAction *ed_doc = new QAction("Добавить объект", this);
            QObject::connect(ed_doc, SIGNAL(triggered()), this, SLOT(slot_add()));
            QAction *fix_doc = new QAction("Фильтр", this);
            QObject::connect(fix_doc, SIGNAL(triggered()), par, SLOT(slot_search()));
            mnu->addAction(ed_doc);
            mnu->addAction(fix_doc);
    }
        mnu->popup(arg->globalPos());
        mnu->show();
    }
    QTableView::mousePressEvent(arg);
}
void lst_view::mouseDoubleClickEvent(QMouseEvent* arg)
{
    curs = arg->pos();
    if (this->indexAt(curs).isValid()){
        slot_edit();
    } else {
        slot_add();
    }
    QTableView::mouseDoubleClickEvent(arg);
}
void lst_view::slot_add()
{
    editor_object* edob = new editor_object();
    if (edob->exec() == QDialog::Accepted){
        std::shared_ptr<persisted_object> tmpl(new persisted_object(edob->result()));
        int i = model()->rowCount();
        model()->setData(model()->index(i, 0, QModelIndex()), QVariant::fromValue(tmpl), Qt::EditRole);
    }
    delete edob;
    par->slot_def_filtr();
}
void lst_view::slot_edit()
{
    editor_object* edob = new editor_object(*(this->indexAt(curs).data(Qt::EditRole).value<std::shared_ptr<persisted_object>>()));
    if (edob->exec() == QDialog::Accepted){
        int i{indexAt(curs).row()};
        model()->setData(model()->index(i, 0, QModelIndex()), QVariant::fromValue(std::make_shared<persisted_object>(edob->result())), Qt::EditRole);
    }
    delete edob;
    par->slot_def_filtr();
}
void lst_view::slot_del()
{
    yes_no* pmbx = new yes_no("Вы действительно хотите удалить запись?");
    if (pmbx->exec() == QDialog::Accepted){
        model()->removeRow(indexAt(curs).row(), QModelIndex());
       return;
    }
    delete pmbx;
    par->slot_def_filtr();
}
