#ifndef DELEGATS_H
#define DELEGATS_H
#include <QStyledItemDelegate>

class show_delegat : public QStyledItemDelegate
{
    Q_OBJECT
public:
    show_delegat(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *lab, const QModelIndex &index) const;
    void setModelData(QWidget *lab, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *lab, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // DELEGATS_H
