#ifndef CLIENT_DIA_H
#define CLIENT_DIA_H

#include <QDialog>
#include <QString>

namespace Ui {
class client_dia;
}

class client_dia : public QDialog
{
    Q_OBJECT

public:
    explicit client_dia(QWidget *parent = 0);
    ~client_dia();
    QString temp_ip;

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::client_dia *ui;
};

#endif // CLIENT_DIA_H
