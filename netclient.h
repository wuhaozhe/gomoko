#ifndef NETCLIENT_H
#define NETCLIENT_H
#include <QWidget>
#include <QHostAddress>
#include <QTcpSocket>

class netclient: public QWidget
{
    Q_OBJECT
public:
    QHostAddress server_address;
    netclient(QHostAddress address, QWidget *parent = 0);
    ~netclient();
public slots:
    void recv_message();
    void send_message(int, int, int);                //x, y, and restart

private:
    QTcpSocket *readwritesocket;
    void connect_to_host();              //与host进行连接
signals:
    void client_get_message(int, int, int);               //client 从 host 得到信息
    void connect_success();
    void client_disconnected();
};

#endif // NETCLIENT_H
