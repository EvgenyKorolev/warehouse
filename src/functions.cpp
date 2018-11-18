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

