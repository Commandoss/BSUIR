//
//  ImportWork.cpp
//  Diary
//
//  Created by Belousov Ilya on 11.12.20.
//

#include "ImportWork.hpp"

cImportWork::cImportWork() {
}

cImportWork::cImportWork(cImportWork &cop) {
    info = cop.info;
    data = cop.data;
    type = cop.type;
}


cImportWork::~cImportWork() {
    this->type.clear();
}

void cImportWork::changeType() {
    int menuInput = 0;
    cout << "\nWhat type do you want to ask?\n";
    cout << "1. Common.\n" << "2. Important.\n";
//    cout << "3. Very important.\n" << "4. Don't ask importance.\n";
    cout << "3. Very important.\n";
    cout << "4. Exit.\n" << "Answer: ";
    menuInput = ExceptionInput::check_int(4, 1);
    
    switch (menuInput) {
        case Common:
            if (!this->type.empty()) this->type.clear();
            this->type = "Common";
            break;
            
        case Important:
            if (!this->type.empty()) this->type.clear();
            this->type = "Important";
            break;
            
        case VeryImportant:
            if (!this->type.empty()) this->type.clear();
            this->type = "Very Important";
            break;
            
//        case Nothing:
//            if (!this->type.empty()) this->type.clear();
//            break;
            
        default:
            if (!this->type.empty()) this->type.clear();
            this->type = "Common";
            break;
    }
}

string cImportWork::getTypeEvent() {
    return this->type;
}

void cImportWork::menuObj() {
    int menuInput = 0;
    cout << "\nWhat would you like to change in this event?\n";
    cout << "1. Change all event.\n" << "2. Change only event.\n";
    cout << "3. Change only type.\n" << "4. Change only data.\n";
    cout << "5. Exit.\n" << "Answer: ";
    menuInput = ExceptionInput::check_int(5, 1);
    
    switch (menuInput) {
        case ChangeAllEvent:
            setEvent();
            changeType();
            break;
            
        case ChangeEvent:
            changeEvent();
            break;
            
        case ChangeType:
            changeType();
            break;
            
        case ChangeData:
            setData();
            break;
            
        default:
            break;
    }
}

void cImportWork::printEvent() {
    cout << "Event: " << getEvent() << endl;
    if (!data.emptyData()) {
        cout << "Data: " << getData(2) << " "
        << data.getDayWeek() << " " << getData(3) << endl;
    }
    if (!type.empty()) {
        cout << "Type: " << getTypeEvent() << endl;
    }
}

ostream& operator<<(ostream &os, cImportWork &cIW) {
    os << cIW.getEvent() << endl;
    if (!cIW.data.emptyData()) {
        os << cIW.getData(1) << " "
        << cIW.getData(2) << " " << cIW.getData(3) << "\n";
    }
    if (!cIW.type.empty()) {
        os << cIW.getTypeEvent() << endl;
    }
    return os;
}

istream& operator>>(istream &in, cImportWork &cIW) {
    time_t day = -1, month = -1;
    string line;
    getline(in, cIW.info);
    in >> day >> month;
    getline(in, line);
    cIW.data.setDay(day);
    cIW.data.setMonth(month);
    cIW.data.setYear(atoi(line.c_str()));
    getline(in, cIW.type);
    return in;
}
