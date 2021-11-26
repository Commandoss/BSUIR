//
//  Menu.cpp
//  main
//
//  Created by Belousov Ilya on 7.11.21.
//

#include "MenuPS.hpp"

AppMenuPS::AppMenuPS() {
    this->menu = {
        {1, std::bind(&AppMenuPS::send_msg, this)},
        {2, std::bind(&AppMenuPS::send_frame, this)},

        {3, std::bind(&AppMenuPS::open_port, this)},
        {4, std::bind(&AppMenuPS::change_speed_in, this)},
        {5, std::bind(&AppMenuPS::change_speed_out, this)},
        {6, std::bind(&AppMenuPS::close_port, this)},

        {7, std::bind(&AppMenuPS::connect_port, this)},
        {8, std::bind(&AppMenuPS::disconnect_port, this)},
        {9, std::bind(&AppMenuPS::read_received_data, this)},
    };
}

std::string AppMenuPS::input_device_name() {
    std::cout << "Input device name\n";
    return input_line(ADRESS_SIZE);
}

Cropping AppMenuPS::create_frame() {
    std::string data = input_line(MAX_SIZE_FRAME_DATA);

    Cropping C;
    C.set_sender(this->Ps.get_port_name());
    C.set_recipiend(input_device_name());
    C.change_data(data.c_str());
    C.start();

    return C;
}

Msg AppMenuPS::create_msg() {
    struct Msg msg;
    msg.set_data(input_line(MAX_SIZE_MSG_DATA));
    return msg;
}

void AppMenuPS::interface() {
    std::cout << "Port name: " << this->Ps.get_port_name();
    std::cout << "\n\t---Menu---\n";
    std::cout << "\n";
    std::cout << "1. Send msg.\n";
    std::cout << "2. Send frame.\n";
    std::cout << "\n";
    std::cout << "3. Open port.\n";
    std::cout << "4. Change speed in port.\n";
    std::cout << "5. Change speed in out.\n";
    std::cout << "6. Close port\n";
    std::cout << "\n";
    std::cout << "7. Connect port.\n";
    std::cout << "8. Disconnect port.\n";
    std::cout << "9. Read received data.\n";
    std::cout << "\n";
    std::cout << "10. Exit.\n";
}

void AppMenuPS::send_msg() {
    check_open_device();
    struct Msg msg = create_msg();

    std::stringstream ss;
    boost::archive::text_oarchive wr(ss);
    wr & msg;

    this->Ps.add_to_queue_write(input_device_name(), ss.str());
}

void AppMenuPS::send_frame() {
    check_open_device();

    std::string line = input_line(MAX_SIZE_FRAME_DATA);

    Cropping C = create_frame();
    std::stringstream ss;
    boost::archive::text_oarchive wr(ss);
    wr & C;

    this->Ps.add_to_queue_write(C.get_recipient(), ss.str());
}

void AppMenuPS::open_port() {
    if (this->Ps.is_open())
        throw Error("ApplicationMenu::open_port: The port has already been created.");
    this->Ps.create_port();

    std::cout << "The port was created: " << this->Ps.get_port_name() << std::endl;
}

void AppMenuPS::change_speed_in() {
    check_open_device();
    std::cout << "\tSet speed in\n";
    Ps.change_speed_in(input_number());
}

void AppMenuPS::change_speed_out() {
    check_open_device();
    std::cout << "\tSet speed out\n";
    Ps.change_speed_out(input_number());
}

void AppMenuPS::close_port() {
    if (!Ps.is_open())
        throw Error("AppMenuPS::close_port: The port is already closed.");

    Ps.close_port();
    std::cout << "Port closed successfully" << std::endl;
}

void AppMenuPS::connect_port() {
    check_open_device();

    std::cout << "\tDevice name\n";
    std::string device = input_line();

    if (!Ps.connect(device))
        throw Error("AppMenuPS::connect_port: Connection failed.");

    std::cout << "Connection successful!\n";
}

void AppMenuPS::disconnect_port() {
    Ps.disconnect();
    std::cout << "Device disconnected successfully!\n";
}

void AppMenuPS::check_open_device() {
    if (!Ps.is_open())
        throw Error("AppMenuPS::check_open_device: The port has not been created.");
}

void AppMenuPS::start() {
    unsigned int answer = 0;
    while (true) {
        try {
            interface();
            answer = input_number(1, (int)this->menu.size() + 1);

            clear_terminal();

            menu[answer]();
        } catch (const Error &ex) {
            std::cerr << "\t---Error---\n";
            std::cerr << "What: " << ex.what() << "\n";
            std::cerr << "\t---End---\n\n";

        } catch (const boost::archive::archive_exception &ex) {
            std::cerr << "\t---Error boost---\n";
            std::cerr << "What: " << boost::diagnostic_information(ex);
            std::cerr << "\t---End---\n\n";

        }
        confirmation();
    }
}

void AppMenuPS::read_received_data() {
    auto data = this->Ps.get_data_queue_read();
    std::stringstream ss(data.second);
    boost::archive::text_iarchive rd(ss);

    if (data.first == MSG_TYPE) {
        Msg msg;
        rd & msg;
        std::cout << msg;
    } else if (data.first == FRAME_TYPE) {
        Cropping frame;
        rd & frame;
        std::cout << frame;
    }
}
