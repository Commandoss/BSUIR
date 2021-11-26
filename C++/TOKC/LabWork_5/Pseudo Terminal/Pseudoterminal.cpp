//
//  Pseudoterminal.cpp
//  LabWork_4
//
//  Created by Belousov Ilya on 28.10.21.
//

#include "Pseudoterminal.hpp"

Pseudoterminal::Pseudoterminal() {
    this->descriptor = -1;
    this->connectedDevice = {"", -1};
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
        throw Error("Pseudoterminal::create_terminal: open port.");

    if (grantpt(descriptor) < 0)
        throw Error("Pseudoterminal::create_terminal: grantpt.");

    if (unlockpt(descriptor) < 0)
        throw Error("Pseudoterminal::create_terminal: unlockpt.");

    this->port = ptsname(descriptor);
    if (this->port.empty())
        throw Error("Pseudoterminal::create_terminal: ptsname.");

    init_settings();
    return descriptor;
}

void Pseudoterminal::create_port() {
    if (this->is_open())
        throw Error("Pseudoterminal::create_port: The pseudo terminal has already been created.");

    this->descriptor = create_terminal();
    thread_start();
}

bool Pseudoterminal::is_open() {
    return this->descriptor > 0;
}

std::string Pseudoterminal::get_port_name() {
    return this->port;
}

bool Pseudoterminal::connect(const std::string &port) {
    if (is_connected())
        throw Error("Pseudoterminal::сompound: Connection already established.");
    if (get_port_name() == port)
        throw Error("Pseudoterminal::сompound: Can't connect to myself");

    int descriptor = 0;
    for (auto counter = 0; counter < 10; counter++) {
        descriptor = open(port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
        if (descriptor < 0) {
            std::cerr << "Func: Pseudoterminal::connect.\n" << "Info: The device is not available or does not exist on the network.\n";
            wait();
            continue;
        }

        this->connectedDevice = {port, descriptor};
        return true;
    }
    return false;
}

void Pseudoterminal::close_port() {
    if (!this->is_open())
        return;

    thread_stop();
    disconnect();

    close(this->descriptor);

    this->descriptor = -1;
    this->port.clear();
}

void Pseudoterminal::disconnect() {
    if (!is_connected())
        throw Error("Pseudoterminal::disconnection: Device is not connected.");

    close(this->connectedDevice.second);
    this->connectedDevice = {"", -1};
}

std::string Pseudoterminal::read_port(const size_t &size) {
    if (!this->is_open())
        throw Error("Pseudoterminal::read_port: Port no open.");

    long n = 0;
    char buffer[size + 1];
    if ((n = read(this->descriptor, &buffer, size)) < 0)
        throw Error("Pseudoterminal::read_port: Failed to read.");

    buffer[n] += '\0';
    return buffer;
}

size_t Pseudoterminal::write_port(const std::string &str) {
    if (this->connectedDevice.second < 0)
        throw Error("Pseudoterminal::write_port: No connection has been established with this device.");

    wait();
    size_t count = write(this->connectedDevice.second, str.c_str(), str.size());
    wait();

    return count;
}

void Pseudoterminal::init_settings() {
    int settingDescriptor = open(this->port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    this->settings = new PseudoterminalSettings(settingDescriptor);
    if (this->settings == nullptr)
        throw Error("Pseudoterminal::init_port_settings: memory not allocade.");
}

void Pseudoterminal::change_speed_out(const size_t &speed) {
    if (!is_open())
        throw Error("Pseudoterminal::change_speed_out: port no open.");

    this->settings->set_speed_out_port(speed);
}

void Pseudoterminal::change_speed_in(const size_t &speed) {
    if (!is_open())
        throw Error("Pseudoterminal::change_speed_in: port no open.");

    this->settings->set_speed_in_port(speed);
}

void Pseudoterminal::wait() const noexcept {
    unsigned int CWmin = 15, CWmax = 1023;
    std::srand((unsigned int)std::time(NULL));

    unsigned int sleep = std::rand() % CWmax + CWmin;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
}

void Pseudoterminal::set_marker_param() {
    if (this->queueWrite.size() == 0)
        return;

    queueWrite.pop();
}

void Pseudoterminal::thread_read() {
    std::unique_lock<std::mutex> uq(this->mutRead);
    while (true) {
        std::stringstream ss;

        condition.wait(uq, [this] { return this->fread == THREAD_RUN
            || this->fread == THREAD_STOP;
        });
        if (this->fread == THREAD_STOP)
            return;

        std::string buffer(read_port(SIZE_READ_PORT));
        ss << buffer;

        try {
            boost::archive::text_iarchive rd(ss);
            rd & this->marker;
        } catch (const boost::archive::archive_exception &ex) {
            get_status(buffer);
            write_port(buffer);
            continue;
        }

        if (this->marker.get_id() != 0)
            add_to_queue_read(this->marker.get_type(), this->marker.get_data());

        THREAD_SET_FLAG_RUN(this->mutWrite, this->condition, this->fwrite);
    }
}

void Pseudoterminal::thread_write() {
    std::unique_lock<std::mutex> uq(this->mutWrite);
    while (true) {
        std::stringstream ss;
        condition.wait(uq, [this] {
            return this->fwrite == THREAD_RUN
            || this->fwrite == THREAD_STOP;
        });
        if (this->fwrite == THREAD_STOP)
            return;

        if (this->connectedDevice.second < 0)
            continue;

        if (this->marker.get_access_control().first == TOKEN_BIT_MARKER && this->queueWrite.size() != 0)
            set_marker_param();
        else if (this->marker.get_access_control().first == TOKEN_BIT_FRAME &&
                 get_port_name() == this->marker.get_source_adress()) {}
            // функция освобождения маркера
        else if (this->marker.get_access_control().first == TOKEN_BIT_FRAME &&
                 get_port_name() == this->marker.get_destination_adress()) {}
        // функция принятия данных в чтение


        try {
            boost::archive::text_oarchive wr(ss);
            wr & this->marker;
        } catch (const boost::archive::archive_exception &ex) {
            continue;
        }
        write_port(ss.str());
        this->fwrite = THREAD_WAIT;
    }
}

void Pseudoterminal::thread_start() {
    this->fwrite = THREAD_WAIT;
    this->fread = THREAD_RUN;
    this->reader = std::thread(&Pseudoterminal::thread_read, this);
    this->writer = std::thread(&Pseudoterminal::thread_write, this);
}

void Pseudoterminal::thread_stop() {
    if (this->writer.joinable()){
        THREAD_SET_FLAG_STOP(this->mutWrite, this->condition, this->fwrite);
        this->writer.join();
    }

    if (this->reader.joinable()) {
        THREAD_SET_FLAG_STOP(this->mutRead, this->condition, this->fread);
        this->reader.join();
    }
}

void Pseudoterminal::add_to_queue_write(const std::string &name, const std::string &value) {
    this->queueWrite.push({name, value});
}

void Pseudoterminal::add_to_queue_read(const unsigned int &type, const std::string value) {
    this->queueRead.push({type, value});
}

bool Pseudoterminal::is_connected() {
    return this->connectedDevice.second > 0;
}

std::pair<unsigned int, std::string> Pseudoterminal::get_data_queue_read() {
    if (queueRead.size() == 0)
        throw Error("Pseudoterminal::get_data_queue_read: No data available.");

    std::pair<unsigned int, std::string> data = this->queueRead.front();
    this->queueRead.pop();
    return data;
}

void Pseudoterminal::get_status(const std::string &buffer) {
    std::stringstream ss(buffer);
    boost::archive::text_iarchive rd(ss);
    Status S;
    try {
        rd & S;
    } catch (const boost::archive::archive_exception &ex) {
        return;
    }
    
    write_port(buffer);
    if (S.Flag == disconnection) {
        this->fwrite = THREAD_STOP;
        this->fread = THREAD_STOP;
    }
}

// param
