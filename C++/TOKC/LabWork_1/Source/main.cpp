//
//  main.cpp
//  LabWork_1
//
//  Created by Belousov Ilya on 15.09.21.
//

#include <iostream>
#include "Pseudoports.hpp"
#include "SerialPorts.hpp"

using namespace::std;

int main(int argc, const char * argv[]) {
    string port;
    string str = "std::string SerialPorts::read_port(const size_t size) {";
    string str2 = "std::string SerialPorts::read ort(const size_t size) {";
    try {
        Pseudoports Ps;
        Ps.create_port();
        port = Ps.get_port_name();

        SerialPorts Sp(port);

        cout << port << endl;
        cout << Sp.write_port(str) << endl;
        cout << Ps.read_port(str.size()) << endl;

        cout << Ps.write_port(str2) << endl;
        cout << Sp.read_port(str2.size()) << endl;

    } catch (const std::string msgerr) {
        cout << "Error: " << msgerr << endl;
    }
    return 0;
}

