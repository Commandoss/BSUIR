//
//  Menu.cpp
//  main
//
//  Created by Belousov Ilya on 7.11.21.
//

#include "Menu.hpp"

ApplicationMenu::ApplicationMenu() {
    this->ss.clear();
    this->menu = {
        {1, std::bind(&ApplicationMenu::send_msg, this)},
        {2, std::bind(&ApplicationMenu::send_pack, this)},
        {3, std::bind(&ApplicationMenu::send_frame, this)},

        {4, std::bind(&ApplicationMenu::accept_msg, this)},
        {5, std::bind(&ApplicationMenu::accept_pack, this)},
        {6, std::bind(&ApplicationMenu::accept_frame, this)},

        {7, std::bind(&ApplicationMenu::open_port, this)},
        {8, std::bind(&ApplicationMenu::change_speed_in, this)},
        {9, std::bind(&ApplicationMenu::change_speed_out, this)},
        {10, std::bind(&ApplicationMenu::close_port, this)},

        {11, std::bind(&ApplicationMenu::connect_port, this)},
        {12, std::bind(&ApplicationMenu::disconnect_port, this)},
        {13, std::bind(&ApplicationMenu::out_list_connect_device, this)},
    };
}

std::string ApplicationMenu::input_line() const {
    std::string line;
    std::cout << "Input line: ";
    std::cin >> line;
    return line;
}

std::string ApplicationMenu::input_line(const size_t &size) const {
    char line[size];
    std::cout << "Input line: ";
    std::cin.getline(line, size);
    return line;
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

unsigned int ApplicationMenu::select_device() {
    std::cout << "Select Device:\n";
    out_list_connect_device();
    return input_number();
}

Package ApplicationMenu::create_pack() {
    unsigned int device = select_device();
    std::string data = input_line(MAX_SIZE_PACK_DATA);

    Package P;
    P.change_data(data);
    P.set_sender(this->Ps.get_port_name());
    P.set_recipiend(this->Ps.get_name_device(device));
    P.start();

    return P;
}

Cropping ApplicationMenu::create_frame() {
    unsigned int device = select_device();
    std::string data = input_line(MAX_SIZE_PACK_DATA);

    Cropping C;
    C.set_sender(this->Ps.get_port_name());
    C.set_recipiend(this->Ps.get_name_device(device));
    C.change_data(data);
    C.start();

    return C;
}

MSG ApplicationMenu::create_msg() {
    std::string data = input_line(MAX_SIZE_MSG_DATA);

    struct MSG msg;
    msg.set_data(data);

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
    std::cout << "4. Accept msg.\n";
    std::cout << "5. Accept pack\n";
    std::cout << "6. Accept frame.\n";
    std::cout << "\n";
    std::cout << "7. Open port.\n";
    std::cout << "8. Change speed in port.\n";
    std::cout << "9. Change speed in out.\n";
    std::cout << "10. Close port\n";
    std::cout << "\n";
    std::cout << "11. Connect port.\n";
    std::cout << "12. Disconnect port.\n";
    std::cout << "13. List connect device.\n";
    std::cout << "\n";
    std::cout << "14. Exit.\n";
    std::cout << "Answer: ";
}

void ApplicationMenu::send_msg() {
    check_connected_devices();

    struct MSG msg = create_msg();
    boost::archive::text_oarchive wr(this->ss);
    wr & msg;

    this->Ps.write_port(this->ss.str(), select_device());
}

void ApplicationMenu::send_pack() {
    check_connected_devices();

    std::string line = input_line(MAX_SIZE_PACK_DATA);
    unsigned int device = select_device();

    Package pack = create_pack();
    boost::archive::text_oarchive wr(this->ss);
    wr & pack;

    std::cout << Ps.write_port(this->ss.str(), device);
}

void ApplicationMenu::send_frame() {
    check_connected_devices();

    std::string line = input_line(MAX_SIZE_FRAME_DATA);
    unsigned int device = select_device();

    Cropping C = create_frame();
    boost::archive::text_oarchive wr(this->ss);
    wr & C;

    Ps.write_port(this->ss.str(), device);
}

void ApplicationMenu::accept_msg() {
    check_open_device();

    std::cout << "Waiting for msg to be received.\n";
    this->ss << Ps.read_port(MAX_SIZE_MSG);

    struct MSG msg;
    boost::archive::text_iarchive rd(this->ss);
    rd & msg;

    std::cout << msg;
}

void ApplicationMenu::accept_pack() {
    check_open_device();

    std::cout << "Waiting for package to be received.\n";
    this->ss << Ps.read_port(MAX_SIZE_PACK);

    Package P;
    boost::archive::text_iarchive rd(this->ss);
    rd & P;

    std::cout << P;
}

void ApplicationMenu::accept_frame() {
    check_open_device();

    std::cout << "Waiting to receive a frame.\n";
    this->ss << Ps.read_port(MAX_SIZE_FRAME);

    Cropping C;
    boost::archive::text_iarchive rd(this->ss);
    rd & C;

    std::cout << C;
}

void ApplicationMenu::open_port() {
    check_open_device();
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

    if (!Ps.connect(device)) {
        Error("Func: connect_port.", "Info: Connection failed!");
        return;
    }
    std::cout << "Connection successful!\n";
}

void ApplicationMenu::disconnect_port() {
    check_connected_devices();

    Ps.disconnect(select_device());
    std::cout << "Device disconnected successfully!\n";
}

void ApplicationMenu::out_list_connect_device() {
    check_connected_devices();

    std::cout << "\tList device\n";
    std::map listDevice = Ps.get_list_network();
    int counter = 0;
    for (auto device : listDevice) {
        std::cout << counter << "." << device.second.first << "\n";
        counter++;
    }
}

//bool ApplicationMenu::check_status(string &str) {
//    stringstream ss(str);
//    status s;
//    try {
//        boost::archive::text_iarchive rd(ss);
//        rd & s;
//        if (s.flag == connect) {
//            Ps.accept_connect(s.sender);
//        } else if (s.flag == disconnect) {
//            Ps.accept_disconnect(Ps.find_device(s.sender));
//        } else if (s.flag == error) {
//
//        }
//    } catch (...) {
//        return false;
//    }
//
//    return true;
//}

void ApplicationMenu::check_connected_devices() {
    check_open_device();

    if (Ps.get_count_connect() == 0)
        throw Error("Func: send_frame.", "Info: Connect to at least one device to transfer data!");

}

void ApplicationMenu::check_open_device() {
    if (!Ps.is_open())
        throw Error("Func: check_open_device.", "Info: The port has not been created!");
}

void ApplicationMenu::start() {
    while (true) {
        try {

        } catch (const Error &err) {
            std::cerr << "\t---Error---\n";
            std::cerr << "Where: " << err.where() << "\n";
            std::cerr << "What: " << err.what() << "\n";
            std::cerr << "\t---End---\n";
            confirmation();

        } catch (const boost::exception &ex) {
            std::cerr << "\t---Error boost---\n";
            std::cerr << "What: " << boost::diagnostic_information(ex) << "\n";
            std::cerr << "\t---End---\n";
            confirmation();

        }
    }
}
