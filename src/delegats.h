#ifndef DELEGATS_H
#define DELEGATS_H
#include <QStyledItemDelegate>

class show_delegat : public QStyledItemDelegate
{
    Q_OBJECT
public:
    show_delegat(QObject *parent = nullptr);
    void updateEditorGeometry(QWidget *lab, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const;
};
class pic_delegat : public QStyledItemDelegate
{
    Q_OBJECT
public:
    pic_delegat(QObject *parent = nullptr);
    void updateEditorGeometry(QWidget *lab, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const;
};
#endif // DELEGATS_H
