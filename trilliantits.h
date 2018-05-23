#ifndef TRILLIANTITS_H
#define TRILLIANTITS_H

#include <QObject>
#include <QTimer>
#include "dialog.h"
#include <SDL/SDL.h>


class Dialog;

class trillianTits : public QObject
{
    Q_OBJECT
public:
    explicit trillianTits(QObject *parent = nullptr, Dialog *dia = nullptr);
    ~trillianTits();

signals:

public slots:

private:
    Dialog *ui;
    QTimer *tTimer;
    SDL_Joystick *joy_left;
    SDL_Joystick *joy_right;
    SDL_Event event;
    int upd = 0;

private slots:
    void updateTime();
};

#endif // TRILLIANTITS_H
