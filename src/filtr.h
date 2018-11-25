#ifndef FILTR_H
#define FILTR_H
#include <QDialog>
#include <QObject>
class QLineEdit;
class QDateEdit;
class QComboBox;
class filtr : public QDialog
{
    Q_OBJECT
public:
    filtr(QWidget* par = nullptr);
public slots:
    void slot_fltr();
public:
    QLineEdit* kli;
    QDateEdit* dat;
    QComboBox* do_pos;
};

#endif // FILTR_H
