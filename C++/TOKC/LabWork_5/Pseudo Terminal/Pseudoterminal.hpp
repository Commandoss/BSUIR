//
//  Pseudoterminal.hpp
//  LabWork_4
//
//  Created by Belousov Ilya on 28.10.21.
//

#ifndef Pseudoterminal_hpp
#define Pseudoterminal_hpp

#include <unistd.h>
#include <fcntl.h>
#include <memory>
#include <map>
#include <iostream>
#include <sstream>
#include <ctime>
#include <chrono>
#include <queue>
#include <fstream>

#include "PseudoterminalSettings.hpp"
#include "Marking.hpp"
#include "ThreadControl.hpp"

class Pseudoterminal {
protected:

    int descriptor;
    std::string port;
    PseudoterminalSettings *settings;

    std::pair<std::string, int> connectedDevice;

    std::queue<std::pair<std::string, std::string>> queue;

    std::thread reader, writer;
    unsigned int fread, fwrite;
    std::mutex mutRead, mutWrite;
    std::condition_variable condition;

    Marking marker;
public:
    Pseudoterminal();
    ~Pseudoterminal();

    void create_device();
    unsigned int create_terminal();

    std::string get_port_name();

    bool сompound(const std::string &port);
    void disconnection();

    std::string read_port(const std::size_t &size);
    size_t write_port(const std::string &str);

    void change_speed_in(const size_t &speed);
    void change_speed_out(const size_t &speed);

    bool close_port();
    bool is_open();
    bool is_connected();

    void add_to_queue(const std::string &name, const std::string &value);

protected:
    void init_port_settings();

    void start_thread();
    void stop_thread();

    void thread_read();
    void thread_write();

    void wait() const noexcept;

    void set_marker_param();
};

#endif /* Pseudoterminal_hpp */
