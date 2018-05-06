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

    // Получаем значения, соответствующие смещению джойстика
    // по оси Х
    int xAxis = SDL_JoystickGetAxis(joy, 0);
    // по оси Y
    int yAxis = SDL_JoystickGetAxis(joy, 1);
    ui->logJoy(xAxis, yAxis);
}
