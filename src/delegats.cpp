#include "delegats.h"
#include <QLabel>

show_delegat::show_delegat(QObject *parent) : QStyledItemDelegate(parent){}
QWidget* show_delegat::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option); Q_UNUSED(index);
    QLabel *lab = new QLabel(parent);
    return lab;
}
void show_delegat::setEditorData(QWidget *lab, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QLabel *lined = static_cast<QLabel*>(lab);
    lined->setText(value);
}
void show_delegat::setModelData(QWidget *lab, QAbstractItemModel *model, const QModelIndex &index) const
{
    Q_UNUSED(lab) Q_UNUSED(model) Q_UNUSED(index)
}
void show_delegat::updateEditorGeometry(QWidget *lab, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    lab->setGeometry(option.rect);
}
