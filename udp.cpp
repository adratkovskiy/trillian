#include "udp.h"

udp::udp(QObject *parent, Dialog *dia, int _port, QString udpH) : QObject(parent)
{
    ui = dia;
    udpHost = udpH;
    udpPort = _port;
    socket = new QUdpSocket(this);
    ui->logMe("udp host:port: " + udpH + ":" + QString::number(_port));
    //socket->bind(QHostAddress::LocalHost, udpPort);
    //ui->logMe("udp listen port:" + QString::number(udpPort));
    //connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

udp::~udp()
{

}

void udp::setHostPort(QString udpH, int _port)
{
    ui->logMe("set host:port: " + udpH + ":" + QString::number(_port));
    udpPort = _port;
    udpHost = udpH;
}
void udp::accessToSend(bool acc) {
    QString acc_str;
    acc == true ? acc_str = "started" : acc_str = "stopped";
    ui->logMe("sending: " + acc_str);
    sendAccess = acc;
}

void udp::sendMess(QString mess)
{
    if (sendAccess) {
        QByteArray Data;
        Data.append(mess);
        socket->writeDatagram(Data, QHostAddress(udpHost) , qint16(udpPort));
    }
    else {

    }
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
