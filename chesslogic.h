#ifndef CHESSLOGIC_H
#define CHESSLOGIC_H
#include <QWidget>
#include <QVector>
#include <QPair>
#include <QMouseEvent>
#include <QString>
#include "netclient.h"
#include "netserver.h"

class chessboard;
class chesslogic: public QWidget
{
    Q_OBJECT
public:
    friend class chessboard;
    QVector< QVector< QPair<int, int> > > place;
    chesslogic(QVector< QVector< QPair<int, int> > > temp_place, QWidget *parent = 0);
    int whether_host = 0;         //0 not host, 1 is host
    QVector< QVector<int> > status;
    QString input_up;
    ~chesslogic();
protected:
private:
    const int each_width = 30;       //每个格子边长
    QPair<int, int> judge(int x, int y);
    netclient *client;
    netserver *server;
    int restart_flag = 0;              //重新开始比赛的flag
    int whether_win(int x, int y);             //0表示比赛未结束，1表示host赢，2表示client赢
    bool judge_win(int x, int y);               //判断是否五连珠
    void danger_check(bool if_host);             //判断是否危险, 参数表示是否是主机true代表是，false代表不是
    bool check_huo3(int opposite, int my, int x, int y);        //传入对方下的棋
    bool check_si4(int opposite, int my, int x, int y);              //opposite代表对方棋子颜色
    bool check_double3(int opposite, int my, int x, int y);
    int step[8][2] = {{0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {1, 0}, {-1, 0}};
    bool in_chessboard(int x, int y);
public slots:
    void host_set(QString in_ip);
    void client_set(QString in_ip);
    void reac_restart();
    void reac_disconnect();
signals:
    void client_transport(int, int, int);            //分别传输所下棋子的x,y,z坐标
    void host_transport(int, int, int);
    void gui_fresh();
    void client_connect_success();
    void host_get_connect();
    void client_win(bool);
    void host_win(bool);
    void unlock();
    void client_disconnect();
    void host_disconnect();
private slots:
    void host_recv_message(int, int, int);         //主机接收到信息
    void client_recv_message(int, int, int);             //client接收到信息
};

#endif // CHESSLOGIC_H
