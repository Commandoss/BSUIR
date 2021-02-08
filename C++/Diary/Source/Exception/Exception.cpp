//
//  Exception.cpp
//  Diary
//
//  Created by Belousov Ilya on 11.12.20.
//

#include "Exception.hpp"

MyException::MyException() {
    this -> date = 0;
    this -> msg = "Error, code unknown.";
}

MyException::~MyException() {
    msg.clear();
}

MyException::MyException(int date) {
    switch (date) {
        case 1:
            this -> msg = "Not a number entered.\n";
            break;
            
        case 2:
            this -> msg = "The day is not set correctly.\n";
            break;
            
        case 3:
            this -> msg = "The month is not set correctly.\n";
            break;
            
        case 4:
            this -> msg = "The year is not set correctly.\n";
            break;
            
        case 5:
            this -> msg = "Invalid characters entered.\n";
            break;
            
        case 6:
            this -> msg = "The word must start with a capital letter.\n";
            break;
            
        case 7:
            this -> msg = "The entered data does not correspond to the range.\n";
            break;
            
        case 8:
            this -> msg = "Time is set incorrectly.\n";
            break;
            
        case 9:
            this -> msg = "Cannot set empty string.\n";
            break;
            
        case 10:
            this -> msg = "Date setting error, February 28 days this year.\n";
            break;
            
        default:
            this -> msg = "Error, code unknown.\n";
            break;
    }
}

string MyException::What() {
    return this -> msg;
}

int MyException::gateDate() {
    return this -> date;
}
