#include "ipgetter.h"
#include <QHostInfo>
#include <QAbstractSocket>

Ipgetter::Ipgetter()
{

}

QString Ipgetter::getip()
{
    QString ip;
    QHostInfo info = QHostInfo::fromName(QHostInfo::localHostName());
    if(info.error() != QHostInfo::NoError)
    {
        return "0.0.0.0";
    }
    for(int i = 0; i < info.addresses().size(); i++)
    {
        if(info.addresses()[i].protocol() == QAbstractSocket::IPv4Protocol)
        {
            ip = info.addresses()[i].toString();
        }
    }
    return ip;
}
