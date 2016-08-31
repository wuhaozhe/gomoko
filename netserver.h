#ifndef NET_H
#define NET_H
#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>
#include <QWidget>
#include <QHostAddress>
#include <QString>

class netserver: public QWidget
{
    Q_OBJECT
public:
    netserver(QHostAddress address, QWidget *parent = 0);
    ~netserver();
private:
    QTcpServer *listensocket;
    QTcpSocket *readwritesocket;
    QHostAddress server_address;
public slots:
    void send_message(int x, int y, int restart);
    void recv_message();
private slots:
    void accept_connection();
signals:
    void server_get_message(int, int, int);
    void get_connection();
    void host_disconnected();
};

#endif // NET_H
