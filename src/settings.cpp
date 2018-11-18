#include "settings.h"
#include "functions.h"
#include <QSqlRecord>

settings::settings()
{
    bool parse{true};
    QString ini{""};
    if (QFile(".warehouse.conf").exists()){
        main_ini = ".warehouse.conf";
    } else if (QFile(QDir::homePath() + "/.warehouse/.warehouse.conf").exists()){
        main_ini = QDir::homePath() + "/.warehouse/.warehouse.conf";
    } else if (QFile(QDir::homePath() + "/.warehouse.conf").exists()){
        main_ini = QDir::homePath() + "/.warehouse.conf";
    } else {
        db_dir = QDir::homePath() + "/.warehouse/";
        image_dir = db_dir + "images/";
        main_ini = QDir::homePath() + "/.warehouse.conf";
        db_name = "data.db3";
        parse = false;
        if(!save_ini()) QMessageBox::information(nullptr, "Ошибка", "Не могу создать файл с настройками");
    }
    if (parse){
        QFile ini_f(main_ini);
        if (ini_f.open(QIODevice::ReadOnly)){
            QTextStream stream(&ini_f);
            ini = stream.readAll();
            ini_f.close();
            int st = ini.indexOf("db_dir = ") + 9;
            int sst = ini.indexOf('\n', st);
            db_dir = ini.mid(st, sst - st);
            st = ini.indexOf("image_dir = ") + 12;
            sst = ini.indexOf('\n', st);
            image_dir = ini.mid(st, sst - st);
            st = ini.indexOf("db_name = ") + 10;
            sst = ini.indexOf('\n', st);
            db_name = ini.mid(st, sst - st);
        } else {
            QMessageBox::information(nullptr, "Отладка", "Не открывается файл с настройками");
        }
    }
    QFile tester(db_dir + db_name);
    if (!tester.exists()){
        create_base();
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(db_dir + db_name);
        if(!db.open()){
            QMessageBox::information(nullptr, "Внимание", "База данных не открывается");
        }
    }
    QDir tmpd;
    if (!tmpd.exists(db_dir)){
        QMessageBox::information(nullptr, "Внимание", "Невозможно найти или сохранить путь к директории с данными");
    }
}
bool settings::save_ini() const
{
    QFile f_ini(main_ini);
    if(f_ini.open(QIODevice::WriteOnly)){
        QString ini = "db_dir = " + db_dir + "\n" + "image_dir = " + image_dir + "\n" +  "db_name = " + db_name + "\n";
        QTextStream stream(&f_ini);
        stream << ini;
        f_ini.close();
        return true;
    }
    return false;
}
unsigned settings::work_days(const QDate& arg) const
{
    QDate tmp = arg;
    unsigned ret{0};
    if (tmp >= QDate::currentDate()) return ret;
    while (tmp != QDate::currentDate()){
        if (tmp.dayOfWeek() != 6 || tmp.dayOfWeek() != 7 || !is_hollyday(tmp)) ++ret;
        tmp = tmp.addDays(1);
    }
    return ret;
}
void settings::create_base()
{
    QDir my_dir(db_dir);
    my_dir.mkpath(db_dir);
    my_dir.mkdir(image_dir);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(db_dir + db_name);
    if(!db.open()){ QMessageBox::information(nullptr, "Внимание", "База данных не открывается");}
    QSqlQuery query(db);
    QString prep = "CREATE TABLE persisted(kl_name TEXT, kl_surname TEXT, kl_fname TEXT,"
                   "start_data INTEGER, pay_data INTEGER, info TEXT, cost INTEGER, "
                   "dop_cost INTEGER, many INTEGER, closed TEXT, uniq INTEGER UNIQUE NOT NULL,"
                   "foto_name TEXT, hash TEXT, inq INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL);";
    if (!query.exec(prep)) {
        QMessageBox::information(nullptr, "Внимание", "База данных пуста и не удается создать таблицу persisted");
    }
    prep = "CREATE TABLE hollydays (hollyday INTEGER UNIQUE NOT NULL);";
    if (!query.exec(prep)) {
        QMessageBox::information(nullptr, "Внимание", "База данных пуста и не удается создать таблицу hollydays");
    }
}
bool settings::db_execute(const QString& str_query, const QString& str_info)
{
    QSqlQuery query(db);
    if (!query.exec(str_query)){
        QMessageBox::information(nullptr, "Внимание",  str_info);
        return false;
    }
    return true;
}
std::unique_ptr<persisted_object> settings::request_data(const QString& str_query)
{
    QSqlQuery query(db);
    QSqlRecord rec;
    if (!query.exec(str_query)){
        return std::make_unique<persisted_object>(new persisted_object());
    }
    std::unique_ptr<persisted_object> ret = std::make_unique<persisted_object>(persisted_object());
    query.first();
    rec = query.record();
    QDateTime pay_dat, start_dat;
    start_dat.setMSecsSinceEpoch(query.value(rec.indexOf("start_data")).value<qint64>());
    pay_dat.setMSecsSinceEpoch(query.value(rec.indexOf("pay_data")).value<qint64>());
    ret->set_person(std::make_tuple(my::base64_minus(query.value(rec.indexOf("kl_name")).toString()), my::base64_minus(query.value(rec.indexOf("kl_surname")).toString()),
                                    my::base64_minus(query.value(rec.indexOf("kl_fname")).toString())));
    ret->set_start_data(pay_dat.date());
    ret->set_pay_data(start_dat.date());
    ret->set_info(my::base64_minus(query.value(rec.indexOf("info")).toString()));
    ret->set_cost(query.value(rec.indexOf("cost")).toUInt());
    ret->set_dop_cost(query.value(rec.indexOf("dop_cost")).toUInt());
    ret->set_foto_name(my::base64_minus(query.value(rec.indexOf("foto_name")).toString()));
    ret->set_hash(qint32(query.value(rec.indexOf("hash")).toULongLong()));
    ret->set_many(query.value(rec.indexOf("many")).toUInt());
    if (my::base64_minus(query.value(rec.indexOf("closed")).toString()) == "true"){
        ret->set_close();
    } else ret->unset_close();
    ret->set_uniq(query.value(rec.indexOf("hash")).toULongLong());
    return ret;
}
bool settings::is_hollyday(const QDate&) const
{
    QSqlQuery query(db);
    QSqlRecord rec;
    if (!query.exec("SELECT * FROM persisted;")){
        return false;
    }
    rec = query.record();
    query.first();
    QDateTime hol_dat;
    if (query.value(rec.indexOf("hollyday")).value<qint64>() != 0) return true;
    return false;
}
bool settings::add_hollyday(const QDate& arg)
{
    QDateTime hol_data(arg);
    QString prep = "INSERT INTO hollydays(hollyday) VALUES ('" + QString::number(hol_data.toMSecsSinceEpoch()) + "');";
            if (db_execute(prep, "Что-то не то с добавлением праздника в базу данных.")) return true;
            return false;
}
bool settings::del_holliday(const QDate& arg)
{
    QDateTime hol_data(arg);
    QString prep = "DELETE hollydays * WHERE hollyday ='" + QString::number(hol_data.toMSecsSinceEpoch()) + "';";
    if (db_execute(prep, "Что-то не то с удалением праздника из базы данных.")) return true;
    return false;
}
