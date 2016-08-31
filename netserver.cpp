#include "netserver.h"
#include <QByteArray>
#include <QStringList>
#include <QDebug>

netserver::netserver(QHostAddress address, QWidget *parent): QWidget(parent)
{
    server_address = address;
    listensocket = new QTcpServer();
    listensocket->listen(QHostAddress::Any, 40000);
    connect(listensocket, SIGNAL(newConnection()), this, SLOT(accept_connection()));
}

void netserver::accept_connection()
{
    emit get_connection();
    readwritesocket = listensocket->nextPendingConnection();          //socket parent自动设置为server
    connect(readwritesocket, SIGNAL(readyRead()), this, SLOT(recv_message()));
    connect(readwritesocket, SIGNAL(disconnected()), this, SIGNAL(host_disconnected()));
}

void netserver::recv_message()
{
    QString info;
    info = (this->readwritesocket->readAll()).data();
    QStringList temp = info.split(',');
    int x = temp[0].toInt();
    int y = temp[1].toInt();
    int restart = temp[2].toInt();
    emit server_get_message(x, y, restart);
}

void netserver::send_message(int x, int y, int restart)
{
    QString send_info;
    send_info += QString::number(x);
    send_info += ',';
    send_info += QString::number(y);
    send_info += ',';
    send_info += QString::number(restart);
    QByteArray array_info = send_info.toUtf8();
    this->readwritesocket->write(array_info);
}

netserver::~netserver()
{
    //qDebug("deletesever");
    delete readwritesocket;
    delete listensocket;
}
