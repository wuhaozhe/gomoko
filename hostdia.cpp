#include "hostdia.h"
#include "ui_hostdia.h"
#include "ipgetter.h"

hostdia::hostdia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hostdia)
{
    ui->setupUi(this);
    ui->lineEdit->setText(Ipgetter::getip());
    temp_ip = ui->lineEdit->text();
}

hostdia::~hostdia()
{
    delete ui;
}
