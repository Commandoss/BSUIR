//
//  Pseudoterminal.cpp
//  LabWork_4
//
//  Created by Belousov Ilya on 28.10.21.
//

#include "Pseudoterminal.hpp"

Pseudoterminal::Pseudoterminal() {
    this->lnetwork.clear();
    this->descriptor = -1;
    this->counter = 0;
    this->settings = nullptr;
}

Pseudoterminal::~Pseudoterminal() {
    if (this->settings != nullptr)
        delete this->settings;
}

bool Pseudoterminal::create_port() {
    if (this->is_open()) {
        Error::char_arr_error("Info: The pseudo terminal has already been created!");
        return false;
    }

    this->descriptor = posix_openpt(O_RDWR | O_NOCTTY | O_NDELAY);
    fcntl(this->descriptor, F_SETFL, 0);
    if (this->descriptor < 0) {
        Error::char_arr_error("Func: create port\nInfo: open port");
        return false;
    }

    if (grantpt(this->descriptor) < 0) {
        Error::char_arr_error("Func: create port\nInfo: grantpt");
        return false;
    }


    if (unlockpt(this->descriptor) < 0) {
        Error::char_arr_error("Func: create port\nInfo: unlockpt");
        return false;
    }

    this->port = ptsname(this->descriptor);
    if (this->port.empty()) {
        Error::char_arr_error("Func: create port\nInfo: ptsname");
        return false;
    }

    init_port_settings();
    return true;
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

bool Pseudoterminal::connect(const std::string &port) {
    this->counter = 0;
    for (; this->counter < 10; this->counter++) {
        int descriptor = open(port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
        if (descriptor < 0) {
            Error::char_arr_error("Func: Pseudoterminal::connect.\nInfo: The device is not available or does not exist on the network!\n");
            wait();
            continue;
        }
        this->lnetwork.insert({(unsigned int)lnetwork.size(), {port, descriptor}});
        return true;
    }
    return false;
}

void Pseudoterminal::disconnect(const unsigned int &device) {
    if (device > this->lnetwork.size())
        Error::char_arr_error("Func: Pseudoterminal::disconnect\nInfo: This device is not in the list of connected!\n");
    close(this->lnetwork[device].second);
}

std::string Pseudoterminal::read_port(const size_t &size) {
    if (!this->is_open())
        Error::char_arr_error("Func: read port\nInfo: Port no open!");

    wait();

    long n = 0;
    char buffer[size + 1];
    if ((n = read(this->descriptor, &buffer, size)) < 0)
        Error::char_arr_error("Func: read port.\nInfo: Failed to read");
    buffer[n] += '\0';
    return buffer;
}

size_t Pseudoterminal::write_port(const std::string &str, const unsigned int &device) {
    if (device > this->lnetwork.size())
        Error::char_arr_error("Func: write port\nInfo: No connection has been established with this device!\n");
    this->buffer << str;
    flush_port_buffer();
    return write(this->lnetwork[device].second, str.c_str(), str.size());
}

void Pseudoterminal::init_port_settings() {
    int settingDescriptor = open(this->port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    this->settings = new PseudoterminalSettings(settingDescriptor);
}

void Pseudoterminal::flush_port_buffer() {
    if (tcflush(this->descriptor, TCIFLUSH) < 0)
        Error::char_arr_error("Func: flush_port_buffer\nError: tcflush");
}

void Pseudoterminal::change_speed_out(const size_t &speed) {
    if (!is_open())
        Error::char_arr_error("Func: Pseudoports::change_speed\nInfo: port no open.");

    this->settings->set_speed_out_port(speed);
}

void Pseudoterminal::change_speed_in(const size_t &speed) {
    if (!is_open())
        Error::char_arr_error("Func: Pseudoports::change_speed\nInfo: port no open.");

    this->settings->set_speed_in_port(speed);
}


std::map<unsigned int, std::pair<std::string, int>> Pseudoterminal::get_list_network() const {
    return this->lnetwork;
}

size_t Pseudoterminal::get_count_connect() const {
    return this->lnetwork.size();
}

void Pseudoterminal::wait() const noexcept {
    unsigned int CWmin = 15, CWmax = 1023;
    std::srand(std::time(NULL));
    unsigned int sleep = std::rand() % CWmax + CWmin;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
}

void Pseudoterminal::resending() {

}

void Pseudoterminal::collision() {
    if (!is_open()) {
        Error::char_arr_error("Func: Pseudoterminal::collision\nInfo: Port no open!");
        return;
    }
    if (get_count_connect() <= 0) {
        Error::char_arr_error("Func: Pseudoterminal::collision\nInfo: The port is not connected to any device!");
        return;
    }


    std::stringstream ss;
    boost::archive::text_oarchive wr(ss);

    status s;
    s.set_error(get_port_name());

    wr & s;
    for (auto device : this->lnetwork) {
        write_port(ss.str(), device.first);
    }
}
