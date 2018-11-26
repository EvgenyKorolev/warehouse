#include "proxy_data.h"
#include "functions.h"
#include <QSqlRecord>

proxy_data::proxy_data()
{
    settings& tmps = settings::getInatance();
    QSqlDatabase& db = tmps.get_db();
    QSqlQuery query(db);
    QSqlRecord rec;
    if (!query.exec("SELECT * FROM persisted;")){
         QMessageBox::information(nullptr, "Внимание", "Что-то не то с чтением базы данных");
    }
    while(query.next()){
        std::shared_ptr<persisted_object> ret = std::make_shared<persisted_object>(persisted_object());
        rec = query.record();
        QDateTime pay_dat, start_dat;
        start_dat.setMSecsSinceEpoch(query.value(rec.indexOf("start_data")).value<qint64>());
        pay_dat.setMSecsSinceEpoch(query.value(rec.indexOf("pay_data")).value<qint64>());
        ret->set_person(std::make_tuple(my::base64_minus(query.value(rec.indexOf("kl_name")).toString()), my::base64_minus(query.value(rec.indexOf("kl_surname")).toString()),
                                        my::base64_minus(query.value(rec.indexOf("kl_fname")).toString())));
        ret->set_start_data(start_dat.date());
        ret->set_pay_data(pay_dat.date());
        ret->set_info(my::base64_minus(query.value(rec.indexOf("info")).toString()));
        ret->set_cost(query.value(rec.indexOf("cost")).toUInt());
        ret->set_dop_cost(query.value(rec.indexOf("dop_cost")).toUInt());
        ret->set_foto_name(my::base64_minus(query.value(rec.indexOf("foto_name")).toString()));
        ret->set_hash(qint32(query.value(rec.indexOf("hash")).toULongLong()));
        ret->set_many(query.value(rec.indexOf("many")).toUInt());
        if (query.value(rec.indexOf("closed")).toString() == "true"){
            ret->set_close();
        } else ret->unset_close();
        ret->set_uniq(query.value(rec.indexOf("uniq")).toString());
        data.append(ret);
    }
}
int proxy_data::size() const {return data.size();};
int proxy_data::count() const {return data.count();};
std::shared_ptr<persisted_object> proxy_data::at(std::size_t arg) const
{
    return data.at(static_cast<int>(arg));
};
void proxy_data::append(std::shared_ptr<persisted_object> arg)
{
    settings& tmps = settings::getInatance();
    QDateTime start_data(arg->get_start_data());
    QDateTime pay_data(arg->get_pay_data());
    QString closed{"false"};
    if (arg->is_closed()) {closed = "true";}
    QString prep = "INSERT INTO persisted(kl_name, kl_surname, kl_fname, start_data, pay_data, info, cost, dop_cost, many, closed, uniq, foto_name, hash) VALUES ('" +
            my::base64_plus(std::get<0>(arg->get_person())) + "', '" + my::base64_plus(std::get<1>(arg->get_person())) + "', '" +
            my::base64_plus(std::get<2>(arg->get_person())) + "', '" + QString::number(start_data.toMSecsSinceEpoch()) + "', '" +
            QString::number(pay_data.toMSecsSinceEpoch()) + "', '" + my::base64_plus(arg->get_info()) + "', '" + QString::number(arg->get_cost()) + "', '" +
            QString::number(arg->get_dop_cost()) + "', '" + QString::number(arg->get_many()) + "', '" + closed + "', '" +
            arg->get_uniq()  + "', '" + my::base64_plus(arg->get_foto_name()) + "', '" + QString::number(arg->get_hash()) + "');";
            if (tmps.db_execute(prep, "Что-то не то с добавлением записи в базу данных.")) data.append(arg);
};
void proxy_data::insert(std::shared_ptr<persisted_object> arg)
{
    settings& tmps = settings::getInatance();
    QDateTime start_data(arg->get_start_data());
    QDateTime pay_data(arg->get_pay_data());
    QString closed{"false"};
    if (arg->is_closed()) {closed = "true";}
    QString prep = "UPDATE persisted SET kl_name = '" + my::base64_plus(std::get<0>(arg->get_person())) + "', kl_surname = '" +
            my::base64_plus(std::get<1>(arg->get_person())) + "', kl_fname = '" + my::base64_plus(std::get<2>(arg->get_person())) + "', start_data = '" +
            QString::number(start_data.toMSecsSinceEpoch()) + "', pay_data = '" + QString::number(pay_data.toMSecsSinceEpoch()) + "', info = '" +
            my::base64_plus(arg->get_info()) + "', cost = '" + QString::number(arg->get_cost()) + "', dop_cost = '" +
            QString::number(arg->get_dop_cost()) + "', many = '" + QString::number(arg->get_many()) + "', closed = '" + closed + "', foto_name = '" +
            my::base64_plus(arg->get_foto_name()) + "', hash = '" +
            QString::number(arg->get_hash()) + "' WHERE uniq ='" + arg->get_uniq() + "';";
    if (tmps.db_execute(prep, "Что-то не то с обновлением записи в базе данных.")){
        auto it = data.begin();
        while (it != data.end()){
            if ((*it)->get_uniq() == arg->get_uniq()){
               *it = arg;
                break;
            }
            ++it;
        }
    }
};
void proxy_data::insert(std::size_t row, std::shared_ptr<persisted_object> arg)
{
    Q_UNUSED(row)
    if (data.at(static_cast<int>(row))->get_uniq() != arg->get_uniq()){
        QMessageBox::information(nullptr, "Внимание", "При внесении изменений произошел конфликт индексов");
        return;
    }
    insert(arg);
}
void proxy_data::del(std::shared_ptr<persisted_object> arg)
{
    settings& tmps = settings::getInatance();
    QString prep = "DELETE FROM persisted WHERE uniq ='" + arg->get_uniq() + "';";
    if (tmps.db_execute(prep, "Что-то не то с удалением записи из базы данных.")){
        if (arg->get_fname() != ""){
            QFile fl(settings::getInatance().get_image_dir() + arg->get_foto_name());
            fl.remove();
        }
        auto it = data.begin();
        while (it != data.end()){
            if ((*it)->get_uniq() == arg->get_uniq()){
               data.erase(it);
                break;
            }
            ++it;
        }
    }
}
