//
//  smain.cpp
//  LabWork_2
//
//  Created by Belousov Ilya on 9.10.21.
//

#include <iostream>
#include "Server.hpp"
//
int main(int argc, const char * argv[]) {
    try {
        Server s;
        s.start();
        Package cP = s.get_bath();
        std::cout << cP;

        char jk[20];
        memcpy(&jk, cP.get_data(), sizeof(jk) * sizeof(*jk));

        IPv4 from(127, 0, 0, 1);
        IPv4 whom(127, 0, 0, 1);

        int mas[] = {1, 2, 3, 4, 5};
        Package P(from, whom);
        P.change_data(mas);
        P.start();

        s.send_bath(P);
        
    } catch (std::string const &msg) {
        std::cout << "\t-Error-\n" << std::endl;
        std::cout << msg << std::endl;
    }
    return 0;
}
