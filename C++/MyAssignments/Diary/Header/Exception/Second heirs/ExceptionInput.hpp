//
//  ExceptionInput.hpp
//  Diary
//
//  Created by Belousov Ilya on 11.12.20.
//

#ifndef ExceptionInput_hpp
#define ExceptionInput_hpp

#include "Exception.hpp"

class ExceptionInput: public MyException {
public:
    ExceptionInput();
    ExceptionInput(int date);
    ~ExceptionInput();
    
    static time_t check_day();
    static time_t check_month();
    template <typename Type>
    static Type check_year(Type &day, Type &month);
    
    static int check_time(const int type);
    static int check_int(const int max, const int min);
    static string check_string(int length);
    static string check_nameFile();
    
    string What() override;
    int gateDate() override;
};

template <typename Type>
Type ExceptionInput::check_year(Type &day, Type &month) {
    int value;
    while (true) {
        try {
            cin >> value;
            if (std::cin.fail()) throw MyException(1);
            
            int leapYear = value % 4;
            
            if (month == 2 && day > 29 - leapYear) throw MyException(10);
            
            if ( day > 30 + month % 2 ) throw MyException(2);
        
            if (value < 1960 || value > 2099) throw MyException(4);

            break;
        }
        catch (MyException myEx) {
            cout << "Code exception: " << myEx.What();
            cout << "Input error please try again" << endl;
            cin.clear();
            rewind(stdin);
            cout << "Set day: ";
            day = ExceptionInput::check_day();
            cout << "Set mont: ";
            month = ExceptionInput::check_month();
        }
        catch (...) {
             MyException myEx;
            cout << "Code exception: " << myEx.What();
            cout << "Input error please try again" << endl;
            cin.clear();
            rewind(stdin);
            cout << "Set day: ";
            day = ExceptionInput::check_day();
            cout << "Set mont: ";
            month = ExceptionInput::check_month();
        }
    }
    return value;
}

#endif /* ExceptionInput_hpp */
