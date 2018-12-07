#include "functions.h"
QString my::base64_plus(const QString& arg)
{
    QString ret{""};
    QByteArray retar;
    retar.append(arg);
    retar = retar.toBase64();
    ret = retar;
    return ret;
}
QString my::base64_plus(const QString&& arg)
{
    QString ret{""};
    QByteArray retar;
    retar.append(arg);
    retar = retar.toBase64();
    ret = retar;
    return ret;
}
QString my::base64_minus(const QString& argx)
{
    QByteArray retar;
    QByteArray retar2;
    retar2.append(argx);
    retar = QByteArray::fromBase64(retar2);
    QString arg(retar);
    return arg;
}
QString my::base64_minus(const QString&& argx)
{
    QByteArray retar;
    QByteArray retar2;
    retar2.append(argx);
    retar = QByteArray::fromBase64(retar2);
    QString arg(retar);
    return arg;
}
QJsonObject my::parse_str(const QString&& arg)
{
    QJsonObject ret;

    return ret;
}



//QJsonObject ret;
//ret.insert("name", QJsonValue(std::get<0>(person)));
//ret.insert("surname", QJsonValue(std::get<1>(person)));
//ret.insert("fname", QJsonValue(std::get<2>(person)));
//ret.insert("start_data", QJsonValue(QString::number(QDateTime(start_data).toMSecsSinceEpoch())));
//ret.insert("pay_data", QJsonValue(QString::number(QDateTime(pay_data).toMSecsSinceEpoch())));
//ret.insert("info", QJsonValue(info));
//ret.insert("cost", QJsonValue(QString::number(cost)));
//ret.insert("dop_cost", QJsonValue(QString::number(dop_cost)));
//ret.insert("many", QJsonValue(QString::number(many)));
//if (closed){
//        ret.insert("closed", QJsonValue("true"));
//} else {
//        ret.insert("closed", QJsonValue("false"));
//}
//ret.insert("uniq", QJsonValue(uniq));
// //ret.insert("foto", QJsonValue(foto)); // В текущей реализации фото вытягивается отдельно, надо помнить об этом :(
//ret.insert("hash", QJsonValue(QString::number(hash)));
//return ret;
//}
//void persisted_object::load_json(const QJsonObject& arg)
//{
//person = std::make_tuple(arg.value("name").toString(), arg.value("surname").toString(), arg.value("fname").toString());
//QDateTime tmpd;
//tmpd.setMSecsSinceEpoch(arg.value("start_data").toString().toLongLong());
//start_data =  tmpd.date();
//tmpd.setMSecsSinceEpoch(arg.value("pay_data").toString().toLongLong());
//pay_data = tmpd.date();
//info = arg.value("info").toString();
//cost = static_cast<unsigned int>(arg.value("cost").toInt());
//dop_cost = static_cast<unsigned int>(arg.value("dop_cost").toInt());
//many = static_cast<unsigned int>(arg.value("manu").toInt());
//if (arg.value("closed").toString() == "true"){
//   closed = true;
//} else {
//   closed = false;
//}
//uniq = arg.value("uniq").toString();
// //foto = arg.value("foto").toString(); // В текущей реализации фото добавляется отдельно, надо помнить об этом :(
//hash = arg.value("hash").toString().toInt();
