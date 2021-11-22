//
//  Menu.cpp
//  main
//
//  Created by Belousov Ilya on 7.11.21.
//

#include "Menu.hpp"

ApplicationMenu::ApplicationMenu() {
    this->menu = {
        {1, std::bind(&ApplicationMenu::send_msg, this)},
        {2, std::bind(&ApplicationMenu::send_pack, this)},
        {3, std::bind(&ApplicationMenu::send_frame, this)},

        {4, std::bind(&ApplicationMenu::open_port, this)},
        {5, std::bind(&ApplicationMenu::change_speed_in, this)},
        {6, std::bind(&ApplicationMenu::change_speed_out, this)},
        {7, std::bind(&ApplicationMenu::close_port, this)},

        {8, std::bind(&ApplicationMenu::connect_port, this)},
        {9, std::bind(&ApplicationMenu::disconnect_port, this)},
    };
}

std::string ApplicationMenu::input_line() const {
    clear_buffer();
    std::string line;
    std::cout << "Input line: ";
    std::cin >> line;
    return line;
}

std::string ApplicationMenu::input_line(const size_t &size) const {
    clear_buffer();
    char line[size];
    std::cout << "Input line: ";
    std::cin.getline(line, size);
    return line;
}

std::string ApplicationMenu::input_device_name() {
    std::cout << "Input device name: ";
    return input_line(MSG_ADRESS_SIZE);
}

int ApplicationMenu::input_number() const {
    int number;
    std::cout << "Input number: ";
    std::cin >> number;
    return number;
}

void ApplicationMenu::clear_buffer() const {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.ios_base::clear();
}

void ApplicationMenu::clear_terminal() const {
    system("clear");
}

void ApplicationMenu::confirmation() const {
    std::cout << "\nconfirm to continue...";
    clear_buffer();
    getchar();
    clear_terminal();
}

Package ApplicationMenu::create_pack() {
    std::string data = input_line(MAX_SIZE_PACK_DATA);

    Package P;
    P.change_data(data.c_str());
    P.set_sender(this->Ps.get_port_name());
    P.set_recipiend(input_device_name());
    P.start();

    return P;
}

Cropping ApplicationMenu::create_frame() {
    std::string data = input_line(MAX_SIZE_PACK_DATA);

    Cropping C;
    C.set_sender(this->Ps.get_port_name());
    C.set_recipiend(input_device_name());
    C.change_data(data.c_str());
    C.start();

    return C;
}

Msg ApplicationMenu::create_msg() {
    std::string data = input_line(MAX_SIZE_MSG_DATA);

    struct Msg msg;
    msg.set_data(data);
    msg.set_sender(Ps.get_port_name());
    msg.set_destination(input_device_name());

    return msg;
}

void ApplicationMenu::interface() {
    std::cout << "Port name: " << this->Ps.get_port_name();
    std::cout << "\n\t---Menu---\n";
    std::cout << "\n";
    std::cout << "1. Send msg.\n";
    std::cout << "2. Send pack.\n";
    std::cout << "3. Send frame.\n";
    std::cout << "\n";
    std::cout << "4. Open port.\n";
    std::cout << "5. Change speed in port.\n";
    std::cout << "6. Change speed in out.\n";
    std::cout << "7. Close port\n";
    std::cout << "\n";
    std::cout << "8. Connect port.\n";
    std::cout << "9. Disconnect port.\n";
    std::cout << "\n";
    std::cout << "10. Exit.\n";
}

void ApplicationMenu::send_msg() {
    check_open_device();
    struct Msg msg = create_msg();

    std::stringstream ss;
    boost::archive::text_oarchive wr(ss);
    wr & msg;

    this->Ps.add_to_queue(msg.Destination, ss.str());
}

void ApplicationMenu::send_pack() {
    check_open_device();

    std::string line = input_line(MAX_SIZE_PACK_DATA);

    Package pack = create_pack();
    std::stringstream ss;
    boost::archive::text_oarchive wr(ss);
    wr & pack;

    this->Ps.add_to_queue(pack.get_recipient(), ss.str());
}

void ApplicationMenu::send_frame() {
    check_open_device();

    std::string line = input_line(MAX_SIZE_FRAME_DATA);

    Cropping C = create_frame();
    std::stringstream ss;
    boost::archive::text_oarchive wr(ss);
    wr & C;

    this->Ps.add_to_queue(C.get_recipient(), ss.str());
}

void ApplicationMenu::open_port() {
    if (this->Ps.is_open())
        throw Error("Func: ApplicationMenu::open_port.", "Info: The port has already been created!");
    this->Ps.create_device();

    std::cout << "The port was created: " << this->Ps.get_port_name() << std::endl;
}

void ApplicationMenu::change_speed_in() {
    check_open_device();
    std::cout << "\tSet speed in\n";
    Ps.change_speed_in(input_number());
}

void ApplicationMenu::change_speed_out() {
    check_open_device();
    std::cout << "\tSet speed out\n";
    Ps.change_speed_out(input_number());
}

void ApplicationMenu::close_port() {
    if (!Ps.is_open())
        Error("Func: Main::close_port.", "Info: The port is already closed!\n");

    Ps.close_port();
    std::cout << "Port closed successfully" << std::endl;
}

void ApplicationMenu::connect_port() {
    check_open_device();

    std::cout << "\tDevice name\n";
    std::string device = input_line();

    if (!Ps.сompound(device)) {
        Error("Func: connect_port.", "Info: Connection failed!");
        return;
    }
    std::cout << "Connection successful!\n";
}

void ApplicationMenu::disconnect_port() {
    Ps.disconnection();
    std::cout << "Device disconnected successfully!\n";
}

void ApplicationMenu::check_open_device() {
    if (!Ps.is_open())
        throw Error("Func: check_open_device.", "Info: The port has not been created!");
}

void ApplicationMenu::start() {
    unsigned int answer = 0;
    while (true) {
        try {
            interface();
            answer = input_number();

            clear_terminal();
            if (std::cin.ios_base::fail()) {
                clear_buffer();
                throw Error("ApplicationMenu::start", "Not a number entered");
            }
            
            if (answer == this->menu.size() + 1)
                break;

            if (this->menu.find(answer) == menu.end())
                throw Error("ApplicationMenu::start", "Incorrect number");

            menu[answer]();
        } catch (const Error &ex) {
            std::cerr << "\t---Error---\n";
            std::cerr << "Where: " << ex.where() << "\n";
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

