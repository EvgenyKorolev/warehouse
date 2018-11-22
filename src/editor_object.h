#ifndef EDITOR_OBJECT_H
#define EDITOR_OBJECT_H
#include "persisted_object.h"
#include <QObject>
#include <QDialog>
class QLineEdit;
class QGraphicsScene;
class QGraphicsView;
class QTextEdit;
class QSpinBox;
class QDateEdit;
class editor_object : public QDialog
{
    Q_OBJECT
public:
    editor_object(const persisted_object&, QWidget* par = nullptr);
    editor_object(QWidget* par = nullptr);
    ~editor_object();
    persisted_object result();
public slots:
    void slot_save();
private:
    void init();
    QLineEdit* ed_name;
    QLineEdit* ed_surname;
    QLineEdit* ed_fname;
    QDateEdit* ed_start_data;
    QTextEdit* ed_info;
    QSpinBox* cost;
    QSpinBox* dop_cost;
    QGraphicsScene* main_scene;
    QGraphicsView* main_view;
    QPixmap actual_img;
    persisted_object data;
};

#endif // EDITOR_OBJECT_H


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
//qint32 hash; // Хэш фотографии
