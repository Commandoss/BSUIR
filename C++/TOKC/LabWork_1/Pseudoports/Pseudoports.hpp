//
//  Pseudoports.hpp
//  writer
//
//  Created by Belousov Ilya on 30.09.21.
//

#ifndef Pseudoports_hpp
#define Pseudoports_hpp

#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <memory>

#include "PseudoPSettings.hpp"

class Pseudoports {
private:
    int masterDescriptor;
    std::string port;

    PseudoPSettings *settings;

public:
    Pseudoports();
    ~Pseudoports();

    std::string create_port();
    void close_port();
    bool is_open();

    std::string get_port_name();

    std::string read_port(const std::size_t size);
    size_t write_port(const std::string str);

private:
    void init_port_settings();
    void flush_port_buffer();
    void error(std::string msg);
};



#endif /* Pseudoports_hpp */
