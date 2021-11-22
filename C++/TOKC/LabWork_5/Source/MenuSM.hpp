//
//  MenuSM.hpp
//  main
//
//  Created by Belousov Ilya on 18.11.21.
//

#ifndef MenuSM_hpp
#define MenuSM_hpp

#include <iostream>
#include <boost/exception/diagnostic_information.hpp>

#include "StationMonitor.hpp"

class ApplicationMenuSM {
private:
    StationMonitor Sm;
    std::map<int, std::function<void()>> menu;

public:
    ApplicationMenuSM();
    void start();

private:
    void interface();

    void open_port();
    void close_port();

    void change_speed_in();
    void change_speed_out();

    void connect_port();
    void disconnect_port();

private:
    void check_open_device();

private:
    std::string input_line() const;
    std::string input_line(const size_t &size) const;

    int input_number() const;

    std::string input_device_name();

private:
    void clear_buffer() const;
    void clear_terminal() const;
    void confirmation() const;
};

#endif /* MenuSM_hpp */
