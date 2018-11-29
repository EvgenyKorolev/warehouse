#ifndef SETTINGS_H
#define SETTINGS_H
#include "persisted_object.h"
#include <QString>
#include <QSqlDatabase>
#include <QList>
#include <QFile>
#include <QDir>
#include <QDate>
#include <QTextStream>
#include <QSqlQuery>
#include <memory>
enum class win{one, two};
class settings
{
public:
    static settings& getInatance(){
        static settings _instance;
        return _instance;
    }
    int get_wight() {return wight;}
    bool is_hollyday(const QDate&) const;
    bool add_hollyday(const QDate&);
    bool del_holliday(const QDate&);
    std::shared_ptr<QVector<QDate>> lst_holliday();

    bool db_execute(const QString& str_query, const QString& str_info);
    std::unique_ptr<persisted_object> request_data(const QString& str_query);
    unsigned work_days(const QDate&) const;
    QSqlDatabase& get_db(){return db;}
    bool save_ini() const;
    QString get_main_ini() const {return  main_ini;}
    QString get_image_dir() const {return  image_dir;}
    QString get_db_dir() const {return  db_dir;}
    QString get_db_name() const {return  db_name;}
    void get_main_ini(const QString& arg){main_ini = arg;}
    void get_image_dir(const QString& arg){image_dir = arg;}
    void get_db_dir(const QString& arg){db_dir = arg;}
    void get_db_name(const QString& arg){db_name = arg;}
    win get_ws() const {return winstart;}
    void set_ws(win);
private:
    void create_base();

    settings();
    settings(const settings&);
    settings& operator=(const settings&);
// Переменные для хранения разных настроек
    QString main_ini{""};
    QString image_dir{""};
    QString db_dir{""};
    QString db_name{""};
    QSqlDatabase db;
    std::shared_ptr<QVector<QDate>> hollidays;
    win winstart;
    int wight{250};
};

#endif // SETTINGS_H
