#include "mainwindow.h"
#include "settings.h"
#include <QSplashScreen>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen splash(QPixmap(":/images/s.png"));
    splash.show();
    settings::getInatance();
    MainWindow w;
    splash.finish(&w);
    w.show();
    return a.exec();
}
