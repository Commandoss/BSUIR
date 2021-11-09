//
//  Menu.hpp
//  main
//
//  Created by Belousov Ilya on 7.11.21.
//

#ifndef Menu_hpp
#define Menu_hpp

#include <iostream>
#include <map>
#include <thread>
#include <sstream>

#include <boost/exception/diagnostic_information.hpp>

#include "Pseudoterminal.hpp"
#include "Package.hpp"
#include "Cropping.hpp"
#include "Msg.hpp"
#include "Error.hpp"

class ApplicationMenu {
private:
    Pseudoterminal Ps;
    std::stringstream ss;

    std::map<int, std::function<void()>> menu;

public:
    ApplicationMenu();

    void start();

    void interface();

    void send_msg();
    void send_pack();
    void send_frame();

    void accept_msg();
    void accept_pack();
    void accept_frame();

    void open_port();
    void close_port();

    void change_speed_in();
    void change_speed_out();

    void connect_port();
    void disconnect_port();

private:
    unsigned int select_device();
    void start_thread_read();

    void out_list_connect_device();

    Package create_pack();
    Cropping create_frame();
    MSG create_msg();

    void check_connected_devices();
    void check_open_device();

private:
    std::string input_line() const;
    std::string input_line(const size_t &size) const;

    int input_number() const;

private:
    void clear_buffer() const;
    void clear_terminal() const;
    void confirmation() const;
};

#endif /* Menu_hpp */
