//
//  main.cpp
//  LabWork_4
//
//  Created by Belousov Ilya on 28.10.21.
//

#include <iostream>
#include <map>
#include <thread>

#include "Pseudoterminal.hpp"

using namespace::std;

void confirmation();
void interface(Pseudoterminal &Ps);
void clear_terminal();

void send_msg(Pseudoterminal &Ps);
void send_pack(Pseudoterminal &Ps);
void send_frame(Pseudoterminal &Ps);

void accept_msg(Pseudoterminal &Ps);
void accept_pack(Pseudoterminal &Ps);
void accept_frame(Pseudoterminal &Ps);

void open_port(Pseudoterminal &Ps);
void change_speed_in(Pseudoterminal &Ps);
void change_speed_out(Pseudoterminal &Ps);
void close_port(Pseudoterminal &Ps);

void connect_port(Pseudoterminal &Ps);
void disconnect_port(Pseudoterminal &Ps);

void start_thread(Pseudoterminal &Ps);

int main(int argc, const char * argv[]) {
    Pseudoterminal Ps;
    map<int, function<void(Pseudoterminal &Ps)>> menu {
        {1, send_msg},
        {2, send_pack},
        {3, send_frame},

        {4, accept_msg},
        {5, accept_pack},
        {6, accept_frame},

        {7, open_port},
        {8, change_speed_in},
        {9, change_speed_out},
        {10, close_port},

        {11, connect_port},
        {12, disconnect_port},
    };

    unsigned int answer = 0;
    while (true) {
        interface(Ps);
        cin >> answer;
        if (answer > menu.size())
            break;
        clear_terminal();
        menu[answer](Ps);
    }

    return 0;
}

void clear_terminal() {
    system("clear");
}

void confirmation() {
    cout << "\nconfirm to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.ios_base::clear();
    getchar();
    clear_terminal();
}

void interface(Pseudoterminal &Ps) {
    cout << "Port name: " << Ps.get_port_name();
    cout << "\n\t---Menu---\n";
    cout << "\n";
    cout << "1. Send msg.\n";
    cout << "2. Send pack.\n";
    cout << "3. Send frame.\n";
    cout << "\n";
    cout << "4. Accept msg.\n";
    cout << "5. Accept pack\n";
    cout << "6. Accept frame.\n";
    cout << "\n";
    cout << "7. Open port.\n";
    cout << "8. Change speed in port.\n";
    cout << "9. Change speed in out.\n";
    cout << "10. Close port\n";
    cout << "\n";
    cout << "11. Connect port\n";
    cout << "12. Disconnect port\n";
    cout << "\n";
    cout << "13. Exit.\n";
    cout << "Answer: ";
}

//void create_pack(Pseudoterminal &Ps) {
//    Package P;
//    P.set_sender(Ps.get_port_name());
//
//    char recipiend[PACK_ADRESS_SIZE];
//    cout << "Input recipiend: ";
//    cin >> recipiend;
//    P.set_recipiend(recipiend);
//
//    char data[MAX_SIZE_PACK_DATA];
//    cout << "Input data: ";
//    cin >> data;
//    P.change_data(data);
//
//    P.start();
//}
//
//void create_frame(Pseudoterminal &Ps) {
//    Package P;
//    P.set_sender(Ps.get_port_name());
//
//    char recipiend[PACK_ADRESS_SIZE];
//    cout << "Input recipiend: ";
//    cin >> recipiend;
//    P.set_recipiend(recipiend);
//
//    char data[MAX_SIZE_PACK_DATA];
//    cout << "Input data: ";
//    cin >> data;
//    P.change_data(data);
//
//    P.start();
//}

void send_msg(Pseudoterminal &Ps) {
    if (!Ps.is_open()) {
        Error::char_arr_error("Func: send_msg.\nInfo: The port has not been created!");
        confirmation();
        return;
    }
    if (Ps.get_count_connect() == 0) {
        Error::char_arr_error("Func: send_msg.\nInfo: Connect to at least one device to transfer data!");
        confirmation();
        return;
    }

    string msg;
    cout << "Input msg: ";
    getline(cin, msg);

    cout << "Select Device:\n";
    map listDevice = Ps.get_list_network();
    for (auto device : listDevice) {
        cout << device.first << "\n";
    }

    unsigned int device;
    cout << "Answer: ";
    cin >> device;
    Ps.write_port(msg, device);

}

void send_pack(Pseudoterminal &Ps) {
    if (!Ps.is_open()) {
        Error::char_arr_error("Func: send_pack.\nInfo: The port has not been created!");
        confirmation();
        return;
    }
    if (Ps.get_count_connect() == 0) {
        Error::char_arr_error("Func: send_pack.\nInfo: Connect to at least one device to transfer data!");
        confirmation();
        return;
    }

    char data[MAX_SIZE_PACK_DATA];
    cout << "Input data: ";
    fgets(data, MAX_SIZE_PACK_DATA, stdout);

    cout << "Select Device:\n";
    map listDevice = Ps.get_list_network();
    for (auto device : listDevice) {
        cout << device.first << "\n";
    }

    unsigned int device;
    cout << "Answer: ";
    cin >> device;

    Package P;
    P.change_data(data);
    P.set_sender(Ps.get_port_name());
    P.set_recipiend(listDevice[device].first);
    P.start();

    stringstream ss;
    boost::archive::text_iarchive wr(ss);
    wr & P;
    Ps.write_port(ss.str(), device);
}

void send_frame(Pseudoterminal &Ps) {
//    if (!Ps.is_open()) {
//        Error::char_arr_error("Func: send_frame.\nInfo: The port has not been created!");
//        return;
//    }
//    if (Ps.get_count_connect() == 0) {
//        Error::char_arr_error("Func: send_frame.\nInfo: Connect to at least one device to transfer data!");
//        return;
//    }
}

void accept_msg(Pseudoterminal &Ps) {

}

void accept_pack(Pseudoterminal &Ps) {

}

void accept_frame(Pseudoterminal &Ps) {

}

void open_port(Pseudoterminal &Ps) {
    if (!Ps.create_port())
        return;

    cout << "The port was created: " << Ps.get_port_name() << endl;
    confirmation();
}

void change_speed_in(Pseudoterminal &Ps) {
    speed_t speed;
    cout << "Set speed in: ";
    cin >> speed;
    Ps.change_speed_in(speed);
    confirmation();
}

void change_speed_out(Pseudoterminal &Ps) {
    speed_t speed;
    cout << "Set speed out: ";
    cin >> speed;
    Ps.change_speed_out(speed);
    confirmation();
}

void close_port(Pseudoterminal &Ps) {
    if (!Ps.is_open()) {
        Error::char_arr_error("Func: Main::close_port.\nInfo: The port is already closed!\n");
        confirmation();
        return;
    }

    Ps.close_port();
    cout << "Port closed successfully" << endl;
    confirmation();
}

void connect_port(Pseudoterminal &Ps) {

}

void disconnect_port(Pseudoterminal &Ps) {

}

void start_thread(Pseudoterminal &Ps) {
//    thread thRead(&Pseudoterminal::read_port, Ps, MAX_SIZE_PACK_DATA);
//    thread thWrite(&Pseudoterminal::write_port, Ps);
}
