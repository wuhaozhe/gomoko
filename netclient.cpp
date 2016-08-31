#include "netclient.h"
#include <QDebug>

netclient::netclient(QHostAddress address, QWidget* parent): QWidget(parent)
{
    server_address = address;
    readwritesocket = new QTcpSocket();
    connect(readwritesocket, SIGNAL(connected()), this, SIGNAL(connect_success()));
    connect_to_host();
    connect(readwritesocket, SIGNAL(readyRead()), this, SLOT(recv_message()));
    connect(readwritesocket, SIGNAL(disconnected()), this, SIGNAL(client_disconnected()));
}

void netclient::recv_message()
{
    QString info;
    info = (this->readwritesocket->readAll()).data();
    QStringList temp = info.split(',');
    int x = temp[0].toInt();
    int y = temp[1].toInt();
    int restart = temp[2].toInt();
    emit client_get_message(x, y, restart);
}

void netclient::send_message(int x, int y, int restart)
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

void netclient::connect_to_host()
{
    readwritesocket->connectToHost(server_address, 40000);
}

netclient::~netclient()
{
    qDebug("delete client");
    delete readwritesocket;
}
