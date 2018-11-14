#include "settings.h"

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
    if (!tester.exists()){ create_base();}
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(db_dir + db_name);
    if(!db.open()){
        QMessageBox::information(nullptr, "Внимание", "База данных не открывается");
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
    QSqlDatabase temp_db = QSqlDatabase::addDatabase("QSQLITE");
    temp_db.setDatabaseName(db_dir + db_name);
    if(!temp_db.open()){ QMessageBox::information(nullptr, "Внимание", "База данных не открывается");}
    QSqlQuery query;
    QString prep = "CREATE TABLE persisted (kl_name TEXT NOT NULL, kl_surname TEXT NOT NULL, kl_fname TEXT NOT NULL,"
                   "start_data INTEGER, pay_data INTEGER, info TEXT, cost INTEGER, "
                   "dop_cost INTEGER, many INTEGER, closed TEXT, uniq INTEGER UNIQUE NOT NULL,"
                   "foto_name TEXT UNIQUE, hash TEXT, inq INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL);";
    if (!query.exec(prep)) {
        QMessageBox::information(nullptr, "Внимание", "База данных пуста и не удается создать таблицу persisted");
    }
    prep = "CREATE TABLE hollydays (hollyday INTEGER UNIQUE NOT NULL);";
    if (!query.exec(prep)) {
        QMessageBox::information(nullptr, "Внимание", "База данных пуста и не удается создать таблицу hollydays");
    }
    temp_db.close();
}
