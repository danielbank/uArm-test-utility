#include "uarm_controller.h"
#include "ui_uarm_controller.h"
#include <QDebug>

uArm_controller::uArm_controller(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uArm_controller) {
    ui->setupUi(this);
    uArm_serial_port.setFileName("/dev/ttyUSB0");
    uArm_serial_port.open(QIODevice::ReadWrite);
    current_vacuum_flag = ui->vacuum_on->isChecked();
}

uArm_controller::~uArm_controller() {
    delete ui;
}

void uArm_controller::build_cmd(int16_t height, uint16_t stretch,
                                int16_t base_rotation, int16_t hand_rotation,
                                uint8_t appendage_flags) {
    struct uArm_set_position_cmd set_pos;

    set_pos = { 0,0, 0,0,0,0, 0};
    set_pos.header_1 = 0xff;
    set_pos.header_2_set_position = 0xaa;
    set_pos.base_rotation = base_rotation;
    set_pos.hand_rotation = hand_rotation;
    set_pos.height = height;
    set_pos.stretch = stretch;
    set_pos.appendage_flags = appendage_flags;

    cmd_set_pos = set_pos;
}

void uArm_controller::extract_values_from_ui(int16_t &height, uint16_t &stretch,
                                             int16_t &base_rotation, int16_t &hand_rotation,
                                             uint8_t &appendage_flags) {
    bool vacuum_flag;
    height = ui->elevation->value();
    stretch = ui->radius->value();
    base_rotation = ui->azimuth->value();
    hand_rotation = ui->hand_rotation->value();
    vacuum_flag = ui->vacuum_on->isChecked();
    if (current_vacuum_flag == vacuum_flag) {
        appendage_flags = 0x00;
    } else {
        if (vacuum_flag) {
            appendage_flags = 0x01;
        } else {
            appendage_flags = 0x02;
        } /* endif */
    } /* endif */
    current_vacuum_flag = vacuum_flag;

    qDebug() << "height =" << height << "stretch =" << stretch;
    qDebug() << "base_rotation =" << base_rotation << "hand_rotation =" << hand_rotation;
    qDebug() << "appendage flags =" << appendage_flags;
}

void uArm_controller::send_cmd() {
    qint64 bytes_written = uArm_serial_port.write((char *)&cmd_set_pos, sizeof(cmd_set_pos));
    if (bytes_written != sizeof(cmd_set_pos)) {
        abort();
    } /* endif */
    uArm_serial_port.flush();
}

void uArm_controller::value_changed(int) {
    int16_t height;
    uint16_t stretch;
    int16_t base_rotation;
    int16_t hand_rotation;
    uint8_t appendage_flags;

    extract_values_from_ui(height, stretch, base_rotation, hand_rotation, appendage_flags);
    build_cmd(height, stretch, base_rotation, hand_rotation, appendage_flags);
    send_cmd();
}

void uArm_controller::on_elevation_valueChanged(int value) {
    value_changed(value);
}

void uArm_controller::on_azimuth_valueChanged(int value) {
    value_changed(value);
}

void uArm_controller::on_hand_rotation_valueChanged(int value) {
    value_changed(value);
}

void uArm_controller::on_radius_valueChanged(int value) {
    value_changed(value);
}

void uArm_controller::on_vacuum_on_stateChanged(int ) {
    value_changed(0);
}
