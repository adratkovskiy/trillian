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
    joy_left = SDL_JoystickOpen(0);
    joy_right = SDL_JoystickOpen(1);
}

trillianTits::~trillianTits()
{

}

void trillianTits::updateTime() {
    SDL_PollEvent(&event);
    int xAxis_left = SDL_JoystickGetAxis(joy_left, 0);
    int yAxis_left = SDL_JoystickGetAxis(joy_left, 1);
    int xAxis_right = SDL_JoystickGetAxis(joy_right, 0);
    int yAxis_right = SDL_JoystickGetAxis(joy_right, 1);
    QString buttons = QString::number(floor(xAxis_left / 3300)) + QString::number(floor(yAxis_left / 3300));
    buttons.append(QString::number(floor(xAxis_right / 3300)) + QString::number(floor(yAxis_right / 3300)));
    buttons.append(QString::number(SDL_JoystickGetButton(joy_left, 0)));
    buttons.append(QString::number(SDL_JoystickGetButton(joy_left, 1)));
    buttons.append(QString::number(SDL_JoystickGetButton(joy_left, 2)));
    buttons.append(QString::number(SDL_JoystickGetButton(joy_left, 3)));
    buttons.append(QString::number(SDL_JoystickGetButton(joy_left, 4)));
    buttons.append(QString::number(SDL_JoystickGetButton(joy_left, 5)));
    buttons.append(QString::number(SDL_JoystickGetButton(joy_left, 6)));
    buttons.append(QString::number(SDL_JoystickGetButton(joy_left, 7)));
    buttons.append(QString::number(SDL_JoystickGetButton(joy_left, 8)));
    buttons.append(QString::number(SDL_JoystickGetButton(joy_left, 9)));
    buttons.append(QString::number(SDL_JoystickGetButton(joy_left, 10)));
    buttons.append(QString::number(SDL_JoystickGetButton(joy_left, 11)));
    buttons.append(QString::number(SDL_JoystickGetButton(joy_left, 12)));
    ui->logJoyButtons(buttons);
    ui->sendCommand("cmd#js"+buttons);
}
