#ifndef FILTR_H
#define FILTR_H
#include <QDialog>
#include <QObject>
#include <tuple>
class QLineEdit;
class filtr : public QDialog
{
    Q_OBJECT
public:
    filtr(QWidget* par = nullptr);
    QString result();
public slots:
    void slot_fltr();
public:
    QLineEdit* kli;   // ФИО
};

#endif // FILTR_H
