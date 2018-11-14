#include "settings.h"
#include "persisted_object.h"
QString persisted_object::get_text() const
{
    return std::get<0>(person) + std::get<1>(person) + std::get<2>(person) + "\n" + "Оставлено: " + start_data.toString() +
            "\n" + "Текущая стоимость: " + QString::number(get_pay()) + "руб.";

}
QImage persisted_object::get_foto() const
{

}
unsigned persisted_object::get_pay() const
{
    return settings::getInatance().work_days(start_data);
}

//std::tuple<QString, QString, QString> person; // Данные клиента
//QDate start_data; // Дата начала хранения
//QDate pay_data; // Дата окончания хранения (оплаты)
//QString info;   // Дополнительная информация
//unsigned cost;  // Стоимость в сутки
//unsigned dop_cost;   // Стоимость допуслуг
//unsigned many;
//bool closed;
//size_t uniq;
//QString foto; // файл фотографии
//QString hash; // Хэш фотографии
