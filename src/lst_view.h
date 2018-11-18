#ifndef LST_VIEW_H
#define LST_VIEW_H
#include <QObject>
#include <QTableView>
#include <QMouseEvent>

class lst_view : public QTableView
{
    Q_OBJECT
public:
    lst_view(QWidget *par = nullptr);
    void mousePressEvent(QMouseEvent *arg);
    void mouseDoubleClickEvent(QMouseEvent* arg);
public slots:
    void slot_add();
    void slot_edit();
    void slot_del();
    void slot_filtr();
private:
    QPoint curs;   // Запоминаем местоположение курсора
};

#endif // LST_VIEW_H
