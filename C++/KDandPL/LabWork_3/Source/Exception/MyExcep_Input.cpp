//
//  MyExcep_Input.cpp
//  LabWork_6_Exception
//
//  Created by Belousov Ilya on 11/8/20.
//

#include "MyExcep_Input.hpp"

MyExcep_Input::MyExcep_Input() {
}

MyExcep_Input::MyExcep_Input(std::string message, int data) {
    this -> msg = message;
    this -> date = data;
}

MyExcep_Input::~MyExcep_Input() {
}

int MyExcep_Input::check_int(const int max, const int min) {
    int value;
    while (true) {
        try {
//            std::cin.exceptions(std::ios_base::badbit|std::ios_base::failbit);
            std::cin >> value;
            if (std::cin.fail()) throw MyException(1);
            if (value < min || value > max) throw MyException(2);
            
            break;
        }
        catch (MyException myEx) {
            std::cout << "Code exception: " << myEx.What();
            std::cout << "Input error please try again" << std::endl;
            std::cin.clear();
            rewind(stdin);
        }
//        catch (std::exception ex) {
//            std::cout << "Code exception: " << ex.what();
//            std::cout << "Input error please try again" << std::endl;
//            std::cin.clear();
//            rewind(stdin);
//        }
        catch (...) {
             MyException myEx;
            std::cout << "Code exception: " << myEx.What();
            std::cout << "Input error please try again" << std::endl;
            std::cin.clear();
            rewind(stdin);
        }
    }
    return value;
}

std::string MyExcep_Input::check_string(int length) {
    std::string line;
    while (true) {
        try {
            std::cin >> line;
            if (line[0] < 'A' || line[0] > 'Z') throw MyException(10);
            if (line.size() > length) throw MyException(6);
            if (line.empty()) throw MyException(7);
            for (int counter = 0; counter < line.size(); counter++) {
                if ((line[counter] < 'A' || line[counter] > 'Z') &&
                    (line[counter] < 'a' || line[counter] > 'z')) {
                    throw MyException(8);
                }
            }
            break;
        }
        catch (MyException myEx) {
            std::cout << "Code exception: " << myEx.What();
            std::cout << "Input error please try again" << std::endl;
            std::cin.clear();
            rewind(stdin);
        }
        catch (...) {
             MyException myEx;
            std::cout << "Code exception: " << myEx.What();
            std::cout << "Input error please try again" << std::endl;
            std::cin.clear();
            rewind(stdin);
        }
    }
    return line;
}

double MyExcep_Input::check_double(const int max, const int min) {
    double value;
    while (true) {
        try {
            std::cin >> value;
            if (std::cin.fail()) throw MyException(9);
            if (value < min || value > max) throw MyException(2);
            
            break;
        }
        catch (MyException myEx) {
            std::cout << "Code exception: " << myEx.What();
            std::cout << "Input error please try again" << std::endl;
            std::cin.clear();
            rewind(stdin);
        }
        catch (...) {
             MyException myEx;
            std::cout << "Code exception: " << myEx.What();
            std::cout << "Input error please try again" << std::endl;
            std::cin.clear();
            rewind(stdin);
        }
    }
    return value;
}

std::string MyExcep_Input::check_Adress(const int length) { //???/
    std::string line;
    rewind(stdin);
    while (true) {
        try {
            std::getline(std::cin, line);
            if ((line.find("St.") == std::string::npos) ||
                 (line.find("H.")  == std::string::npos) ||
                 (line.find("F.") == std::string::npos))
                throw MyException(15);
            if (line.size() > length) throw MyException(6);
            if (line.empty()) throw MyException(7);
            
            break;
        }
        catch (MyException myEx) {
            std::cout << "Code exception: " << myEx.What();
            std::cout << "The line should look like this: St. H. F.\n";
            std::cout << "Input error please try again" << std::endl;
            std::cin.clear();
            rewind(stdin);
        }
        catch (...) {
            MyException myEx;
            std::cout << "Code exception: " << myEx.What();
            std::cout << "Input error please try again" << std::endl;
            std::cin.clear();
            rewind(stdin);
        }
    }
    return line;
}

std::string MyExcep_Input::check_Pass() {
    std::string line;
    while (true) {
        try {
            std::cin >> line;
            if (line.empty()) throw MyException(7);
            if (line.size() < 9) throw MyException(6);
            for (int i = 0; i < line.size(); i++) {
                if (i < 2 && (line[i] < 'A' || line[i] > 'Z')) throw MyException(12);
                if (i > 2 && (line[i] < '0'|| line[i] > '9')) throw MyException(12);
            }
            break;
        }
        catch (MyException myEx) {
            std::cout << "Code exception: " << myEx.What();
            std::cout << "The line should look like this: XX0000000\n";
            std::cout << "Input error please try again" << std::endl;
            std::cin.clear();
            rewind(stdin);
        }
        catch (...) {
             MyException myEx;
            std::cout << "Code exception: " << myEx.What();
            std::cout << "The line should look like this: XX0000000\n";
            std::cout << "Input error please try again" << std::endl;
            std::cin.clear();
            rewind(stdin);
        }
    }
    return line;
}

std::string MyExcep_Input::check_Lic() {
    std::string line;
    while (true) {
        try {
            std::cin >> line;
            if (line.empty()) throw MyException(7);
            if (line.size() < 9) throw MyException(6);
            for (int i = 0; i < line.size(); i++) {
                if (i < 3 && (line[i] < 'A' || line[i] > 'Z')) throw MyException(13);
                if (i > 3 && (line[i] < '0'|| line[i] > '9')) throw MyException(13);
            }
            break;
        }
        catch (MyException myEx) {
            std::cout << "Code exception: " << myEx.What();
            std::cout << "The line should look like this: XXX000000\n";
            std::cout << "Input error please try again" << std::endl;
            std::cin.clear();
            rewind(stdin);
        }
        catch (...) {
             MyException myEx;
            std::cout << "Code exception: " << myEx.What();
            std::cout << "The line should look like this: XXX000000\n";
            std::cout << "Input error please try again" << std::endl;
            std::cin.clear();
            rewind(stdin);
        }
    }
    return line;
}

std::string MyExcep_Input::check_Target() {
    std::string line;
    while (true) {
        try {
            std::cin >> line;
            if (line.empty()) throw MyException(7);
            if (line.size() < 9) throw MyException(6);
            for (int i = 0; i < line.size(); i++) {
                if (i < 3 && (line[i] < 'A' || line[i] > 'Z')) throw MyException(14);
                if (i > 6 && (line[i] < 'A' || line[i] > 'Z')) throw MyException(14);
                if ((i > 3 && i < 6) && (line[i] < '0' || line[i] > '9')) throw MyException(14);
            }
            break;
        }
        catch (MyException myEx) {
            std::cout << "Code exception: " << myEx.What();
            std::cout << "The line should look like this: XXX0000XX\n";
            std::cout << "Input error please try again" << std::endl;
            std::cin.clear();
            rewind(stdin);
        }
        catch (...) {
             MyException myEx;
            std::cout << "Code exception: " << myEx.What();
            std::cout << "The line should look like this: XXX0000XX\n";
            std::cout << "Input error please try again" << std::endl;
            std::cin.clear();
            rewind(stdin);
        }
    }
    return line;
}

std::string MyExcep_Input::What() {
    return this -> msg;
}

int MyExcep_Input::gateDate() {
    return this -> date;
}
