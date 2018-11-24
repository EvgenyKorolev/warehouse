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
    QLineEdit* ed_name;         // Имя
    QLineEdit* ed_surname;      // Фамилия
    QLineEdit* ed_fname;        // Отчество
    QDateEdit* ed_start_data;   // Дата сдачи на хранение
    QTextEdit* ed_info;         // Доп. информация
    QSpinBox* cost;             // Стоимость в сутки
    QSpinBox* dop_cost;         // Стоимость дополнительных услуг
    QImage actual_img;         // Фотография

    QGraphicsScene* main_scene; // Сцена для фото
    QGraphicsView* main_view;   // Вьюха для фото
    persisted_object data;      // Внутренний объект
};
#endif // EDITOR_OBJECT_H
