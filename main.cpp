#include "dialog.h"
#include <QApplication>

#undef main

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();

    return a.exec();
}
