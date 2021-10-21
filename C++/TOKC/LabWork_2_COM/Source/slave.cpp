//
//  smain.cpp
//  LabWork_2
//
//  Created by Belousov Ilya on 9.10.21.
//

#include <iostream>
#include "SerialPorts.hpp"
#include <array>
#include <sstream>

using namespace::std;

int port_mode = 2;
string namePort;

void clear_term() {
    system("clear");
}

void confirmation() {
    cout << "\nconfirm to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.ios_base::clear();
    getchar();
    clear_term();
}

void out_menu(SerialPorts &S) {
    cout << "Port name: " << namePort;
    cout << "\n\t---Menu---\n";
    cout << "1. Send msg.\n";
    cout << "2. Send pack.\n";

    cout << "3. Accept msg.\n";
    cout << "4. Accept pack\n";

    cout << "5. Change speed.\n";
    cout << "6. Change mode.\n";

    cout << "7. Close port\n";
    cout << "8. Exit.\n";
    cout << "Answer: ";
}

void change_speed(SerialPorts &S) {
    std::string speed;
    cout << "Set speed: ";
    cin >> speed;

    S.change_speed(stoi(speed));

    confirmation();
}

void change_mode(SerialPorts &S) {
    cout << "\tPort mode\n";
    cout << "1. Read. " << "2. Write";
    cin >> port_mode;

    confirmation();
}

void send_pack(SerialPorts &S) {
    if (port_mode != 2) {
        cout << "Port mode: Read.\n";
        cout << "In this mode, you cannot send a pack.";
        confirmation();
        return;
    }

    char msg[MAX_SIZE_PACK_DATA];
    cout << "Set msg pack: ";
    cin >> msg;

    Package pack;
    pack.change_data(msg);
    pack.start();

    std::stringstream ss;
    boost::archive::text_oarchive wr(ss);
    wr & pack;
    cout << "\ndispatch...." << endl;
    S.write_port(ss.str());

    confirmation();
    return;
}

void send_msg(SerialPorts &S) {
    if (port_mode != 2) {
        cout << "Port mode: Read.\n";
        cout << "In this mode, you cannot send a message.";
        confirmation();
        return;
    }

    std::string msg;
    cout << "Set msg: ";
    cin >> msg;
    S.write_port(msg);

    confirmation();
}

void close_port(SerialPorts &S) {
    S.close_port();
    port_mode = 0;

    confirmation();
}

void accept_msg(SerialPorts &S) {
    if (port_mode != 1) {
        cout << "Port mode: Write.\n";
        cout << "It is impossible to receive a message in this mode.";
        confirmation();
        return;
    }

    size_t size;
    cout << "Set size: ";
    cin >> size;
    cout << "Waiting for a message....";

    string msg = S.read_port(size);
    clear_term();
    cout << "Msg: " << msg;

    confirmation();
}

void accept_pack(SerialPorts &S) {
    if (port_mode != 1) {
        cout << "Port mode: Write.\n";
        cout << "It is impossible to receive a pack in this mode.";
        confirmation();
        return;
    }

    Package pack;

    stringstream ss(S.read_port(MAX_SIZE_PACK));
    boost::archive::text_iarchive rd(ss);

    rd & pack;
    cout << pack;

    confirmation();
}

int main(int argc, const char * argv[]) {
    try {
        SerialPorts S;

        cout << "Set name port: ";
        cin >> namePort;

        S.open_port(namePort);

        array<function<void(SerialPorts &)>, 7> menu = {
            send_msg,
            send_pack,
            accept_msg,
            accept_pack,
            change_speed,
            change_mode,
            close_port,
        };

        unsigned int answer = 0;
        while(true) {
            out_menu(S);
            cin >> answer;
            answer--;

            if (answer > 6)
                break;
            clear_term();
            menu[answer](S);
        }

//        int s[] = {1, 0, 2, 12, 12, 12, 12, 123, 33}; // 9
//        char s[20] = "Hello world!";
//
//        IPv4 from(127, 0, 0, 1);
//        IPv4 whom(127, 0, 0, 1);
//
//        Package P(from, whom);
//        P.change_data(s);
//        P.start();
//
//        Client c(from);
//        c.start();
//        c.send_pack(P);
//
//        std::cout << c.get_pack();

    } catch (std::string const &msg) {
        std::cout << "\t-Error-\n" << std::endl;
        std::cout << msg << std::endl;
    }

    return 0;
}

