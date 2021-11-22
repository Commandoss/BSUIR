//
//  Menu.hpp
//  main
//
//  Created by Belousov Ilya on 7.11.21.
//

#ifndef Menu_hpp
#define Menu_hpp

#include <iostream>
#include <boost/exception/diagnostic_information.hpp>

#include "Pseudoterminal.hpp"

class ApplicationMenu {
private:
    Pseudoterminal Ps;
    std::map<int, std::function<void()>> menu;

public:
    ApplicationMenu();
    
    void start();

private:
    void interface();

    void send_msg();
    void send_pack();
    void send_frame();

    void open_port();
    void close_port();

    void change_speed_in();
    void change_speed_out();

    void connect_port();
    void disconnect_port();

private:
    Package create_pack();
    Cropping create_frame();
    Msg create_msg();

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

#endif /* Menu_hpp */
