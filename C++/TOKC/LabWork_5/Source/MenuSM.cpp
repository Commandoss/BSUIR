//
//  MenuSM.cpp
//  main
//
//  Created by Belousov Ilya on 18.11.21.
//

#include "MenuSM.hpp"

ApplicationMenuSM::ApplicationMenuSM() {
    this->menu = {
        {1, std::bind(&ApplicationMenuSM::open_port, this)},
        {2, std::bind(&ApplicationMenuSM::change_speed_in, this)},
        {3, std::bind(&ApplicationMenuSM::change_speed_out, this)},
        {4, std::bind(&ApplicationMenuSM::close_port, this)},

        {5, std::bind(&ApplicationMenuSM::connect_port, this)},
        {6, std::bind(&ApplicationMenuSM::disconnect_port, this)},
    };
}

std::string ApplicationMenuSM::input_line() const {
    clear_buffer();
    std::string line;
    std::cout << "Input: ";
    std::cin >> line;
    return line;
}

std::string ApplicationMenuSM::input_line(const size_t &size) const {
    clear_buffer();
    char line[size];
    std::cout << "Input: ";
    std::cin.getline(line, size);
    return line;
}

std::string ApplicationMenuSM::input_device_name() {
    std::cout << "Input device name: ";
    return input_line(MSG_ADRESS_SIZE);
}

int ApplicationMenuSM::input_number() const {
    int number;
    std::cout << "Input: ";
    std::cin >> number;
    return number;
}

void ApplicationMenuSM::clear_buffer() const {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.ios_base::clear();
}

void ApplicationMenuSM::clear_terminal() const {
    system("clear");
}

void ApplicationMenuSM::confirmation() const {
    std::cout << "\nconfirm to continue...";
    clear_buffer();
    getchar();
    clear_terminal();
}

void ApplicationMenuSM::interface() {
    std::cout << "Stantion monitor name: " << this->Sm.get_port_name();
    std::cout << "\n\t---Menu---\n";
    std::cout << "1. Create station.\n";
    std::cout << "2. Change speed in station.\n";
    std::cout << "3. Change speed out station.\n";
    std::cout << "4. Close port\n";
    std::cout << "\n";
    std::cout << "5. Connect device.\n";
    std::cout << "6. Disconnect device.\n";
    std::cout << "\n";
    std::cout << "7. Exit.\n";
}

void ApplicationMenuSM::open_port() {
    this->Sm.create_device();
    std::cout << "The port was created: " << this->Sm.get_port_name() << std::endl;
}

void ApplicationMenuSM::change_speed_in() {
    check_open_device();
    std::cout << "\tSet speed in\n";
    Sm.change_speed_in(input_number());
}

void ApplicationMenuSM::change_speed_out() {
    check_open_device();
    std::cout << "\tSet speed out\n";
    Sm.change_speed_out(input_number());
}

void ApplicationMenuSM::close_port() {
    if (!Sm.is_open())
        throw Error("Func: Main::close_port.", "Info: The port is already closed!\n");

    Status s;
    s.set_disconnect();
    std::stringstream ss;
    boost::archive::text_oarchive wr(ss);
    wr & s;

    Sm.add_to_queue(Sm.get_port_name(), ss.str());
    Sm.close_port();
    std::cout << "Port closed successfully" << std::endl;
}

void ApplicationMenuSM::connect_port() {
    check_open_device();

    std::cout << "\tDevice name\n";
    std::string device = input_line();

    if (!Sm.сompound(device))
        throw Error("Func: connect_port.", "Info: Connection failed!");

    std::cout << "Connection successful!\n";
}

void ApplicationMenuSM::disconnect_port() {
    Sm.disconnection();
    std::cout << "Device disconnected successfully!\n";
}

void ApplicationMenuSM::check_open_device() {
    if (!Sm.is_open())
        throw Error("Func: check_open_device.", "Info: The port has not been created!");
}

void ApplicationMenuSM::start() {
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

