#include "udp.h"

udp::udp(QObject *parent, Dialog *dia, int _port) : QObject(parent)
{
    ui = dia;
    udpPort = _port;
    socket = new QUdpSocket(this);
    //socket->bind(QHostAddress::LocalHost, udpPort);
    //ui->logMe("udp listen port:" + QString::number(udpPort));
    //connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void udp::sendMess(QString mess)
{
    QByteArray Data;
    Data.append(mess);
    socket->writeDatagram(Data, QHostAddress("192.168.0.140") , qint16(udpPort));
}

void udp::readyRead()
{
    // when data comes in
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());
    quint16 senderPort;
    QHostAddress *address = new QHostAddress();
    socket->readDatagram(buffer.data(), buffer.size(), address);
    ui->logMe("Message port: " + senderPort);
    ui->logMe("Message: " + buffer);
    delete(address);
}
