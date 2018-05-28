#include "dialog.h"
#include "ui_dialog.h"

#include <QtGui>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :QDialog(parent),ui(new Ui::Dialog)
{
    ui->setupUi(this);

    _name = "";
    _sok = new QTcpSocket(this);
    connect(_sok, SIGNAL(readyRead()), this, SLOT(onSokReadyRead()));
    connect(_sok, SIGNAL(connected()), this, SLOT(onSokConnected()));
    connect(_sok, SIGNAL(disconnected()), this, SLOT(onSokDisconnected()));
    connect(_sok, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(onSokDisplayError(QAbstractSocket::SocketError)));

    herTits = new trillianTits(this, this);
    udpSock = new udp(this, this, ui->sbPort->text().toInt(), ui->leHost->text());
}

Dialog::~Dialog()
{
    delete herTits;
    delete ui;
}

void Dialog::logMe(QString log)
{
    ui->lwLog->addItem(log);
}

void Dialog::logJoy(int axisX, int axisY)
{
    ui->lblPad->setText(QString::number(axisX)+" "+QString::number(axisY));
}

void Dialog::logJoyButtons(QString butt)
{
    ui->lblButtons->setText(butt);
}
void Dialog::onSokDisplayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, "Error", "The host was not found");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, "Error", "The connection was refused by the peer.");
        break;
    default:
        QMessageBox::information(this, "Error", "The following error occurred: "+_sok->errorString());
    }
}

void Dialog::onSokReadyRead()
{
    QDataStream in(_sok);
    //если считываем новый блок первые 2 байта это его размер
    if (_blockSize == 0) {
        //если пришло меньше 2 байт ждем пока будет 2 байта
        if (_sok->bytesAvailable() < (int)sizeof(quint16))
            return;
        //считываем размер (2 байта)
        in >> _blockSize;
        qDebug() << "_blockSize now " << _blockSize;
    }
    //ждем пока блок прийдет полностью
    if (_sok->bytesAvailable() < _blockSize)
        return;
    else
        //можно принимать новый блок
        _blockSize = 0;
    //3 байт - команда серверу
    quint8 command;
    in >> command;
    qDebug() << "Received command " << command;
}

void Dialog::onSokConnected()
{
    ui->pbConnect->setEnabled(false);
    ui->pbDisconnect->setEnabled(true);
    _blockSize = 0;
    AddToLog("Connected to"+_sok->peerAddress().toString()+":"+QString::number(_sok->peerPort()),Qt::green);

    //try autch
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0;
    out << (quint8)trillianBody::comAutchReq;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    _sok->write(block);
}

void Dialog::onSokDisconnected()
{
    ui->pbConnect->setEnabled(true);
    ui->pbDisconnect->setEnabled(false);
    ui->pbSend->setEnabled(false);
    AddToLog("Disconnected from"+_sok->peerAddress().toString()+":"+QString::number(_sok->peerPort()), Qt::green);
}

void Dialog::on_pbConnect_clicked()
{
    //_sok->connectToHost(ui->leHost->text(), ui->sbPort->value());
    udpSock->setHostPort(ui->leHost->text(), ui->sbPort->text().toInt());
    udpSock->accessToSend(true);
}

void Dialog::on_pbDisconnect_clicked()
{
    //_sok->disconnectFromHost();
    udpSock->accessToSend(false);
}

void Dialog::on_pbSend_clicked()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0;
    out << (quint8)trillianBody::comMessageToAll;
    out << ui->pteMessage->document()->toPlainText();
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    _sok->write(block);
    ui->pteMessage->clear();
}

void Dialog::AddToLog(QString text, QColor color)
{
    ui->lwLog->insertItem(0, QTime::currentTime().toString()+" "+text);
    ui->lwLog->item(0)->setTextColor(color);
}

QString Dialog::getIpTarget()
{
    return ui->leHost->text();
}

void Dialog::sendCommand(QString cmd)
{
    udpSock->sendMess(cmd);
    /*QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0;
    out << (quint8)trillianBody::comMessageToAll;
    out << cmd;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    _sok->write(block);*/
}

