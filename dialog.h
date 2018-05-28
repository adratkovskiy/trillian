#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTcpSocket>
#include <QHostAddress>
#include "../marvin/trillianbody.h"
#include <QMessageBox>
#include "trilliantits.h"
#include <QUdpSocket>
#include "udp.h"

class trillianBody;
class trillianTits;
class udp;

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    void logMe(QString log);
    void logJoy(int axisX, int axisY);
    void logJoyButtons(QString butt);
    void sendCommand(QString cmd);
    QString getIpTarget();
    ~Dialog();

private slots:
    void onSokConnected();
    void onSokDisconnected();
    void onSokReadyRead();
    void onSokDisplayError(QAbstractSocket::SocketError socketError);

    void on_pbConnect_clicked();
    void on_pbDisconnect_clicked();
    void on_pbSend_clicked();

private:
    Ui::Dialog *ui;
    QTcpSocket *_sok;
    quint16 _blockSize;
    QString _name;
    void AddToLog(QString text, QColor color = Qt::black);
    trillianTits *herTits;
    udp *udpSock;

};

#endif // DIALOG_H
