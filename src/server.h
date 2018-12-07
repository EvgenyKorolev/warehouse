#ifndef SERVER_H
#define SERVER_H
#include <QObject>
#include <QSet>
#include <QMap>
class QTcpServer;
class QTcpSocket;
class MainWindow;
class proxy_data;
class settings;
class server : public QObject
{
    Q_OBJECT
public:
    explicit server(quint16 port, proxy_data* pd_, settings* sd_, MainWindow* mw_, QObject *parent = nullptr);
    virtual ~server();

signals:
    void res();
private slots:
    void slotNewConnection();
    void slotDataClient();
private:
    proxy_data* pd;
    settings* sd;
    MainWindow* mw;
    QTcpServer *m_tcpServer;
    int server_status;
    quint16 listen_port;
    QMap<qintptr, QTcpSocket*> m_tcpClients;
    QSet<qintptr> av_tcpClients;
};

#endif // SERVER_H
