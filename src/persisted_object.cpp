#include "settings.h"
#include "functions.h"
#include "persisted_object.h"
#include <QPainter>
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
    return std::get<0>(person) + std::get<1>(person) + std::get<2>(person) + "<br>" + "Оставлено: " + start_data.toString() +
            "<br>" + "Текущая стоимость: " + QString::number(get_pay()) + "руб.";
}
QImage persisted_object::get_foto() const
{
    QImage ret = QImage(settings::getInatance().get_image_dir() + foto + ".png", "png");
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

}
