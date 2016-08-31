#include "chessboard.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QColor>

chessboard::chessboard(QWidget *parent): QWidget(parent)
{
    //setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    picture = new QPixmap();
    picture->load(":/new/prefix1/bomb.ico");
    this->setGeometry(200, 200, 495, 495);
    for(int i = 1; i <= 15; i++)
    {
        QVector< QPair<int, int> > temp;
        for(int j = 1; j <= 15; j++)
        {
            temp.push_back(qMakePair(i * each_width, j * each_width));
        }
        place.push_back(temp);
    }
    chess_logic = new chesslogic(place, this);
    connect(chess_logic, SIGNAL(gui_fresh()), this, SLOT(fresh()));
    connect(chess_logic, SIGNAL(unlock()), this, SLOT(reac_unlock()));
}

void chessboard::paintEvent(QPaintEvent *ev)
{
    QPainter *painter = new QPainter(this);
    painter->setBrush(Qt::darkYellow);
    painter->setPen(Qt::black);
    painter->drawRect(0, 0, this->width(), this->height());
    for(int i = 0; i < 15; i++)
    {
        painter->drawLine(each_width, each_width + i * each_width, 15 * each_width, each_width + i * each_width);
        painter->drawLine(each_width + i * each_width, each_width, each_width + i * each_width, 15 * each_width);
    }
    painter->setBrush(Qt::black);     //花小黑方框
    painter->drawRect(place[3][3].first - 2, place[3][3].second - 2, 4, 4);
    painter->drawRect(4 * each_width - 2, 12 * each_width - 2, 4, 4);
    painter->drawRect(12 * each_width - 2, 4 * each_width - 2, 4, 4);
    painter->drawRect(12 * each_width - 2, 12 * each_width - 2, 4, 4);
    painter->drawRect(8 * each_width - 2, 8 * each_width - 2, 4, 4);

    //画棋子
    for(int i = 0; i < 15; i++)
        for(int j = 0; j < 15; j++)
        {
            if(chess_logic->status[i][j] == 1)
            {
                painter->setBrush(Qt::black);                      //black 棋子
                painter->drawEllipse(place[i][j].first - each_width / 3, place[i][j].second - each_width / 3, (each_width * 2) / 3, (each_width * 2) / 3);
            }
            if(chess_logic->status[i][j] == 2)
            {
                painter->setBrush(Qt::white);                      //white 棋子
                painter->drawEllipse(place[i][j].first - each_width / 3, place[i][j].second - each_width / 3, (each_width * 2) / 3, (each_width * 2) / 3);
            }
            if(chess_logic->status[i][j] == 3 && dangerous_flag == 1)
            {
                painter->drawPixmap(place[i][j].first - each_width / 3, place[i][j].second - each_width / 3, picture->scaled((each_width * 2) / 3, (each_width * 2) / 3));
            }
        }
    delete painter;
}

void chessboard::fresh()
{
    update();
}

void chessboard::mousePressEvent(QMouseEvent *ev)
{
    if(lock_flag == 0)
    {
        if(ev->button() == Qt::LeftButton)
        {
            QPair<int, int> temp = chess_logic->judge(ev->x(), ev->y());
            if(temp.first >= 0 && temp.second >= 0)
            {
                update();
                lock_flag = 1;
            }
        }
    }
}

void chessboard::reac_unlock()
{
    lock_flag = 0;
}

void chessboard::fresh_dangerous(bool temp)
{
    if(temp)
    {
        dangerous_flag = 1;
        update();
    }
    else
    {
        dangerous_flag = 0;
        update();
    }
}
chessboard::~chessboard()
{
    delete chess_logic;
    delete picture;
}
