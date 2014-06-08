#ifndef UARM_CONTROLLER_H
#define UARM_CONTROLLER_H

#include <QMainWindow>
#include <QFile>
#include <cstdint>
#include "fixedendian.h"

namespace Ui {
class uArm_controller;
}

class uArm_controller : public QMainWindow
{
    Q_OBJECT

public:
    explicit uArm_controller(QWidget *parent = 0);
    ~uArm_controller();

private slots:
    void on_elevation_valueChanged(int);

    void on_azimuth_valueChanged(int);

    void on_hand_rotation_valueChanged(int);

    void on_radius_valueChanged(int value);

    void on_vacuum_on_stateChanged(int);

private:
    void build_cmd(int16_t height, uint16_t stretch,
                   int16_t base_rotation, int16_t hand_rotation,
                   uint8_t appendage_flags);
    void extract_values_from_ui(int16_t &height, uint16_t &stretch,
                                int16_t &base_rotation, int16_t &hand_rotation,
                                uint8_t &appendage_flags);
    void send_cmd();
    void value_changed(int);

    Ui::uArm_controller *ui;
    QFile uArm_serial_port;
    QByteArray out_buffer[20];
    QByteArray in_buffer[20];
    bool current_vacuum_flag;               /* Used to decide whether change is required */
#pragma pack(1)
    struct uArm_set_position_cmd {
        uint8_t header_1;                   /* 0xff */
        uint8_t header_2_set_position;      /* 0xaa */
        BigEndian<uint16_t> base_rotation;  /* azimuth amount */
        BigEndian<uint16_t> stretch;        /* radius */
        BigEndian<uint16_t> height;         /* elevation */
        BigEndian<uint16_t> hand_rotation;  /* rotation of end appendage */
        uint8_t appendage_flags;            /* flags to control gripper and vacuum */
    } cmd_set_pos;
#pragma pack()
};

#endif // UARM_CONTROLLER_H
