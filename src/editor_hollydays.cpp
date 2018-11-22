#include "editor_hollydays.h"
#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>
#include <QMouseEvent>
#include <QSortFilterProxyModel>
#include <QDateEdit>
#include <QLabel>
#include <QMenu>
#include <QRegExp>
#include "settings.h"
editor_hollydays::editor_hollydays(QWidget* par) : QDialog (par)
{
    this->resize(150, 400);
    this->setWindowTitle("Выходные дни");
    this->setWindowIcon(QIcon(":/images/w.png"));
    QGridLayout* main_lay = new QGridLayout();
    model = new hollydays_model();
    view = new hollydays_view(this);
    QLabel* lab = new QLabel();
    lab->setText("Список праздников:");
    years = new QComboBox();
    years->addItem("Все годы");
    if (settings::getInatance().lst_holliday()->size() > 0){
        QDate start = settings::getInatance().lst_holliday()->front();
        QDate end = settings::getInatance().lst_holliday()->last();
        QString tmp{""};
        do  {
            tmp += QString::number(start.year()) += " год";
            years->addItem(tmp);
            tmp = "";
            start = start.addYears(1);
        } while (start <= end);

    }
    QObject::connect(years, SIGNAL(currentTextChanged(const QString&)), this, SLOT(slot_filtr()));

    slot_filtr();
    main_lay->addWidget(lab, 0, 0);
    main_lay->addWidget(years, 1, 0);
    main_lay->addWidget(view, 2, 0);
    QPushButton *my_add = new QPushButton("Добавить");
    QObject::connect(my_add, SIGNAL(clicked()), view, SLOT(slot_add()));
    QPushButton *my_ok = new QPushButton("Готово");
    QObject::connect(my_ok, SIGNAL(clicked()), this, SLOT(accept()));
    main_lay->addWidget(my_add, 3, 0);
    main_lay->addWidget(my_ok, 4, 0);
    setLayout(main_lay);
}
void editor_hollydays::slot_filtr()
{
    QRegExp rexp;
    rexp.setPatternSyntax(QRegExp::Wildcard);
    QString str{""};
    if (years->currentText() == "Все годы"){
        str = "*";
    } else {
        str = "*" + years->currentText().right(8).left(4);
    }
    rexp.setPattern(str);
    QSortFilterProxyModel* prmod = new QSortFilterProxyModel();
    view->setModel(prmod);
    prmod->setFilterKeyColumn(0);
    prmod->setFilterRegExp(rexp);
    prmod->setSourceModel(model);
    view->scrollToBottom();
}
// Представление для дат ------------------------------------------------------------------------------------------------
hollydays_view::hollydays_view(editor_hollydays* call, QWidget *par) : QListView (par)
{
    call_back = call;
}
void hollydays_view::mousePressEvent(QMouseEvent *arg)
{
    if ((arg->buttons() == Qt::RightButton)){
        QMenu *mnu = new QMenu(this);
        mnu->setEnabled(true);
        if (this->indexAt(arg->pos()).isValid()) {
            curs = arg->pos();
            QAction *add_obj = new QAction("Добавить дату", this);
            QObject::connect(add_obj, SIGNAL(triggered()), this, SLOT(slot_add()));
            QAction *del_obj = new QAction("Удалить дату", this);
            QObject::connect(del_obj, SIGNAL(triggered()), this, SLOT(slot_del()));
            mnu->addAction(del_obj);
            mnu->addAction(add_obj);
        } else {
            QAction *ed_doc = new QAction("Добавить дату", this);
            QObject::connect(ed_doc, SIGNAL(triggered()), this, SLOT(slot_add()));
            mnu->addAction(ed_doc);
    }
        mnu->popup(arg->globalPos());
        mnu->show();
    }
    QListView::mousePressEvent(arg);
}
void hollydays_view::mouseDoubleClickEvent(QMouseEvent* arg)
{
    slot_add();
    QListView::mouseDoubleClickEvent(arg);
}
void hollydays_view::slot_add()
{
    input_date* eddat = new input_date();
    if (eddat->exec() == QDialog::Accepted){
        model()->setData(QModelIndex(), QVariant::fromValue(eddat->result()), Qt::EditRole);
    }
    call_back->slot_filtr();
    delete eddat;
}
void hollydays_view::slot_del()
{
    model()->removeRow(this->indexAt(curs).row(), QModelIndex());
    call_back->slot_filtr();
}
void hollydays_view::slot_filtr()
{

}
// Модель для дат ------------------------------------------------------------------------------------------------
hollydays_model::hollydays_model(QObject *parent) : QAbstractListModel(parent)
{
    model_data = settings::getInatance().lst_holliday();
}
int hollydays_model::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return  model_data->count();
}
QVariant hollydays_model::data(const QModelIndex &index, int role) const
{
    if (index.isValid()){
    if (role == Qt::DisplayRole){
        if (index.row() < model_data->size()){
            return QVariant::fromValue(model_data->at(index.row()).toString("d.MMMM.yyyy"));
        }
    }
    if (role ==  Qt::EditRole) {
        if (index.row() < model_data->size()){
                    return QVariant::fromValue(model_data->at(index.row()));
        }
    }
    } return QVariant();
}
bool hollydays_model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(index)
    if (role == Qt::EditRole){
            settings::getInatance().add_hollyday(value.value<QDate>());
            return true;
    }
    return false;
}
QVariant hollydays_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section)
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal){
        return QVariant("Праздники");
    }
    return QVariant();
}
Qt::ItemFlags hollydays_model::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractListModel::flags(index);
    if( index.isValid() ) {
            flags |= Qt::ItemIsSelectable;
    } else flags |= Qt::ItemIsEnabled;
    return flags;
}
bool hollydays_model::removeRows(int row, int count, const QModelIndex & parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = row; i < row + count; i++){
        settings::getInatance().del_holliday(model_data->at(row));
     }
     endRemoveRows();
     this->layoutChanged();
     return true;
}
// Диалогове окно для ввода даты
input_date::input_date(const QDate& dat)
{
    this->setWindowTitle("Выберите дату");
    this->setWindowIcon(QIcon(":/images/w.png"));
    QGridLayout* main_lay = new QGridLayout();
    dated = new QDateEdit();
    dated->setDate(dat);
    QLabel* lab = new QLabel();
    lab->setText("Выберите дату:");
    QPushButton *my_ok = new QPushButton("Готово");
    QObject::connect(my_ok, SIGNAL(clicked()), this, SLOT(slot_ok()));
    QPushButton *my_cancel = new QPushButton("Отмена");
    QObject::connect(my_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    main_lay->addWidget(lab, 0, 0);
    main_lay->addWidget(dated, 0, 1);
    main_lay->addWidget(my_ok, 1, 0);
    main_lay->addWidget(my_cancel, 1, 1);
    setLayout(main_lay);
}
input_date::~input_date()
{
    delete  dated;
}
QDate input_date::result() const
{
    return  dated->date();
}
void input_date::slot_ok()
{
    emit accept();
}
