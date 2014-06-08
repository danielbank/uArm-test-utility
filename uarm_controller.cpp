#include "uarm_controller.h"
#include "ui_uarm_controller.h"

uArm_controller::uArm_controller(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uArm_controller)
{
    ui->setupUi(this);
}

uArm_controller::~uArm_controller()
{
    delete ui;
}
