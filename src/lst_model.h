#ifndef LST_MODEL_H
#define LST_MODEL_H
#include "proxy_data.h"
#include <memory>
#include <QAbstractTableModel>

class lst_model : public QAbstractTableModel
{
public:
    lst_model(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());
private:
    proxy_data* model_data;
};

#endif // LST_MODEL_H
