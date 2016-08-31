#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <QWidget>
#include <QPaintEvent>
#include <QVector>
#include <QPair>
#include <QMouseEvent>
#include <QPixmap>
#include "chesslogic.h"

class chessboard: public QWidget
{
    Q_OBJECT
public:
    chessboard(QWidget *parent = 0);
    const int each_width = 30;       //每个格子宽度
    chesslogic *chess_logic;
    int dangerous_flag = 0;        //1 画， 0 不画
    ~chessboard();
protected:
    void paintEvent(QPaintEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
private:
    QVector< QVector< QPair<int, int> > > place;    //每个交点位置, 第一个为x（横）, 第二个为y（纵）
    int win_flag = 0;                     //0代表没有出现胜负， 1代表白胜，2为黑胜
    int lock_flag = 1;
    QPixmap *picture;
public slots:
    void fresh();
    void reac_unlock();
    void fresh_dangerous(bool);
};

#endif // CHESSBOARD_H
