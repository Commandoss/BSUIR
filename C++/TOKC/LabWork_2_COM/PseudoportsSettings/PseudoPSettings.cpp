//
//  PseudoPSettings.cpp
//  writer
//
//  Created by Belousov Ilya on 1.10.21.
//

#include "PseudoPSettings.hpp"

PseudoPSettings::PseudoPSettings(const int descriptor) {
    this->descriptor = descriptor;
    if (!this->is_open()) this->error("Info: Setting port parameters\nError: The file descriptor is not valid!");

    this->clear_termios();
    this->get_old_param_terminal();

    this->set_all_flags();

    this->set_speed_in_port(B9600);
    this->set_speed_out_port(B9600);

    this->set_time_wait(1, 10);

    this->flush_port_buffer();
}

PseudoPSettings::~PseudoPSettings() {
    this->set_old_param_terminal();
}

void PseudoPSettings::set_all_flags() {
    this->get_param_terminal();
    this->set_iflags();
    this->set_lflags();
    this->set_oflags();
    this->set_сflags();
    this->set_param_terminal();
}

void PseudoPSettings::set_iflags() {
    this->newSettings.c_iflag |= (INPCK | ISTRIP);
    this->newSettings.c_iflag &= ~(IXON | IXOFF | IXANY);
}

void PseudoPSettings::set_lflags() {
    this->newSettings.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
}

void PseudoPSettings::set_oflags() {
    this->newSettings.c_oflag &= ~OPOST;
}

void PseudoPSettings::set_сflags() {
    this->newSettings.c_cflag |= (CLOCAL | CREAD);
    this->newSettings.c_cflag |= CS8;
}

void PseudoPSettings::set_speed_in_port(const speed_t speed) {
    this->get_param_terminal();

    if (cfsetispeed(&this->newSettings, speed))
        this->error("Func: set_speed_in_port\nError: cfsetispeed");

    this->set_param_terminal();
}
void PseudoPSettings::set_speed_out_port(const speed_t speed) {
    this->get_param_terminal();

    if (cfsetospeed(&this->newSettings, speed))
        this->error("Func: set_speed_out_port\nError: cfsetospeed");

    this->set_param_terminal();
}

void PseudoPSettings::set_time_wait(const cc_t min, const cc_t time) {
    this->get_param_terminal();

    this->newSettings.c_cc[VTIME] = time;
    this->newSettings.c_cc[VMIN] = min;

    this->set_param_terminal();
}

void PseudoPSettings::set_param_terminal() {
    if (tcsetattr(this->descriptor, TCSANOW, &this->newSettings))
        this->error("Func: set_old_param_terminal -> oldSettings");
}

void PseudoPSettings::get_param_terminal() {
    if (tcgetattr(this->descriptor, &this->newSettings))
        this->error("Func: get_old_param_terminal -> tcgetattr");
}

void PseudoPSettings::set_old_param_terminal() {
    if (tcsetattr(this->descriptor, TCSANOW, &this->oldSettings))
        this->error("Func: set_old_param_terminal -> oldSettings");
}

void PseudoPSettings::get_old_param_terminal() {
    if (tcgetattr(this->descriptor, &this->oldSettings))
        this->error("Func: get_old_param_terminal -> tcgetattr");
}

void PseudoPSettings::flush_port_buffer() {
    if (tcflush(this->descriptor, TCIFLUSH) < 0) {
        this->error("Func: flush_port_buffer\nError: tcflush");
    }
}

void PseudoPSettings::clear_termios() {
    bzero(&this->newSettings, sizeof(this->newSettings));
    bzero(&this->oldSettings, sizeof(this->oldSettings));
}

bool PseudoPSettings::is_open() {
    return descriptor > 0;
}

void PseudoPSettings::error(const std::string msg) {
    throw msg;
}
