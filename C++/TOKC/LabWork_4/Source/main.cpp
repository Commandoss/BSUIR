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
    string msg;
    cout << "Input msg: ";
    getline(cin, msg);

    map listDevice = ;
    for (auto device : ) {

    }

    Ps.write_port(msg, );

}

void send_pack(Pseudoterminal &Ps) {

}

void send_frame(Pseudoterminal &Ps) {

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
