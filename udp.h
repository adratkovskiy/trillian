#ifndef UDP_H
#define UDP_H

#include <QObject>
#include <QUdpSocket>
#include "dialog.h"

class udp : public QObject
{
    Q_OBJECT
public:
    explicit udp(QObject *parent = nullptr, Dialog *dia = nullptr, int _port = 0);
    void sendMess(QString mess);

signals:

public slots:
    void readyRead();
private:
    Dialog *ui;
    QUdpSocket *socket;
    int udpPort;
};

#endif // UDP_H
