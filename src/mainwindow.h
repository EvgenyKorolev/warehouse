#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
class lst_model;
class lst_view;
class QCloseEvent;
class QLabel;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void closeEvent(QCloseEvent* event);
    void slot_filtr(const QString& arg);
public slots:
    void slot_hol();
    void slot_def_filtr();
    void slot_about();
    void slot_set_pic();
    void slot_search();
private:
    lst_view* view;
    lst_model* model;
    QLabel* PicLabel;
};

#endif // MAINWINDOW_H
