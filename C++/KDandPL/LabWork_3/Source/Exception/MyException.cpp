//
//  Exeption.cpp
//  LabWork_5_Human
//
//  Created by Belousov Ilya on 10/21/20.
//

#include "MyException.hpp"

MyException::MyException() {
    this -> date = 0;
    this -> msg = "Error, code unknown.";
}

MyException::MyException(int date) {
    switch (date) {
        case 1:
            this -> msg = "Not a number entered.\n";
            break;
            
        case 2:
            this -> msg = "The entered number exceeds the range.\n";
            break;
            
        case 3:
            this -> msg = "The entered number does not match the date.\n";
            break;
            
        case 4:
            this -> msg = "The entered date does not match the month.\n";
            break;
            
        case 5:
            this -> msg = "The entered date does not match the year.\n";
            break;
            
        case 6:
            this -> msg = "The entered string exceeds the length.\n";
            break;
            
        case 7:
            this -> msg = "Error! Empty string entered.\n";
            break;
            
        case 8:
            this -> msg = "Invalid characters entered.\n";
            break;
            
        case 9:
            this -> msg = "The entered number does not match the double type.\n";
            break;
            
        case 10:
            this -> msg = "The word must start with a capital letter.\n";
            break;
            
        case 11:
            this -> msg = "House number is incorrect.\n"; //???
            break;
            
        case 12:
            this -> msg = "Passport data is set incorrectly.\n";
            break;
            
        case 13:
            this -> msg = "Licence data is set incorrectly.\n";
            break;
            
        case 14:
            this -> msg = "Target visit data is set incorrectly.\n";
            break;
            
        case 15:
            this -> msg = "Adress data is set incorrectly.\n";
            break;
            
        default:
            this -> msg = "Error, code unknown.\n";
            break;
    }
}

std::string MyException::What() {
    return this -> msg;
}

int MyException::gateDate() {
    return this -> date;
}
