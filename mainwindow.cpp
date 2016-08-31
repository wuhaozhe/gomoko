#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hostdia.h"
#include "client_dia.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    chess_logic = ui->widget->chess_logic;
    connect(this, SIGNAL(host_ip_set(QString)), chess_logic, SLOT(host_set(QString)));
    connect(this, SIGNAL(client_ip_set(QString)), chess_logic, SLOT(client_set(QString)));
    connect(chess_logic, SIGNAL(client_connect_success()), this, SLOT(client_get_success()));
    connect(chess_logic, SIGNAL(host_get_connect()), this, SLOT(host_get_connection()));
    connect(chess_logic, SIGNAL(client_win(bool)), this, SLOT(reac_clientwin(bool)));
    connect(chess_logic, SIGNAL(host_win(bool)), this, SLOT(reac_hostwin(bool)));
    connect(this, SIGNAL(restart()), chess_logic, SLOT(reac_restart()));
    connect(this, SIGNAL(gui_fresh(bool)), ui->widget, SLOT(fresh_dangerous(bool)));
    connect(this, SIGNAL(disconnect()), chess_logic, SLOT(reac_disconnect()));
    connect(chess_logic, SIGNAL(host_disconnect()), this, SLOT(reac_host_disconnect()));
    connect(chess_logic, SIGNAL(client_disconnect()), this, SLOT(reac_client_disconnect()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString temp_ip;
    hostdia *temp = new hostdia();
    if(temp->exec() == QDialog::Accepted)
    {
        temp_ip = temp->temp_ip;
    }
    //qDebug()<<qPrintable(temp_ip);
    emit host_ip_set(temp_ip);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString temp_ip;
    client_dia *temp = new client_dia();
    if(temp->exec() == QDialog::Accepted)
    {
        temp_ip = temp->temp_ip;
    }
    emit client_ip_set(temp_ip);
}

void MainWindow::host_get_connection()
{
    QMessageBox::information(this, tr("host"), tr("there is a client connecting you"));
}

void MainWindow::client_get_success()
{
    QMessageBox::information(this, tr("client"), tr("connect success"));
}

void MainWindow::reac_clientwin(bool temp)
{
    if(temp)
    {
        QMessageBox::information(this, tr("client"), tr("you win"));
    }
    else
    {
        QMessageBox::information(this, tr("client"), tr("you lose"));
    }
}

void MainWindow::reac_hostwin(bool temp)
{
    if(temp)
    {
        QMessageBox::information(this, tr("host"), tr("you win"));
    }
    else
    {
        QMessageBox::information(this, tr("host"), tr("you lose"));
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    emit restart();
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    emit gui_fresh(checked);
}

void MainWindow::on_pushButton_4_clicked()
{
    emit disconnect();
}

void MainWindow::reac_host_disconnect()
{
    QMessageBox::information(this, tr("host"), tr("客户端已经与你断开连接"));
}

void MainWindow::reac_client_disconnect()
{
    QMessageBox::information(this, tr("client"), tr("主机已经与你断开连接"));
}
