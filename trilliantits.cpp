#include "trilliantits.h"
#include <QDebug>

trillianTits::trillianTits(QObject *parent, Dialog *dia) : QObject(parent)
{
    ui = dia;
    dia->logMe("logging connected");
    tTimer = new QTimer(this);
    tTimer->setInterval(50);
    connect(tTimer, SIGNAL(timeout()), this, SLOT(updateTime()));
    tTimer->start();
    // Инициализация SDL для использования джойстика
    SDL_Init(SDL_INIT_JOYSTICK);
    // Включаем
    SDL_JoystickEventState(SDL_ENABLE);
    // Открываем ;)
    joy = SDL_JoystickOpen(0);
}

trillianTits::~trillianTits()
{

}

void trillianTits::updateTime() {
    SDL_PollEvent(&event);
    int xAxis = SDL_JoystickGetAxis(joy, 0);
    int yAxis = SDL_JoystickGetAxis(joy, 1);
    QString buttons = QString::number(floor(xAxis / 3300)) + QString::number(floor(yAxis / 3300));
    buttons.append(QString::number(SDL_JoystickGetButton(joy, 0)));
    buttons.append(QString::number(SDL_JoystickGetButton(joy, 1)));
    buttons.append(QString::number(SDL_JoystickGetButton(joy, 2)));
    buttons.append(QString::number(SDL_JoystickGetButton(joy, 3)));
    buttons.append(QString::number(SDL_JoystickGetButton(joy, 4)));
    buttons.append(QString::number(SDL_JoystickGetButton(joy, 5)));
    buttons.append(QString::number(SDL_JoystickGetButton(joy, 6)));
    buttons.append(QString::number(SDL_JoystickGetButton(joy, 7)));
    buttons.append(QString::number(SDL_JoystickGetButton(joy, 8)));
    buttons.append(QString::number(SDL_JoystickGetButton(joy, 9)));
    buttons.append(QString::number(SDL_JoystickGetButton(joy, 10)));
    buttons.append(QString::number(SDL_JoystickGetButton(joy, 11)));
    buttons.append(QString::number(SDL_JoystickGetButton(joy, 12)));
    if (upd < 10) {
        upd++;
    }
    else {
        upd = 0;
    }
    buttons.append(QString::number(upd));
    ui->logJoyButtons(buttons);
    ui->sendCommand("cmd#js"+buttons);
}
