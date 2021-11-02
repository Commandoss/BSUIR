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
#include <map>
#include <sstream>

#include "Package.hpp"
#include "PseudoterminalSettings.hpp"

class Pseudoterminal {
private:
    int descriptor;
    std::string port;

    PseudoterminalSettings *settings;
    
    int counter;

    std::map<unsigned int, std::pair<std::string, int>> lnetwork;
    std::stringstream buffer;
public:
    Pseudoterminal();
    ~Pseudoterminal();

    bool create_port();
    std::string get_port_name();

    void connect(const std::string &port);
    void disconnect(const unsigned int &device);

    std::map<unsigned int, std::pair<std::string, int>> get_list_network() const;

    std::string read_port(const std::size_t &size);
    size_t write_port(const std::string &str, const unsigned int &device);

    void change_speed_in(const size_t &speed);
    void change_speed_out(const size_t &speed);

    void close_port();
    bool is_open();

private:
    void init_port_settings();
    void flush_port_buffer();
//    void error(std::string msg);
};

#endif /* Pseudoterminal_hpp */
