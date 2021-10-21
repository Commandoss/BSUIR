//
//  SerialPorts.cpp
//  LabWork_1
//
//  Created by Belousov Ilya on 11.09.21.
//

#include "SerialPorts.hpp"
#include <iostream>

SerialPorts::SerialPorts() {
    this->descriptor = -1;
    this->settings = nullptr;
}

SerialPorts::SerialPorts(std::string port) : SerialPorts() {
    this->port = port;
    open_port();
}

SerialPorts::~SerialPorts() {
    if (this->settings != nullptr)
        delete this->settings;
}

void SerialPorts::open_port() {
    if (this->port.empty())
        this->error("Func: open port\nPort name not specified.");

    this->descriptor = open(this->port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (!is_open())
        this->error("Func: open_port\nInfo: Unable to open file.");

    fcntl(this->descriptor, F_SETFL, 0);

    this->init_port_settings();
}

void SerialPorts::open_port(const std::string port) {
    this->port = port;
    open_port();
}

void SerialPorts::close_port() {
    if (this->is_open()) {
        close(this->descriptor);
        this->descriptor = -1;
    }
}

bool SerialPorts::is_open() {
    return this->descriptor > 0;
}

void SerialPorts::error(const std::string msg) {
    throw msg;
}

size_t SerialPorts::write_port(const std::string str) {
    if (!this->is_open())
        this->error("Func: read_port\nInfo: Port no open!");

    this->flush_port_buffer();
    return write(this->descriptor, str.c_str(), str.size());
}

std::string SerialPorts::read_port(const size_t size) {
    if (!this->is_open())
        this->error("Func: write_port\nInfo: Port no open!");

    long n = 0;
    char buffer[size + 1];
    if ((n = read(this->descriptor, &buffer, size)) < 0)
        throw "Func: read port.\nInfo: Failed to read";
    buffer[size] += '\0';
    return buffer;
}

void SerialPorts::flush_port_buffer() {
    if (tcflush(this->descriptor, TCIFLUSH) < 0) {
        this->error("Func: flush_port_buffer\nError: tcflush");
    }
}

void SerialPorts::init_port_settings() {
    int settingDescriptor = open(this->port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    this->settings = new PseudoPSettings(settingDescriptor);
}

//int SerialPorts::chech_port_buffer() {
//    int bytes = 0;
//    if (ioctl(this->descriptor, FIONREAD, &bytes) < 0) {
//        this->error("Func: chech_port_buffer\nError: ioctl");
//    }
//    return bytes;
//}

//bool SerialPorts::change_law_port(const fs::path path, const mode_t mode) {
//    if (chmod(path.c_str(), mode) != 0) {
//        this->port_error("Func: change_law_port\n Error: chmod");
//    }
//    return true;
//}

//std::string SerialPorts::get_device_name() {
//    return device;
//}

void SerialPorts::change_speed(const int &speed) {
    if (!is_open())
        this->error("Func: Pseudoports::change_speed\nInfo: port no open.");

    this->settings->set_speed_in_port(speed);
    this->settings->set_speed_out_port(speed);
}
