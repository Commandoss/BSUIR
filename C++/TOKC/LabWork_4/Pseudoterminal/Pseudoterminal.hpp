//
//  Pseudoterminal.hpp
//  LabWork_4
//
//  Created by Belousov Ilya on 28.10.21.
//

#ifndef Pseudoterminal_hpp
#define Pseudoterminal_hpp

#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <memory>

#include "Package.hpp"
#include "PseudoterminalSettings.hpp"

class Pseudoterminal {
private:
    int descriptor;
    std::string port;

    PseudoterminalSettings *settings;
    
    int counter;
public:
    Pseudoterminal();
    ~Pseudoterminal();

    std::string create_port();
    std::string get_port_name();
private:
    void close_port();
    bool is_open();

    void change_speed(const int &speed);

    std::string read_port(const std::size_t size);
    size_t write_port(const std::string str);

private:
    void init_port_settings();
    void flush_port_buffer();
//    void error(std::string msg);
};

#endif /* Pseudoterminal_hpp */
