#include "client_dia.h"
#include "ui_client_dia.h"
#include <QString>

client_dia::client_dia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::client_dia)
{
    ui->setupUi(this);
}

client_dia::~client_dia()
{
    delete ui;
}

void client_dia::on_lineEdit_textChanged(const QString &arg1)
{
    temp_ip = arg1;
}

void client_dia::on_pushButton_3_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '1');
}

void client_dia::on_pushButton_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '2');
}


void client_dia::on_pushButton_6_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '3');
}
void client_dia::on_pushButton_4_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '4');
}


void client_dia::on_pushButton_2_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '5');
}

void client_dia::on_pushButton_5_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '6');
}

void client_dia::on_pushButton_7_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '7');
}

void client_dia::on_pushButton_8_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '8');
}

void client_dia::on_pushButton_9_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '9');
}

void client_dia::on_pushButton_10_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '.');
}

void client_dia::on_pushButton_11_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '0');
}

void client_dia::on_pushButton_12_clicked()
{
    QString s = ui->lineEdit->text();
    ui->lineEdit->setText(s.left(s.size() - 1));
}
