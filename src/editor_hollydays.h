#ifndef EDITOR_HOLLYDAYS_H
#define EDITOR_HOLLYDAYS_H
#include <QDialog>
#include <QObject>
#include <QVariant>
#include <QAbstractListModel>
#include <QListView>
#include <QDate>
#include <memory>
class hollydays_model;
class hollydays_view;
class QComboBox;
class editor_hollydays : public QDialog
{
    Q_OBJECT
public:
    editor_hollydays(QWidget* par = nullptr);
public slots:
    void slot_filtr();
private:
    hollydays_model* model;
    hollydays_view* view;
    QComboBox* years;
};
// Представление для дат
class hollydays_view : public QListView
{
    Q_OBJECT
public:
    hollydays_view(editor_hollydays* call, QWidget *par = nullptr);
    void mousePressEvent(QMouseEvent *arg);
    void mouseDoubleClickEvent(QMouseEvent* arg);
public slots:
    void slot_add();
    void slot_del();
    void slot_filtr();
private:
    editor_hollydays* call_back;
    QPoint curs;   // Запоминаем местоположение курсора
};
// Модель для дат
class hollydays_model : public QAbstractListModel
{
public:
    hollydays_model(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());
private:
    std::shared_ptr<QVector<QDate>> model_data;
};
// Диалогове окно для ввода даты
class QDateEdit;
class input_date : public QDialog
{
    Q_OBJECT
public:
    input_date(const QDate& dat = QDate(2018, 1, 1));
    ~input_date();
    QDate result() const;
public slots:
    void slot_ok();
private:
    QDateEdit* dated;
};
#endif // EDITOR_HOLLYDAYS_H
