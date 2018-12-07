#ifndef FILTR_H
#define FILTR_H
#include <QDialog>
#include <QObject>
#include <utility>
#include <tuple>
class QLineEdit;
// Собственно фильтр
class filtr : public QDialog
{
    Q_OBJECT
public:
    filtr(QWidget* par = nullptr);
    ~filtr();
    QString result() const;
public slots:
    void slot_fltr();
public:
    QLineEdit* kli;   // ФИО
};
// Меню выбора высоты и ширины ячейки с фото
class size_select : public QDialog
{
    Q_OBJECT
public:
    size_select(int weidth, int heidth, QWidget* par = nullptr);
    ~size_select();
    std::pair<int, int> result() const;
public slots:
    void slot_set();
public:
    QLineEdit* ed_weidth;
    QLineEdit* ed_heidth;
};
// Меню настройки номера порта сервера и пароля для доступа;
class server_set : public QDialog
{
    Q_OBJECT
public:
    server_set(quint16 port_, const QString& pass_, QWidget* par = nullptr);
    ~server_set();
    std::pair<quint16, QString> result() const;
public slots:
    void slot_set();
public:
    QLineEdit* ed_pass;
    QLineEdit* ed_port;
};
#endif // FILTR_H
