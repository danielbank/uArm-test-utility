#ifndef UARM_CONTROLLER_H
#define UARM_CONTROLLER_H

#include <QMainWindow>

namespace Ui {
class uArm_controller;
}

class uArm_controller : public QMainWindow
{
    Q_OBJECT

public:
    explicit uArm_controller(QWidget *parent = 0);
    ~uArm_controller();

private:
    Ui::uArm_controller *ui;
};

#endif // UARM_CONTROLLER_H
