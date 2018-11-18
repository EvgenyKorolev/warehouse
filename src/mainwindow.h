#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "lst_view.h"
#include "lst_model.h"
#include <QCloseEvent>
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QSortFilterProxyModel>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);
private:
    lst_view* view;
    lst_model* model;
};

#endif // MAINWINDOW_H
