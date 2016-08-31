#ifndef HOSTDIA_H
#define HOSTDIA_H

#include <QDialog>
#include <QString>

namespace Ui {
class hostdia;
}

class hostdia : public QDialog
{
    Q_OBJECT

public:
    explicit hostdia(QWidget *parent = 0);
    ~hostdia();
    QString temp_ip;

private slots:

private:
    Ui::hostdia *ui;
};

#endif // HOSTDIA_H
