//
//  ImportPersonal.cpp
//  Diary
//
//  Created by Belousov Ilya on 11.12.20.
//

#include "ImportPersonal.hpp"


cImportPersonal::cImportPersonal() {
}

cImportPersonal::~cImportPersonal() {
    this->type.clear();
}

void cImportPersonal::changeType() {
    int menuInput = 0;
    cout << "\nWhat type do you want to ask?\n";
    cout << "1. Meetings.\n" << "2. Remarks.\n";
//    cout << "3. Purchases.\n" << "4. Don't ask importance.\n";
    cout << "3. Purchases.\n";
    cout << "4. Exit.\n" << "Answer: ";
    menuInput = ExceptionInput::check_int(5, 1);
    
    switch (menuInput) {
        case Common:
            if (!this->type.empty()) this->type.clear();
            this->type = "Meetings";
            break;
            
        case Important:
            if (!this->type.empty()) this->type.clear();
            this->type = "Remarks";
            break;
            
        case VeryImportant:
            if (!this->type.empty()) this->type.clear();
            this->type = "Purchases";
            break;
            
//        case Nothing:
//            if (!this->type.empty()) this->type.clear();
//            break;
//            
        default:
            if (!this->type.empty()) this->type.clear();
            this->type = "Meetings";
            break;
    }
}

string cImportPersonal::getTypeEvent() {
    return this->type;
}

void cImportPersonal::menuObj() {
    int menuInput = 0;
    cout << "\nWhat would you like to change in this event?\n";
    cout << "1. Change event.\n";
    cout << "2. Change only type.\n";
    cout << "3. Exit.\n" << "Answer: ";
    menuInput = ExceptionInput::check_int(3, 1);
    menuInput++;
    
    switch (menuInput) {
        case ChangeEvent:
            setEvent();
            changeType();
            break;
            
        case ChangeType:
            changeType();
            break;
            
        default:
            break;
    }
}

void cImportPersonal::printEvent() {
    cout << "Event: " << getEvent() << endl;
    if (!type.empty()) {
        cout << "Type: " << getTypeEvent() << endl;
    }
}

ostream& operator<<(ostream &os, cImportPersonal &cIP) {
    os << cIP.getEvent() << "\n";
    os << cIP.getTypeEvent() << "\n";
    return os;
}

istream& operator>>(istream &is, cImportPersonal &cIP) {
    getline(is, cIP.info);
    getline(is, cIP.type);
//    is >> cIP.type;
    return is;
}
