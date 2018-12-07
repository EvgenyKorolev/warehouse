#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <vector>
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
    void slot_change_columns();
    void slot_reset_doc();
    void slot_size_chenge();
    void slot_serv_set();
private:
    void hide_columns();
    void set_flag(int, bool);
    lst_view* view;
    lst_model* model;
    QLabel* PicLabel;
    QDockWidget *view_area;
    std::vector<bool> t_status;
    QAction* column0;
    QAction* column1;
    QAction* column2;
    QAction* column3;
    QAction* column4;
    QAction* column5;
    QAction* column6;
    QAction* column7;
    QAction* column8;
    QAction* column9;
    QAction* doc;
};

#endif // MAINWINDOW_H
