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
    void slot_filtr_reg(const QString& arg, int col);
    void slot_filtr_str(const QString& arg, int col);
public slots:
    void slot_hol();
    void slot_def_filtr();
    void slot_about();
    void slot_set_pic();
    void slot_search();
    void slot_all();
    void slot_opl();
private:
    lst_view* view;
    lst_model* model;
    QLabel* PicLabel;
};

#endif // MAINWINDOW_H
