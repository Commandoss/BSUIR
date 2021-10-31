//
//  Pseudoterminal.cpp
//  LabWork_4
//
//  Created by Belousov Ilya on 28.10.21.
//

#include "Pseudoterminal.hpp"

Pseudoterminal::Pseudoterminal() {
    this->descriptor = -1;
    this->counter = 0;
    this->settings = nullptr;
}

Pseudoterminal::~Pseudoterminal() {
    if (this->settings != nullptr)
        delete this->settings;
}

std::string Pseudoterminal::create_port() {
    if (this->is_open())
        Error::char_arr_error("Info: The pseudo terminal has already been created!");

    this->descriptor = posix_openpt(O_RDWR | O_NOCTTY | O_NDELAY);
    fcntl(this->descriptor, F_SETFL, 0);
    if (this->descriptor < 0)
        Error::char_arr_error("Func: create port\nInfo: open port");

    if (grantpt(this->descriptor) < 0)
        Error::char_arr_error("Func: create port\nInfo: grantpt");


    if (unlockpt(this->descriptor) < 0)
        Error::char_arr_error("Func: create port\nInfo: unlockpt");

    this->port = ptsname(this->descriptor);
    if (this->port.empty())
        Error::char_arr_error("Func: create port\nInfo: ptsname");

    init_port_settings();

    return this->port;
}

void Pseudoterminal::close_port() {
    if (this->is_open()) {
        close(this->descriptor);
        this->descriptor = -1;
        this->port.clear();
    }
}

bool Pseudoterminal::is_open() {
    return this->descriptor > 0;
}

//void Pseudoterminal::error(std::string msg) {
//    std::cerr << "\tError\n";
//    std::cerr << "Class: PseudoterminalSettings\n";
//    std::cerr << msg << std::endl;
//}

std::string Pseudoterminal::get_port_name() {
    return this->port;
}

std::string Pseudoterminal::read_port(const size_t size) {
    if (!this->is_open())
        Error::char_arr_error("Func: read port\nInfo: Port no open!");

    long n = 0;
    char buffer[size + 1];
    if ((n = read(this->descriptor, &buffer, size)) < 0)
        Error::char_arr_error("Func: read port.\nInfo: Failed to read");
    buffer[n] += '\0';
    return buffer;
}

size_t Pseudoterminal::write_port(const std::string str) {
    if (!this->is_open())
        Error::char_arr_error("Func: write port\nInfo: Port no open!");

    flush_port_buffer();
    return write(this->descriptor, str.c_str(), str.size());
}

void Pseudoterminal::init_port_settings() {
    int settingDescriptor = open(this->port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    this->settings = new PseudoterminalSettings(settingDescriptor);
}

void Pseudoterminal::flush_port_buffer() {
    if (tcflush(this->descriptor, TCIFLUSH) < 0)
        Error::char_arr_error("Func: flush_port_buffer\nError: tcflush");
}

void Pseudoterminal::change_speed(const int &speed) {
    if (!is_open())
        Error::char_arr_error("Func: Pseudoports::change_speed\nInfo: port no open.");

    this->settings->set_speed_in_port(speed);
    this->settings->set_speed_out_port(speed);
}
