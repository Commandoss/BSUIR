//
//  Menu.cpp
//  main
//
//  Created by Belousov Ilya on 7.11.21.
//

#include "Menu.hpp"

ApplicationMenu::ApplicationMenu() {

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

Package& ApplicationMenu::create_pack() {
    unsigned int device = select_device();
    std::string data = input_line(MAX_SIZE_PACK_DATA);

    Package P;
    P.change_data(data);
    P.set_sender(this->Ps.get_port_name());
    P.set_recipiend(this->Ps.get_name_device(device));
    P.start();

    return P;
}

Cropping& ApplicationMenu::create_frame() {
    unsigned int device = select_device();
    std::string data = input_line(MAX_SIZE_PACK_DATA);

    Cropping C;
    C.set_sender(this->Ps.get_port_name());
    C.set_recipiend(this->Ps.get_name_device(device));
    C.change_data(data);
    C.start();

    return C;
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
    if (!this->Ps.is_open()) {
        Error::char_arr_error("Func: send_msg.\nInfo: The port has not been created!");
        return;
    }
    if (this->Ps.get_count_connect() == 0) {
        Error::char_arr_error("Func: send_msg.\nInfo: Connect to at least one device to transfer data!");
        return;
    }

    std::string msg = input_line();

    this->Ps.write_port(msg, select_device());
}

void ApplicationMenu::send_pack() {
    if (!this->Ps.is_open()) {
        Error::char_arr_error("Func: send_pack.\nInfo: The port has not been created!");
        return;
    }
    if (this->Ps.get_count_connect() == 0) {
        Error::char_arr_error("Func: send_pack.\nInfo: Connect to at least one device to transfer data!");
        return;
    }

    std::string line = input_line(MAX_SIZE_PACK_DATA);
    unsigned int device = select_device();

    Package pack = create_pack();
    this->wr & pack;

    std::cout << Ps.write_port(this->ss.str(), device);
}

void ApplicationMenu::send_frame() {
    if (!Ps.is_open()) {
        Error::char_arr_error("Func: send_frame.\nInfo: The port has not been created!");
        return;
    }
    if (Ps.get_count_connect() == 0) {
        Error::char_arr_error("Func: send_frame.\nInfo: Connect to at least one device to transfer data!");
        return;
    }

    std::string line = input_line(MAX_SIZE_FRAME_DATA);
    unsigned int device = select_device();

    Cropping C = create_frame();
    this->wr & C;

    Ps.write_port(this->ss.str(), device);
}

void accept_msg(Pseudoterminal &Ps) {
    if (!Ps.is_open()) {
        Error::char_arr_error("Func: accept_msg.\nInfo: The port has not been created!");
        return;
    }

    size_t size;
    cout << "Input size msg: ";
    cin >> size;

    cout << "Msg: " << Ps.read_port(size);
}

void accept_pack(Pseudoterminal &Ps) {
    if (!Ps.is_open()) {
        Error::char_arr_error("Func: accept_msg.\nInfo: The port has not been created!");
        return;
    }
    cout << "Waiting for package to be received.\n";
    string str(Ps.read_port(MAX_SIZE_PACK));
    stringstream ss(str);
    Package P;
    try {
        boost::archive::text_iarchive rd(ss);
        rd & P;
    } catch (...) {
        if (check_status(Ps, str))
            return;
        Error::char_arr_error("Func: accept_pack.\nInfo: The package was damaged!");
        Ps.collision();
        return;
    }

    cout << P;
}

void accept_frame(Pseudoterminal &Ps) {
    if (!Ps.is_open()) {
        Error::char_arr_error("Func: accept_msg.\nInfo: The port has not been created!");
        return;
    }
    cout << "Waiting to receive a frame.\n";
    string str = Ps.read_port(MAX_SIZE_FRAME);
    stringstream ss(str);

    Cropping C;
    boost::archive::text_iarchive rd(ss);
    try {
        rd & C;
    } catch (...) {
        if (check_status(Ps, str))
            return;
        Error::char_arr_error("Func: accept_pack.\nInfo: The frame was damaged!");
        Ps.collision();
        return;
    }
    cout << C;
}

void open_port(Pseudoterminal &Ps) {
    if (!Ps.create_port())
        return;

    cout << "The port was created: " << Ps.get_port_name() << endl;
}

void change_speed_in(Pseudoterminal &Ps) {
    speed_t speed;
    cout << "Set speed in: ";
    cin >> speed;
    Ps.change_speed_in(speed);
}

void change_speed_out(Pseudoterminal &Ps) {
    speed_t speed;
    cout << "Set speed out: ";
    cin >> speed;
    Ps.change_speed_out(speed);
}

void close_port(Pseudoterminal &Ps) {
    if (!Ps.is_open()) {
        Error::char_arr_error("Func: Main::close_port.\nInfo: The port is already closed!\n");
        return;
    }

    Ps.close_port();
    cout << "Port closed successfully" << endl;
}

void connect_port(Pseudoterminal &Ps) {
    if (!Ps.is_open()) {
        Error::char_arr_error("Func: send_frame.\nInfo: The port has not been created!");
        return;
    }

    string device;
    cout << "Input device name: ";
    cin >> device;

    if (!Ps.connect(device)) {
        Error::char_arr_error("Func: connect_port.\nInfo: Connection failed!");
        return;
    }
    cout << "Connection successful!\n";
}

void disconnect_port(Pseudoterminal &Ps) {
    if (!Ps.is_open()) {
        Error::char_arr_error("Func: disconnect port.\nInfo: The port has not been created!");
        return;
    }
    if (Ps.get_count_connect() == 0) {
        Error::char_arr_error("Func: disconnect port.\nInfo: Connect to at least one device to transfer data!");
        return;
    }

    cout << "Select Device:\n";
    out_list_connect_device(Ps);

    unsigned int device;
    cout << "Answer: ";
    cin >> device;

    Ps.disconnect(device);
    cout << "Device disconnected successfully!\n";
}

void start_thread_read(Pseudoterminal &Ps) {
    //    thread thRead(&Pseudoterminal::read_port, Ps, MAX_SIZE_PACK_DATA);
    //    thread thWrite(&Pseudoterminal::write_port, Ps);
}

void open_dylib() {

}

void out_list_connect_device(Pseudoterminal &Ps) {
    if (!Ps.is_open()) {
        Error::char_arr_error("Func: out_list_connect_device.\nInfo: The port has not been created!");
        return;
    }
    if (Ps.get_count_connect() == 0) {
        Error::char_arr_error("Func: out_list_connect_device.\nInfo: Connect to at least one device to transfer data!");
        return;
    }
    cout << "\tList device\n";
    map listDevice = Ps.get_list_network();
    int counter = 0;
    for (auto device : listDevice) {
        cout << counter << "." << device.second.first << "\n";
        counter++;
    }
}

bool check_status(Pseudoterminal &Ps, string &str) {
    stringstream ss(str);
    status s;
    try {
        boost::archive::text_iarchive rd(ss);
        rd & s;
        if (s.flag == connect) {
            Ps.accept_connect(s.sender);
        } else if (s.flag == disconnect) {
            Ps.accept_disconnect(Ps.find_device(s.sender));
        } else if (s.flag == error) {

        }
    } catch (...) {
        return false;
    }

    return true;
}
