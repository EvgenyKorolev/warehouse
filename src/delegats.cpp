#include "delegats.h"
#include <QLabel>
#include <QPainter>
show_delegat::show_delegat(QObject *parent) : QStyledItemDelegate(parent){}
void show_delegat::updateEditorGeometry(QWidget* lab, const QStyleOptionViewItem& option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    lab->setGeometry(option.rect);
}
void show_delegat::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
   painter->drawText(option.rect, index.model()->data(index).toString());
}
