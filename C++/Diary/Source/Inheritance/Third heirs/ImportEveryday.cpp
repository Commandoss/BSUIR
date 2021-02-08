//
//  ImportEveryday.cpp
//  Diary
//
//  Created by Belousov Ilya on 11.12.20.
//

#include "ImportEveryday.hpp"


cImportEveryday::cImportEveryday() {
}

cImportEveryday::~cImportEveryday() {
    this->type.clear();
}

void cImportEveryday::changeType() {
    int menuInput = 0;
    cout << "\nWhat type do you want to ask?\n";
    cout << "1. Morning.\n" << "2. Daytime.\n";
//    cout << "3. Evening.\n" << "4. Don't ask importance.\n";
    cout << "3. Evening.\n";
    cout << "4. Exit.\n" << "Answer: ";
    menuInput = ExceptionInput::check_int(4, 1);
    
    switch (menuInput) {
        case Common:
            if (!this->type.empty()) this->type.clear();
            this->type = "Morning";
            break;
            
        case Important:
            if (!this->type.empty()) this->type.clear();
            this->type = "Daytime";
            break;
            
        case VeryImportant:
            if (!this->type.empty()) this->type.clear();
            this->type = "Evening";
            break;
            
//        case Nothing:
//            if (!this->type.empty()) this->type.clear();
//            break;
//
        default:
            if (!this->type.empty()) this->type.clear();
            this->type = "Morning";
            break;
    }
}

string cImportEveryday::getTypeEvent() {
    return this->type;
}

void cImportEveryday::menuObj() {
    int menuInput = 0;
    cout << "\nWhat would you like to change in this event?\n";
    cout << "1. Change all event.\n" << "2. Change only event.\n";
    cout << "3. Change only type.\n" << "4. Change only data.\n";
    cout << "5. Change only time.\n";
    cout << "6. Exit.\n" << "Answer: ";
    menuInput = ExceptionInput::check_int(6, 1);
    
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
            
        case ChangeTime:
            setTime();
            break;
            
        default:
            break;
    }
}

void cImportEveryday::printEvent() {
    cout << "Event: " << getEvent() << endl;
    if (!data.emptyData()) {
        cout << "Data: " << getData(2) << " "
        << data.getDayWeek() << " " << getData(3) << endl;
    }
    if (!data.emptyTime()) {
        cout << "Time: ";
        if (getTime(4) < 10) cout << "0";
            cout << getTime(4) << ":";
        if (getTime(5) < 10) cout << "0";
        cout << getTime(5) << endl;
    }
    if (!type.empty()) {
        cout << "Type: " << getTypeEvent() << endl;
    }
}

ostream& operator<<(ostream &os, cImportEveryday &cIE) {
    os << cIE.getEvent() << endl;
    os << cIE.getTypeEvent() << endl;
    os << cIE.getData(1) << " " << cIE.getData(2) << " " << cIE.getData(3) << endl;
    os << cIE.getTime(4) << " " << cIE.getTime(5) << endl;
    return os;
}

istream& operator>>(istream &is, cImportEveryday &cIE) {
    time_t day = -1, month = -1, hour = -1;
    string line;
    getline(is, cIE.info);
    getline(is, cIE.type);
    is >> day >> month;
    getline(is, line);
    cIE.data.setDay(day);
    cIE.data.setMonth(month);
    cIE.data.setYear(atoi(line.c_str()));
    is >> hour;
    line.clear();
    getline(is, line);
    cIE.data.setHour(hour);
    cIE.data.setMinutes(atoi(line.c_str()));
    
    return is;
}

