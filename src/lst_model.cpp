#include "lst_model.h"

lst_model::lst_model(const proxy_data& arg, QObject *parent) : QAbstractTableModel(parent)
{
    model_data = arg;
}
int lst_model::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return  model_data.count();
}
int lst_model::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 3;
}
QVariant lst_model::data(const QModelIndex &index, int role) const
{
    if (index.isValid()){
    if (role == Qt::DisplayRole){
        if (index.column() == 0){
            return QVariant::fromValue(model_data.at(static_cast<std::size_t>(index.row()))->get_foto());
        }
        if (index.column() == 1){
            return QVariant::fromValue(model_data.at(static_cast<std::size_t>(index.row()))->get_text());
        }
    }
    if (role ==  Qt::EditRole) {
        return QVariant::fromValue(model_data.at(static_cast<std::size_t>(index.row())));

    }
    }
    return QVariant();
}
bool lst_model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole){
        if (!index.isValid()){
            model_data.append(value.value<std::shared_ptr<persisted_object>>());
            return true;
        } else {
            model_data.insert(static_cast<std::size_t>(index.row()), value.value<std::shared_ptr<persisted_object>>());
            return true;
        }
    }
    return false;
}
QVariant lst_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal){
        switch (section){
        case 0:
            return QVariant("Фото");
        case 1:
            return QVariant("Сведения");
        }
    }
    return QVariant();
}
Qt::ItemFlags lst_model::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if( index.isValid() ) {
            flags |= Qt::ItemIsSelectable;
    }
    return flags;
}
