//
//  Pseudoports.cpp
//  writer
//
//  Created by Belousov Ilya on 30.09.21.
//

#include "Pseudoports.hpp"

Pseudoports::Pseudoports() {
    this->masterDescriptor = -1;
    this->settings = nullptr;
}

Pseudoports::~Pseudoports() {
    if (this->settings != nullptr)
        delete this->settings;
}

std::string Pseudoports::create_port() {
    if (this->is_open())
        this->error("Info: The pseudo terminal has already been created!");

    this->masterDescriptor = posix_openpt(O_RDWR | O_NOCTTY | O_NDELAY);
    fcntl(this->masterDescriptor, F_SETFL, 0);
    if (this->masterDescriptor < 0) this->error("Func: create port\nInfo: open port");

    if (grantpt(this->masterDescriptor) < 0)
        this->error("Func: create port\nInfo: grantpt");


    if (unlockpt(this->masterDescriptor) < 0)
        this->error("Func: create port\nInfo: unlockpt");

    this->port = ptsname(this->masterDescriptor);
    if (this->port.empty())
        this->error("Func: create port\nInfo: ptsname");

    this->init_port_settings();

    return this->port;
}

void Pseudoports::close_port() {
    if (this->is_open()) {
        close(this->masterDescriptor);
        this->masterDescriptor = -1;
        this->port.clear();
    }
}

bool Pseudoports::is_open() {
    return this->masterDescriptor > 0;
}

void Pseudoports::error(std::string msg) {
    throw msg;
}

std::string Pseudoports::get_port_name() {
    return this->port;
}

std::string Pseudoports::read_port(const size_t size) {
    if (!this->is_open())
        this->error("Func: read port\nInfo: Port no open!");

    long n = 0;
    char buffer[size + 1];
    if ((n = read(this->masterDescriptor, &buffer, size)) < 0)
        this->error("Func: read port.\nInfo: Failed to read");
    buffer[n] += '\0';
    return buffer;
}

size_t Pseudoports::write_port(const std::string str) {
    if (!this->is_open())
        this->error("Func: write port\nInfo: Port no open!");

    this->flush_port_buffer();
    return write(this->masterDescriptor, str.c_str(), str.size());
}

void Pseudoports::init_port_settings() {
    int settingDescriptor = open(this->port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    this->settings = new PseudoPSettings(settingDescriptor);
}

void Pseudoports::flush_port_buffer() {
    if (tcflush(this->masterDescriptor, TCIFLUSH) < 0) {
        this->error("Func: flush_port_buffer\nError: tcflush");
    }
}

void Pseudoports::change_speed(const int &speed) {
    if (!is_open())
        this->error("Func: Pseudoports::change_speed\nInfo: port no open.");

    this->settings->set_speed_in_port(speed);
    this->settings->set_speed_out_port(speed);
}
