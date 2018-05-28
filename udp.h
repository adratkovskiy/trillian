#ifndef UDP_H
#define UDP_H

#include <QObject>
#include <QUdpSocket>
#include "dialog.h"

class udp : public QObject
{
    Q_OBJECT
public:
    explicit udp(QObject *parent = nullptr, Dialog *dia = nullptr, int _port = 0, QString udpH = "127.0.0.1");
    void sendMess(QString mess);
    ~udp();
    void accessToSend(bool acc);
    void setHostPort(QString udpH, int _port);
signals:

public slots:
    void readyRead();
private:
    Dialog *ui;
    QUdpSocket *socket;
    QString udpHost;
    int udpPort;
    bool sendAccess = true;

};

#endif // UDP_H
