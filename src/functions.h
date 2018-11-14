#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <QString>
#include <QImage>
namespace my {
QString base64_plus(const QString& arg);
QString base64_minus(const QString& arg);
QString base64_plus(const QString&& arg);
QString base64_minus(const QString&& arg);
QString im_hash(const QImage& arg);
}
#endif // FUNCTIONS_H
