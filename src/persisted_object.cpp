#include "settings.h"
#include "functions.h"
#include "persisted_object.h"
#include <QPainter>
#include <QDateTime>
#include <QDir>
persisted_object::persisted_object(const persisted_object* arg)
{
    person = arg->person;
    start_data = arg->start_data;
    pay_data = arg->pay_data;
    info = arg->info;
    cost = arg->cost;
    dop_cost = arg->dop_cost;
    many = arg->many;
    closed = arg->closed;
    uniq = arg->uniq;
    foto = arg->foto;
    hash = arg->hash;
    nll = arg->nll;
}
persisted_object::persisted_object(const persisted_object& arg)
{
    person = arg.person;
    start_data = arg.start_data;
    pay_data = arg.pay_data;
    info = arg.info;
    cost = arg.cost;
    dop_cost = arg.dop_cost;
    many = arg.many;
    closed = arg.closed;
    uniq = arg.uniq;
    foto = arg.foto;
    hash = arg.hash;
    nll = arg.nll;
}
persisted_object& persisted_object::operator=(const persisted_object& arg)
{
    person = arg.person;
    start_data = arg.start_data;
    pay_data = arg.pay_data;
    info = arg.info;
    cost = arg.cost;
    dop_cost = arg.dop_cost;
    many = arg.many;
    closed = arg.closed;
    uniq = arg.uniq;
    foto = arg.foto;
    hash = arg.hash;
    nll = arg.nll;
    return *this;
}
QString persisted_object::get_text() const
{
    return std::get<0>(person) + " " + std::get<1>(person) + " " + std::get<2>(person) + " \n" + "Оставлено: " + start_data.toString("dd.MMMM.yyyy") +
            "г. \n" + "Текущая стоимость: " + QString::number(today_cost()) + "руб.";
}
QImage persisted_object::get_foto() const
{
    QImage ret = QImage(settings::getInatance().get_image_dir() + foto, "png");
    if (ret.isNull()) return QImage(":/images/nophoto.png", "png");
    if (im_hash(ret) != hash){
        QImage img = QImage(":/images/no.png", "png");
        QPainter p1(&ret);
        p1.drawImage(10,10,img);
        p1.end();
    }
    return ret;
}
unsigned persisted_object::get_pay() const
{
    return settings::getInatance().work_days(start_data);
}
qint32 persisted_object::im_hash(const QImage& arg) const
{
    qint32 hash{0};
    for(int y{0}; y < arg.height(); y++)
    {
        for(int x{0}; x < arg.width(); x++)
        {
            QRgb pixel = arg.pixel(x,y);
            hash += pixel;
            hash += (hash << 10);
            hash ^= (hash >> 6);
        }
    }
    return hash;
}
bool persisted_object::operator==(const persisted_object& arg)
{
    return (std::get<0>(person) == std::get<0>(arg.person) &&
            std::get<1>(person) == std::get<1>(arg.person) &&
            std::get<2>(person) == std::get<2>(arg.person) &&
            start_data == arg.start_data &&
            info == arg.info &&
            cost == arg.cost &&
            dop_cost == arg.dop_cost &&
            uniq == arg.uniq &&
            hash == arg.hash);
}
bool persisted_object::operator!=(const persisted_object& arg)
{
    return !(*this == arg);
}
void persisted_object::close()
{
    settings& tmps = settings::getInatance();
    QDate tmp = start_data;
    while (tmp <= QDate::currentDate()){
        if (!tmps.is_hollyday(tmp) && tmp.dayOfWeek() != 6 && tmp.dayOfWeek() != 7) many += cost;
        tmp = tmp.addDays(1);
    }
    many += dop_cost;
    pay_data = QDate::currentDate();
    closed = true;
}
unsigned persisted_object::today_cost() const
{
    settings& tmps = settings::getInatance();
    unsigned ret{0};
    QDate tmp = start_data;
    if (closed) return many;
    while (tmp <= QDate::currentDate()){
        if (!tmps.is_hollyday(tmp) && tmp.dayOfWeek() != 6 && tmp.dayOfWeek() != 7) ret += cost;
        tmp = tmp.addDays(1);
    }
    ret += dop_cost;
    return ret;
}
QString persisted_object::str_closed()
{
    if (is_closed()) return "Да";
    return "-";
}
bool persisted_object::add_photo(const QImage& arg)
{
    hash = im_hash(arg);
    QDir dr;
    if (foto != "") {
        dr.mkpath(settings::getInatance().get_image_dir() + foto.left(foto.indexOf("/") + 1));
        return arg.save(settings::getInatance().get_image_dir() + foto);
    } else {
        dr.mkpath(settings::getInatance().get_image_dir() + QString::number(QDate::currentDate().dayOfYear()));
        foto = QString::number(QDate::currentDate().dayOfYear()) + "/" + uniq + ".png";
        return arg.save(settings::getInatance().get_image_dir() + foto);
    }
}
QJsonObject persisted_object::make_json() const
{
    QJsonObject ret;
    ret.insert("name", QJsonValue(std::get<0>(person)));
    ret.insert("surname", QJsonValue(std::get<1>(person)));
    ret.insert("fname", QJsonValue(std::get<2>(person)));
    ret.insert("start_data", QJsonValue(QString::number(QDateTime(start_data).toMSecsSinceEpoch())));
    ret.insert("pay_data", QJsonValue(QString::number(QDateTime(pay_data).toMSecsSinceEpoch())));
    ret.insert("info", QJsonValue(info));
    ret.insert("cost", QJsonValue(QString::number(cost)));
    ret.insert("dop_cost", QJsonValue(QString::number(dop_cost)));
    ret.insert("many", QJsonValue(QString::number(many)));
    if (closed){
            ret.insert("closed", QJsonValue("true"));
    } else {
            ret.insert("closed", QJsonValue("false"));
    }
    ret.insert("uniq", QJsonValue(uniq));
    ret.insert("foto", QJsonValue(foto));
    ret.insert("hash", QJsonValue(QString::number(hash)));
    return ret;
}
void persisted_object::load_json(const QJsonObject& arg)
{
    person = std::make_tuple(arg.value("name").toString(), arg.value("surname").toString(), arg.value("fname").toString());
    QDateTime tmpd;
    tmpd.setMSecsSinceEpoch(arg.value("start_data").toString().toLongLong());
    start_data =  tmpd.date();
    tmpd.setMSecsSinceEpoch(arg.value("pay_data").toString().toLongLong());
    pay_data = tmpd.date();
    info = arg.value("info").toString();
    cost = static_cast<unsigned int>(arg.value("cost").toInt());
    dop_cost = static_cast<unsigned int>(arg.value("dop_cost").toInt());
    many = static_cast<unsigned int>(arg.value("manu").toInt());
    if (arg.value("closed").toString() == "true"){
       closed = true;
    } else {
       closed = false;
    }
    uniq = arg.value("uniq").toString();
    //foto = arg.value("foto").toString();
    hash = arg.value("hash").toString().toInt();
}
