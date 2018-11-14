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
QString im_hash(const QImage& arg)
{
    QString ret{""};
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
    ret = QString::number(hash);
    return ret;
}
