//
//  cmain.cpp
//  LabWork_2
//
//  Created by Belousov Ilya on 11.10.21.
//
//
#include <iostream>
#include "Client.hpp"
#include "Ipv4.hpp"

#include "Package.hpp"
using namespace::std;
int main(int argc, const char * argv[]) {
    try {
//        int s[] = {1, 0, 2, 12, 12, 12, 12, 123, 33}; // 9
        char s[20] = "Hello world!";

        IPv4 from(172, 20, 10, 7);
        IPv4 whom(127, 0, 0, 1);

        Package P(from, whom);
        P.change_data(s);
        P.start();

        Client c(from);
        c.start();
        c.send_pack(P);

        std::cout << c.get_pack();

    } catch (std::string const &msg) {
        std::cout << "\t-Error-\n" << std::endl;
        std::cout << msg << std::endl;
    }
    
    return 0;
}

