#ifndef PERSISTED_OBJECT_H
#define PERSISTED_OBJECT_H
#include <tuple>
#include <QDate>
#include <memory>
#include <QVariant>
#include <QImage>
#include <QString>
#include <random>
class persisted_object
{
public:
    persisted_object() : person{std::make_tuple("", "", "")},
        start_data{QDate()}, pay_data{QDate()}, info{""}, cost{0},
        dop_cost{0}, many{0}, closed{false}, foto{""}, hash{0}, nll(true){
        uniq = QString::number(QDateTime::currentSecsSinceEpoch());
        std::random_device gensc;
        std::mt19937 gen;
        gen.seed(gensc());
        uniq += QString::number(gen());
    }
    ~persisted_object() = default;
    persisted_object(const persisted_object&) = default;
    persisted_object(const persisted_object*);
    persisted_object(persisted_object&&) = default;
    persisted_object& operator=(const persisted_object&) = default;
    persisted_object& operator=(persisted_object&& arg) = default;
    bool operator==(const persisted_object&);
    bool operator!=(const persisted_object&);

    void set_person(const std::tuple<QString, QString, QString>& arg){person = arg;}
    std::tuple<QString, QString, QString> get_person() const{return person;}
    void set_start_data(const QDate& arg) {start_data = arg;}
    QDate get_start_data() const{return start_data;}
    void set_pay_data(const QDate& arg) {pay_data = arg;}
    QDate get_pay_data() const{return  pay_data;}
    void set_info(const QString& arg){info = arg;}
    QString get_info() const{return  info;}
    void set_cost(unsigned arg){cost = arg;}
    unsigned get_cost() const{return cost;}
    void set_dop_cost(unsigned arg){dop_cost = arg;}
    unsigned get_dop_cost() const{return dop_cost;}
    QString get_foto_name() const{return  foto;}
    void set_foto_name(const QString& arg){foto = arg;}
    qint32 get_hash() const{return  hash;}
    void set_hash(qint32 arg){hash = arg;}

    QString get_text() const;
    QImage get_foto() const;
    unsigned get_pay() const;

    bool is_null() const {return nll;}
    void not_null(){nll = false;}
    unsigned today_cost() const;
    QString str_closed();

    qint32 im_hash(const QImage& arg) const;
    void set_many(unsigned arg){cost = arg;}
    unsigned get_many() const{return cost;}
    bool is_closed() const {return closed;}
    void unset_close(){closed = false;}
    void set_close(){closed = true;}
    void close();
    QString get_uniq() const {return uniq;}
    void set_uniq(const QString& arg) {uniq = arg;}
private:
    std::tuple<QString, QString, QString> person; // Данные клиента
    QDate start_data; // Дата начала хранения
    QDate pay_data; // Дата окончания хранения (оплаты)
    QString info;   // Дополнительная информация
    unsigned cost;  // Стоимость в сутки
    unsigned dop_cost;   // Стоимость допуслуг
    unsigned many;  // полная стоимость на моммент закрытия
    bool closed;  // Забрали ли объект
    QString uniq;  // Уникальный номер
    QString foto; // файл фотографии
    qint32 hash; // Хэш фотографии
    bool nll;
};
Q_DECLARE_METATYPE(persisted_object)
Q_DECLARE_METATYPE(std::shared_ptr<persisted_object>)
#endif // PERSISTED_OBJECT_H
