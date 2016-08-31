#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHostAddress>
#include <QString>
#include "chessboard.h"
#include "chesslogic.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    chesslogic *chess_logic;
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void host_get_connection();
    void client_get_success();
    void reac_clientwin(bool);
    void reac_hostwin(bool);

    void on_pushButton_3_clicked();

    void on_checkBox_clicked(bool checked);

    void on_pushButton_4_clicked();
    void reac_host_disconnect();
    void reac_client_disconnect();

private:
    Ui::MainWindow *ui;
    QHostAddress host_address;
signals:
    void host_ip_set(QString);
    void client_ip_set(QString);
    void restart();
    void gui_fresh(bool);
    void disconnect();
};

#endif // MAINWINDOW_H
