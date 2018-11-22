#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
class lst_model;
class lst_view;
class QCloseEvent;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);
public slots:
    void slot_hol();
private:
    lst_view* view;
    lst_model* model;
};

#endif // MAINWINDOW_H
