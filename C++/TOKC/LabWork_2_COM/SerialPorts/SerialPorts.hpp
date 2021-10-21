//
//  SerialPorts.hpp
//  LabWork_1
//
//  Created by Belousov Ilya on 11.09.21.
//

#ifndef SerialPorts_hpp
#define SerialPorts_hpp

#include <string>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include "PseudoPSettings.hpp"
#include "Package.hpp"

class SerialPorts
{
private:
    int descriptor;
    std::string port;

    PseudoPSettings *settings;

public:
    SerialPorts();
    SerialPorts(std::string port);
    ~SerialPorts();

    void start_port();

    void open_port();
    void open_port(const std::string port);

    void close_port();
    bool is_open();

    size_t write_port(const std::string str);
    std::string read_port(const size_t size);

//    int chech_port_buffer();
    void change_speed(const int &speed);
private:
    void flush_port_buffer();
    void init_port_settings();
//    bool change_law_port(const fs::path path, const mode_t mode);
    void error(const std::string msg);
};
	
#endif
