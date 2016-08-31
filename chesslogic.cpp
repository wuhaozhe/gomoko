#include "chesslogic.h"
#include <math.h>
#include <QDebug>
#include <QHostAddress>

chesslogic::chesslogic(QVector< QVector< QPair<int, int> > > temp_place, QWidget *parent): QWidget(parent)
{
   //qDebug("constructor");
   place = temp_place;
   for(int i = 0; i < 15; i++)
   {
       QVector<int> temp;
       for(int j = 0; j < 15; j++)
       {
           temp.push_back(0);
       }
       status.push_back(temp);
   }
}


QPair<int, int> chesslogic::judge(int x, int y)
{
    for(int i = 0; i < 15; i++)
        for(int j = 0; j < 15; j++)
        {
            //qDebug()<<(x - place[i][j].first)<<" "<<(y - place[i][j].second);
            if((abs(x - place[i][j].first) < (each_width / 2 - 4) && abs(y - place[i][j].second) < (each_width / 2 - 4)))
            {

                if(status[i][j] != 1 && status[i][j] != 2)
                {
                    if(whether_host == 0)
                    {
                        emit client_transport(i, j, 0);
                        status[i][j] = 1;
                        danger_check(false);
                        if(whether_win(i, j) == 2)
                        {
                            emit client_win(true);
                        }
                        if(whether_win(i, j) == 1)
                        {
                            emit client_win(false);
                        }
                    }
                    else if(whether_host == 1)
                    {
                        emit host_transport(i, j, 0);
                        status[i][j] = 2;
                        danger_check(true);
                        if(whether_win(i, j) == 1)
                        {
                            emit host_win(true);
                        }
                        if(whether_win(i, j) == 2)
                        {
                            emit host_win(false);
                        }
                    }
                    return qMakePair(i, j);
                }
            }
        }
    return qMakePair(-1, -1);
}

void chesslogic::host_set(QString in_ip)
{
    whether_host = 1;
    QHostAddress temp;
    if(temp.setAddress(in_ip))
    {
        server = new netserver(temp);
        connect(this, SIGNAL(host_transport(int, int, int)), server, SLOT(send_message(int, int, int)));
        connect(server, SIGNAL(server_get_message(int,int,int)), this, SLOT(host_recv_message(int,int,int)));
        connect(server, SIGNAL(get_connection()), this, SIGNAL(host_get_connect()));
        connect(server, SIGNAL(host_disconnected()), this, SIGNAL(host_disconnect()));
    }
}

void chesslogic::client_set(QString in_ip)
{
    whether_host = 0;
    QHostAddress temp;
    if(temp.setAddress(in_ip))
    {
        emit unlock();
        client = new netclient(temp);
        connect(this, SIGNAL(client_transport(int,int,int)), client, SLOT(send_message(int,int,int)));
        connect(client, SIGNAL(client_get_message(int,int,int)), this, SLOT(client_recv_message(int,int,int)));
        connect(client, SIGNAL(connect_success()), this, SIGNAL(client_connect_success()));
        connect(client, SIGNAL(client_disconnected()), this, SIGNAL(client_disconnect()));
    }
}

void chesslogic::host_recv_message(int x, int y, int restart)
{
    if(restart == 0)
    {
        status[x][y] = 1;
        danger_check(true);
        emit unlock();
        emit gui_fresh();
        if(whether_win(x, y) == 1)
        {
            emit host_win(true);
        }
        else if(whether_win(x, y) == 2)
        {
            emit host_win(false);
        }
        else
        {
            emit unlock();
        }
    }
    else if(restart == 1)
    {
        for(int i = 0; i < 15; i++)
            for(int j = 0; j < 15; j++)
            {
                status[i][j] = 0;
            }
        emit gui_fresh();
    }
}

void chesslogic::client_recv_message(int x, int y, int restart)
{
    if(restart == 0)
    {
        status[x][y] = 2;
        danger_check(false);
        emit gui_fresh();
        if(whether_win(x, y) == 2)
        {
            emit client_win(true);
        }
        else if(whether_win(x, y) == 1)
        {
            emit client_win(false);
        }
        else
        {
            emit unlock();
        }
    }
    else if(restart == 1)
    {
        for(int i = 0; i < 15; i++)
            for(int j = 0; j < 15; j++)
            {
                status[i][j] = 0;
            }
        emit unlock();
        emit gui_fresh();
    }
}

int chesslogic::whether_win(int x, int y)
{
    if(status[x][y] == 1)          //client 下的棋
    {
        if(judge_win(x, y))
        {
            return 2;
        }
        else
            return 0;
    }
    else if(status[x][y] == 2)     //host 下的棋
    {
        if(judge_win(x, y))
        {
            return  1;
        }
        else
            return 0;
    }
    return 0;
}

bool chesslogic::judge_win(int x, int y)
{
    int count = 0;            //count successive chess
    for(int i = 0; i < 5; i++)
    {
        if((x - i) >= 0)
        {
            if(status[x - i][y] == status[x][y])
            {
                count++;
            }
        }
    }
    if(count == 5)
        return true;
    count = 0;
    for(int i = 0; i < 5; i++)
    {
        if((x + i) < 15)
        {
            if(status[x + i][y] == status[x][y])
            {
                count++;
            }
        }
    }
    if(count == 5)
        return true;
    count = 0;
    for(int i = 0; i < 5; i++)
    {
        if((x - i) >= 0 && (y - i) >= 0)
        {
            if(status[x - i][y - i] == status[x][y])
            {
                count++;
            }
        }
    }
    if(count == 5)
        return true;
    count = 0;
    for(int i = 0; i < 5; i++)
    {
        if((x - i) >= 0 && (y + i) < 15)
        {
            if(status[x - i][y + i] == status[x][y])
            {
                count++;
            }
        }
    }
    if(count == 5)
        return true;
    count = 0;
    for(int i = 0; i < 5; i++)
    {
        if((x + i) < 15 && (y - i) >= 0)
        {
            if(status[x + i][y - i] == status[x][y])
            {
                count++;
            }
        }
    }
    if(count == 5)
        return true;
    count = 0;
    for(int i = 0; i < 5; i++)
    {
        if((x + i) < 15 && (y + i) < 15)
        {
            if(status[x + i][y + i] == status[x][y])
            {
                count++;
            }
        }
    }
    if(count == 5)
        return true;
    count = 0;
    for(int i = 0; i < 5; i++)
    {
        if((y + i) < 15)
        {
            if(status[x][y + i] == status[x][y])
            {
                count++;
            }
        }
    }
    if(count == 5)
        return true;
    count = 0;
    for(int i = 0; i < 5; i++)
    {
        if((y - i) >= 0)
        {
            if(status[x][y - i] == status[x][y])
            {
                count++;
            }
        }
    }
    if(count == 5)
        return true;
    return false;
}

void chesslogic::reac_restart()
{
    for(int i = 0; i < 15; i++)
        for(int j = 0; j < 15; j++)
        {
            status[i][j] = 0;
        }
    emit gui_fresh();
    if(whether_host == 0)
    {
        emit unlock();
        emit client_transport(0, 0, 1);
    }
    else
    {
        emit host_transport(0, 0, 1);
    }
}

void chesslogic::danger_check(bool if_host)
{
    for(int i = 0; i < 15; i++)
        for(int j = 0; j < 15; j++)
        {
            if(status[i][j] != 1 && status[i][j] != 2)
            {
                if(if_host)
                {
                    if(check_double3(1, 2, i, j) || check_huo3(1, 2, i, j) || check_si4(1, 2, i, j))
                    {
                        status[i][j] = 3;
                    }
                }
                else
                {
                    if(check_double3(2, 1, i, j) || check_huo3(2, 1, i, j) || check_si4(2, 1, i, j))
                    {
                        status[i][j] = 3;
                    }
                }
            }
        }
}

bool chesslogic::check_double3(int opposite, int my, int x, int y)
{
    int amount_count = 0;   //计数以此为中心的八个方向的活2
    for(int i = 0; i < 8; i++)
    {
        int count = 0;
        for(int j = 1; j <= 3; j++)
        {
            int temp_x = x + step[i][0] * j;
            int temp_y = y + step[i][1] * j;
            if(in_chessboard(temp_x, temp_y))
            {
                if((status[temp_x][temp_y] == opposite) && (j <= 2))
                {
                    count++;
                }
                else if((status[temp_x][temp_y] != my) && (j == 3))
                {
                    count++;
                }
            }
        }
        if(count == 3)
            amount_count++;
    }
    if(amount_count >= 2)
        return true;
    else
        return false;
}

bool chesslogic::check_huo3(int opposite, int my, int x, int y)
{
    for(int i = 0; i < 8; i++)
    {
        int count = 0;
        for(int j = 1; j <= 4; j++)
        {
            int temp_x = x + step[i][0] * j;
            int temp_y = y + step[i][1] * j;
            if(in_chessboard(temp_x, temp_y))
            {
                if(status[temp_x][temp_y] == opposite && j <= 3)
                {
                    count++;
                }
                else if(status[temp_x][temp_y] != my && j == 4)
                {
                    count++;
                }
            }
        }
        if(count == 4)
            return true;
    }
    return false;
}

bool chesslogic::check_si4(int opposite, int my, int x, int y)
{
    for(int i = 0; i < 8; i++)
    {
        int count = 0;
        for(int j = 1; j <= 4; j++)
        {
            int temp_x = x + step[i][0] * j;
            int temp_y = y + step[i][1] * j;
            if(in_chessboard(temp_x, temp_y))
            {
                if(status[temp_x][temp_y] == opposite)
                {
                    count++;
                }
            }
        }
        if(count == 4)
            return true;
    }
    return false;
}

bool chesslogic::in_chessboard(int x, int y)
{
    if(x >= 0 && x < 15 && y >= 0 && y < 15)
        return true;
    else
        return false;
}

void chesslogic::reac_disconnect()
{
    //qDebug("hehe");
    if(whether_host == 0)
    {
        delete client;
    }
    else if(whether_host == 1)
    {
        delete server;
    }
}
