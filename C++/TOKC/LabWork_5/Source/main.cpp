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
#include "Package.hpp"
#include "Cropping.hpp"
#include "Menu.hpp"

using namespace::std;

int main(int argc, const char * argv[]) {
//    map<int, function<void(Pseudoterminal &Ps)>> menu {
//        {1, send_msg},
//        {2, send_pack},
//        {3, send_frame},
//
//        {4, accept_msg},
//        {5, accept_pack},
//        {6, accept_frame},
//
//        {7, open_port},
//        {8, change_speed_in},
//        {9, change_speed_out},
//        {10, close_port},
//
//        {11, connect_port},
//        {12, disconnect_port},
//        {13, out_list_connect_device}
//    };
//
//    unsigned int answer = 0;
//    while (true) {
//        interface(Ps);
//
//        cin >> answer;
//        clear_terminal();
//
//        if (answer == menu.size() + 1)
//            break;
//
//        try {
//            menu.find(answer)->second(Ps);
//            confirmation();
//        } catch (...) {
//            Error::char_arr_error("Func: main().\nInfo: Incorrect input!");
//
//            if (cin.ios_base::fail())
//                clear_buffer();
//
//            confirmation();
//        }
//    }

    return 0;
}
