//
//  main.cpp
//  LabWork_4
//
//  Created by Belousov Ilya on 28.10.21.
//

#include <iostream>
#include <map>

#include "Pseudoterminal.hpp"

using namespace::std;

void confirmation();
void interface(Pseudoterminal &Ps);
void clear_terminal();

void create_pack(Pseudoterminal &Ps);
void create_frame(Pseudoterminal &Ps);

int main(int argc, const char * argv[]) {
    Pseudoterminal Ps;
    map<int, function<void(Pseudoterminal &Ps)>> menu {
        {1, interface},
    };

    unsigned int answer = 0;
    while (true) {
        interface(Ps);
        cin >> answer;
        menu[answer](Ps);
    }

    return 0;
}

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

void interface(Pseudoterminal &Ps) {
    cout << "Port name: " << Ps.get_port_name();
    cout << "\n\t---Menu---\n";
    cout << "1. Send msg.\n";
    cout << "2. Send pack.\n";

    cout << "3. Accept msg.\n";
    cout << "4. Accept pack\n";

    cout << "5. Change speed.\n";
    cout << "6. Create pack.\n";
//    cout << "6. Change mode.\n";
//    open_port

    cout << "7. Close port\n";
    cout << "8. Exit.\n";
    cout << "Answer: ";
}

void create_pack(Pseudoterminal &Ps) {
    Package P;
    P.set_sender(Ps.get_port_name());

    char recipiend[PACK_ADRESS_SIZE];
    cout << "Input recipiend: ";
    cin >> recipiend;
    P.set_recipiend(recipiend);

    char data[MAX_SIZE_PACK_DATA];
    cout << "Input data: ";
    cin >> data;
    P.change_data(data);

    P.start();
}

void create_frame(Pseudoterminal &Ps) {
    Package P;
    P.set_sender(Ps.get_port_name());

    char recipiend[PACK_ADRESS_SIZE];
    cout << "Input recipiend: ";
    cin >> recipiend;
    P.set_recipiend(recipiend);

    char data[MAX_SIZE_PACK_DATA];
    cout << "Input data: ";
    cin >> data;
    P.change_data(data);

    P.start();
}
