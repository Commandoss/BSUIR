//
//  ExceptionInput.cpp
//  Diary
//
//  Created by Belousov Ilya on 11.12.20.
//

#include "ExceptionInput.hpp"

ExceptionInput::ExceptionInput() {
}

ExceptionInput::ExceptionInput(int date) {
    this -> date = date;
}

ExceptionInput::~ExceptionInput() {
}

time_t ExceptionInput::check_day() {
    int value;
    while (true) {
        try {
            cin >> value;
            if (std::cin.fail()) throw MyException(1);
            if (value < 1 || value > 31) throw MyException(2);
            break;
        }
        catch (MyException myEx) {
            cout << "Code exception: " << myEx.What();
            cout << "Input error please try again" << endl;
            cin.clear();
            rewind(stdin);
        }
        catch (...) {
            MyException myEx;
            cout << "Code exception: " << myEx.What();
            cout << "Input error please try again" << endl;
            cin.clear();
            rewind(stdin);
        }
    }
    return value;
}


time_t ExceptionInput::check_month() {
    int value;
    while (true) {
        try {
            cin >> value;
            if (std::cin.fail()) throw MyException(1);
            if (value < 1 || value > 12) throw MyException(3);
            break;
        }
        catch (MyException myEx) {
            cout << "Code exception: " << myEx.What();
            cout << "Input error please try again" << endl;
            cin.clear();
            rewind(stdin);
        }
        catch (...) {
             MyException myEx;
            cout << "Code exception: " << myEx.What();
            cout << "Input error please try again" << endl;
            cin.clear();
            rewind(stdin);
        }
    }
    return value;
}

int ExceptionInput::check_time(const int type) {
    int value;
    while (true) {
        try {
            cin >> value;
            if (std::cin.fail()) throw MyException(1);
            
            switch (type) {
                case 1:
                    if (value < 0 || value > 23) throw MyException(8);
                    break;
                    
                case 2:
                    if (value < 0 || value > 59) throw MyException(8);
                    break;
                    
                default:
                    break;
            }
            break;
        }
        catch (MyException myEx) {
            cout << "Code exception: " << myEx.What();
            cout << "Input error please try again" << endl;
            cin.clear();
            rewind(stdin);
        }
        catch (...) {
             MyException myEx;
            cout << "Code exception: " << myEx.What();
            cout << "Input error please try again" << endl;
            cin.clear();
            rewind(stdin);
        }
    }
    return value;
}

string ExceptionInput::check_string(int length) {
    string line;
    while (true) {
        try {
            rewind(stdin);
            getline(cin, line);
            if (line.size() > length) throw MyException(3);
            if (line.empty()) throw MyException(9);
            break;
        }
        catch (MyException myEx) {
            cout << "Code exception: " << myEx.What();
            cout << "Input error please try again" << endl;
            cin.clear();
            rewind(stdin);
        }
        catch (...) {
             MyException myEx;
            cout << "Code exception: " << myEx.What();
            cout << "Input error please try again" << endl;
            cin.clear();
            rewind(stdin);
        }
    }
    return line;
}

int ExceptionInput::check_int(const int max, const int min) {
    int value;
    while (true) {
        try {
            cin >> value;
            if (cin.fail()) throw MyException(1);
            if (value < min || value > max) throw MyException(7);
            
            break;
        }
        catch (MyException myEx) {
            cout << "Code exception: " << myEx.What();
            cout << "Input error please try again" << endl;
            cin.clear();
            rewind(stdin);
        }
        catch (...) {
             MyException myEx;
            cout << "Code exception: " << myEx.What();
            cout << "Input error please try again" << endl;
            cin.clear();
            rewind(stdin);
        }
    }
    return value;
}

string ExceptionInput::check_nameFile() {
    std::string line;
    while (true) {
        try {
            std::cin >> line;
            if (line.size() > FILENAME_LEN) throw MyException(6);
            if (line.empty()) throw MyException(7);
            for (int counter = 0; counter < line.size() - 4; counter++) {
                if ((line[counter] < 'A' || line[counter] > 'Z') &&
                    (line[counter] < 'a' || line[counter] > 'z')) {
                    throw MyException(8);
                }
            }
            if (line.find(".txt") == std::string::npos) throw MyException(17);
            
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

string ExceptionInput::What() {
    return this -> msg;
}

int ExceptionInput::gateDate() {
    return this -> date;
}
