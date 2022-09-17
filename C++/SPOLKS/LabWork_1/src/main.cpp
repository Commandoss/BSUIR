//
//  main.cpp
//  TCP
//
//  Created by Belousov Ilya on 16.09.22.
//

//#include "ipv4.hpp"
//
//int main()
//{
//    IPv4 address(168, 192, 0, 1);
//    std::cout << "Addres: " << address << std::endl;
//
//    IPv4 ip;
//    std::cout << ip << std::endl;
//    std::cin >> ip;
//
//    if(!std::cin.fail())
//    {
//        std::cout << ip << std::endl;
//    }
//}

#include "serialization.hpp"

int main()
{
    Serialization s;
    int num = 259;
    s << num;
//    Ex ex;
//
//    std::stringstream ss;
//    s << ex;
    return 0;
}
