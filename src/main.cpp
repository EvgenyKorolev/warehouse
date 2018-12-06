#include "mainwindow.h"
#include "settings.h"
#include "proxy_data.h"
#include "server.h"
#include <QSplashScreen>
#include <QApplication>
#include <QObject>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen splash(QPixmap(":/images/s.png"));
    splash.show();
    settings::getInatance();
    proxy_data::getInstance();
    server my_server(6666, &proxy_data::getInstance(), &settings::getInatance());
    MainWindow w;
    QObject::connect(&my_server, SIGNAL(res()), &w, SLOT(slot_def_filtr();));
    splash.finish(&w);
    w.show();
    return a.exec();
}
