//
//  Pseudoterminal.cpp
//  LabWork_4
//
//  Created by Belousov Ilya on 28.10.21.
//

#include "Pseudoterminal.hpp"

Pseudoterminal::Pseudoterminal() {
    this->descriptor = -1;
}

Pseudoterminal::~Pseudoterminal() {
    if (this->settings != nullptr)
        delete this->settings;
    close_port();
}

unsigned int Pseudoterminal::create_terminal() {
    int descriptor = posix_openpt(O_RDWR | O_NOCTTY | O_NDELAY);

    fcntl(descriptor, F_SETFL, 0);
    if (descriptor < 0)
        throw Error("Func: create port.", "Info: open port");

    if (grantpt(descriptor) < 0)
        throw Error("Func: create port.", "Info: grantpt");

    if (unlockpt(descriptor) < 0)
        throw Error("Func: create port.", "Info: unlockpt");

    this->port = ptsname(descriptor);
    if (this->port.empty())
        throw Error("Func: create port.", "Info: ptsname");

    init_port_settings();
    return descriptor;
}
void Pseudoterminal::create_device() {
    if (this->is_open())
        throw Error("Func: create port.", "Info: The pseudo terminal has already been created!");

    this->descriptor = create_terminal();
    start_thread();
}

bool Pseudoterminal::close_port() {
    if (this->is_open()) {
        stop_thread();
        close(this->descriptor);
        this->descriptor = -1;
        this->port.clear();
        return true;
    }
    return false;
}

bool Pseudoterminal::is_open() {
    return this->descriptor > 0;
}

std::string Pseudoterminal::get_port_name() {
    return this->port;
}

bool Pseudoterminal::сompound(const std::string &port) {
    if (is_connected()) {

    }
    int descriptor = 0;
    for (auto counter = 0; counter < 10; counter++) {
        descriptor = open(port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
        if (descriptor < 0) {
            std::cout << "Func: Pseudoterminal::connect. " << "Info: The device is not available or does not exist on the network!\n";
            wait();
            continue;
        }

        this->connectedDevice = {port, descriptor};
        return true;
    }
    return false;
}

void Pseudoterminal::disconnection() {
    if (this->connectedDevice.second < 0)
        throw Error("Func: Pseudoterminal::disconnection.", "Info: Device is not connected!\n");

    this->connectedDevice.~pair();
    close(this->connectedDevice.second);
}

std::string Pseudoterminal::read_port(const size_t &size) {
    if (!this->is_open())
        throw Error("Func: read port.", "Info: Port no open!");

    long n = 0;
    char buffer[size + 1];
    if ((n = read(this->descriptor, &buffer, size)) < 0)
        throw Error("Func: read port.", "Info: Failed to read");
    buffer[n] += '\0';
    return buffer;
}

size_t Pseudoterminal::write_port(const std::string &str) {
    if (this->connectedDevice.second < 0)
        throw Error("Func: write port.", "Info: No connection has been established with this device!\n");

    wait();
    size_t count = write(this->connectedDevice.second, str.c_str(), str.size());
    wait();

    return count;
}

void Pseudoterminal::init_port_settings() {
    int settingDescriptor = open(this->port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    this->settings = new PseudoterminalSettings(settingDescriptor);
}

void Pseudoterminal::change_speed_out(const size_t &speed) {
    if (!is_open())
        throw Error("Func: Pseudoports::change_speed.", "Info: port no open.");

    this->settings->set_speed_out_port(speed);
}

void Pseudoterminal::change_speed_in(const size_t &speed) {
    if (!is_open())
        throw Error("Func: Pseudoports::change_speed.", "Info: port no open.");

    this->settings->set_speed_in_port(speed);
}

void Pseudoterminal::wait() const noexcept {
    unsigned int CWmin = 15, CWmax = 1023;
    std::srand((unsigned int)std::time(NULL));
    unsigned int sleep = std::rand() % CWmax + CWmin;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
}

void Pseudoterminal::thread_read() {
    std::stringstream ss;
    std::unique_lock<std::mutex> uq(this->mutRead);
    while (true) {
        ss.clear();
        condition.wait(uq, [this] {
            return this->fread == THREAD_RUN
            || this->fread == THREAD_STOP;
        });
        if (this->fread == THREAD_STOP)
            return;

        ss << read_port(1023);

        try {
            boost::archive::text_iarchive rd(ss);
            rd & this->marker;
        } catch (const boost::archive::archive_exception &ex) {
            continue;
        }
        THREAD_SET_FLAG_RUN(this->mutWrite, this->condition, this->fwrite);
    }
}

void Pseudoterminal::thread_write() {
    std::unique_lock<std::mutex> uq(this->mutWrite);
    while (true) {
        condition.wait(uq, [this] {
            return this->fwrite == THREAD_RUN
            || this->fwrite == THREAD_STOP;
        });
        if (this->fwrite == THREAD_STOP)
            return;

        if (this->connectedDevice.second < 0 && this->marker.get_access_control().first != TOKEN_BIT_MARKER)
            continue;

        set_marker_param();

        std::stringstream ss;
        try {
            boost::archive::text_oarchive wr(ss);
            wr & this->marker;
        } catch (const boost::archive::archive_exception &ex) {
            continue;
        }
        write_port(ss.str());
    }
}

void Pseudoterminal::start_thread() {
    this->fwrite = THREAD_WAIT;
    this->fread = THREAD_RUN;
    this->reader = std::thread(&Pseudoterminal::thread_read, this);
    this->writer = std::thread(&Pseudoterminal::thread_write, this);
}

void Pseudoterminal::stop_thread() {
    THREAD_SET_FLAG_STOP(this->mutWrite, this->condition, this->fwrite);
    this->writer.join();
    
    THREAD_SET_FLAG_STOP(this->mutRead, this->condition, this->fread);
    this->reader.join();
}

void Pseudoterminal::set_marker_param() {

}

void Pseudoterminal::add_to_queue(const std::string &name, const std::string &value) {
    this->queue.push({name, value});
}

bool Pseudoterminal::is_connected() {
    return this->connectedDevice.second > 0;
}
