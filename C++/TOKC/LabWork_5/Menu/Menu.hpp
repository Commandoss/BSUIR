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

#include "Pseudoterminal.hpp"
#include "Package.hpp"
#include "Cropping.hpp"

class ApplicationMenu {
private:
    Pseudoterminal Ps;
    std::stringstream ss;

    boost::archive::text_oarchive wr;
    boost::archive::text_iarchive rd;

public:
    explicit ApplicationMenu();

    void interface();

    void send_msg();
    void send_pack();
    void send_frame();

    void accept_msg();
    void accept_pack();
    void accept_frame();

    void open_port(Pseudoterminal &Ps);
    void close_port(Pseudoterminal &Ps);

    void change_speed_in(Pseudoterminal &Ps);
    void change_speed_out(Pseudoterminal &Ps);

    void connect_port(Pseudoterminal &Ps);
    void disconnect_port(Pseudoterminal &Ps);

private:
    unsigned int select_device();
    void start_thread_read(Pseudoterminal &Ps);

    void out_list_connect_device(Pseudoterminal &Ps);

    Package& create_pack();
    Cropping& create_frame();

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
