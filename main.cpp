#include "uarm_controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    uArm_controller w;
    w.show();

    return a.exec();
}
