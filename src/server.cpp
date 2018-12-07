#include "server.h"
#include "proxy_data.h"
#include "mainwindow.h"
#include "settings.h"
#include <QByteArray>
#include <QTcpServer>
#include <QTcpSocket>
#include <QBuffer>

server::server(quint16 port, proxy_data *pd_, settings *sd_, MainWindow *mw_, QObject *parent) : QObject(parent)
{
    pd = pd_;
    sd = sd_;
    mw = mw_;
    listen_port = port;
    m_tcpServer = new QTcpServer();
    QObject::connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
    if (!m_tcpServer->listen(QHostAddress::Any, listen_port)) {
        sd->server_fail("Невозможно открыть TCP порт: " + QString::number(port));
        m_tcpServer->close();
        server_status = -1;
        return;
    }
    server_status = 1;
}
server::~server()
{
    foreach(qintptr i, m_tcpClients.keys()){
        m_tcpClients[i]->close();
        m_tcpClients.remove(i);
        m_tcpServer->close();
        delete m_tcpServer;
    }
}
void server::slotNewConnection()
{
    if(server_status==1){
        QTcpSocket* clientSocket = m_tcpServer->nextPendingConnection();
        qintptr idusersocs = clientSocket->socketDescriptor();
        m_tcpClients[idusersocs]=clientSocket;
        connect(m_tcpClients[idusersocs], SIGNAL(readyRead()), this, SLOT(slotDataClient()));
        QTextStream os(clientSocket);
        os.setAutoDetectUnicode(true);
        os << "warehouse server\n";
    }
}
void server::slotDataClient()
{
    QTcpSocket* clientSocket = static_cast<QTcpSocket*>(sender());
    qintptr idusersocs=clientSocket->socketDescriptor();
    QString str_ask;
    QTextStream os(clientSocket);
    os.setAutoDetectUnicode(true);
    if(!av_tcpClients.contains(idusersocs)){
        QString c_hash = clientSocket->readAll();
        if (c_hash == (sd->get_pass() + "\n")){            // Тут нужна будет проверка аутентификации !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! c_hash == QByteArray()
            av_tcpClients.insert(idusersocs);
            os << "authentication success\n";
        } else {
            os << "authentication filed\n";
            m_tcpClients[idusersocs]->close();
            m_tcpClients.remove(idusersocs);
        }
    } else {
        str_ask = clientSocket->readAll();
        if (str_ask.left(3) == "att"){
            auto rt = pd->at(static_cast<std::size_t>(str_ask.right(str_ask.size() - 4).toInt()))->make_json();
            os << "{\n";
            auto it = rt.begin();
            while (it != rt.end()){
                os << "{" << it.key() << ":" << it.value().toString() << "}\n";
                ++it;
            }
            os << "}\n";
        }
        if (str_ask.left(3) == "del"){
            if (pd->del(str_ask.right(str_ask.size() - 4).left(str_ask.size() - 5))){
               os << "delete ok\n";
               mw->slot_def_filtr();
            } else {
                os << "delete fail\n";
            }
        }
        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if (str_ask.left(3) == "app"){
            QString key = str_ask.left(str_ask.indexOf(';')).right(4);
            QString str_data = str_ask.right(str_ask.size() - str_ask.indexOf(';'));
            QByteArray tmpa;
            tmpa.append(str_ask.right(str_ask.size() - 4).left(str_ask.size() - 5));
            QByteArray tmpb;
            tmpb = tmpb.fromBase64(tmpa);

!!!!
            QImage image;
            QByteArray ba;
            QBuffer buffer(&ba);
            buffer.open(QIODevice::ReadOnly);
            image.load(&buffer, "PNG");
            pd->
        }
        if (str_ask.left(3) == "upd"){
            QString ant = str_ask.right(str_ask.size() - 4);

        }
        if (str_ask.left(3) == "sft"){
//            QString key = str_ask.left(str_ask.indexOf(';')).right(4);
//            QString str_data = str_ask.right(str_ask.size() - str_ask.indexOf(';'));
//            QByteArray tmpa;
//            tmpa.append(str_ask.right(str_ask.size() - 4).left(str_ask.size() - 5));
//            QByteArray tmpb;
//            tmpb = tmpb.fromBase64(tmpa);


//            QImage image;
//            QByteArray ba;
//            QBuffer buffer(&ba);
//            buffer.open(QIODevice::ReadOnly);
//            image.load(&buffer, "PNG");
//            pd->
        }
        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if (str_ask.left(3) == "gft"){
            QByteArray ba;
            QBuffer buffer(&ba);
            buffer.open(QIODevice::WriteOnly);
            pd->at(static_cast<std::size_t>(str_ask.right(str_ask.size() - 4).toInt()))->get_foto().save(&buffer, "PNG");
            os << ba.toBase64()  << "\n";
        }
        if (str_ask.left(3) == "hol"){
            std::shared_ptr<QVector<QDate>> hls = sd->lst_holliday();
            auto it = hls->begin();
            os << "data: \n";
            QDateTime tmpd;
            while (it != hls->end()) {
                tmpd.setDate(*it);
                os << QString::number(tmpd.toMSecsSinceEpoch()) << ";";
                ++it;
            }
            os << "\n";
        }
        if (str_ask.left(3) == "cls"){
            os << "connection close\n";
            m_tcpClients[idusersocs]->close();
            m_tcpClients.remove(idusersocs);
        }
    }
}
