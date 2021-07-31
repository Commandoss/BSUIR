//
//  HumanClass.cpp
//  Lab5
//
//  Created by Belousov Ilya on 10/9/20.
//

#include "HumanClass.hpp"

HumanClass::HumanClass() {
}

HumanClass::HumanClass(string name, string lastname, vector<int>birth) {
    this->Name = name;
    this->LastName = lastname;
    this->DayBirth = birth;
}

HumanClass::~HumanClass() {
    Name.clear();
    LastName.clear();
    DayBirth.clear();
}

string HumanClass::getName() {
    return Name;
}

string HumanClass::getLastName() {
    return LastName;
}

vector<int> HumanClass::getVDayBirth() {
    return DayBirth;
}

int HumanClass::getBirthDay() {
    return DayBirth[Day];
}

int HumanClass::getBirthMonth() {
    return DayBirth[Month];
}

int HumanClass::getBirthYear() {
    return DayBirth[Year];
}

void HumanClass::setNewName(string name) {
    Name.clear();
    Name = name;
}

void HumanClass::setNewLastName(string lastname) {
    LastName.clear();
    LastName = lastname;
}

void HumanClass::setElemDayBirth(int cellNum, int num) {
    DayBirth[cellNum] = num;
}

void HumanClass::setDayBitrh(vector<int> birth) {
    DayBirth.clear();
    DayBirth = birth;
}

void HumanClass::setToEndVDayBirth(int num) {
    DayBirth.push_back(num);
}

istream& operator>>(istream &in, HumanClass &cH) {
    cout << "Set Name (ex. Ivan): ";
    cH.Name = MyExcep_Input::check_string(15);
    cout << "Set Last Name (ex. Ivanov): ";
    cH.LastName = MyExcep_Input::check_string(20);
    cout << "Set Date of Birth\n";
    cH.SetData(cH.DayBirth);
    return in;
}

ostream& operator<<(ostream &os, HumanClass &cH) {
//    cH.Table();
    os << "|" << setw(15) << cH.getName() << "|";
    os << setw(20) << cH.getLastName() << "|";
    os << setw(5) << cH.getBirthDay() << ".";
    if (cH.getBirthMonth() < 10) {
        cout << "0";
    }
    os << cH.getBirthMonth() << "." << cH.getBirthYear() << "|\n";
    cout << "|--------------------------------------------------|\n";
    return os;
}

void HumanClass::SetData(vector<int> &data) {
    data.resize(3);
    cout << "Set day: ";
    data[0] = MyExcep_Input::check_int(31, 1);
    cout << "Set month: ";
    data[1] = MyExcep_Input::check_int(12, 1);
    cout << "Set year: ";
    data[2] = MyExcep_Input::check_int(2099, 1970);
}

void HumanClass::Table() {
    cout << "\n|--------------------------------------------------|\n";
    cout << "|" << setw(26) << "Humans" << setw(26) << "|\n";
    cout << "|--------------------------------------------------|\n";
    cout << "|" << setw(15) << "Name" << "|" << setw(20) << "Last Name" << "|" << setw(13) << "Bithday"
    << "|\n";
    cout << "|--------------------------------------------------|\n";
}


//
//bool operator==(const HumanClass &cH1, const HumanClass &cH2) {
//    if (cH1.Name != cH2.Name) {
//        cout << "The names don't match.\n";
//        return false;
//    }
//    if (cH1.LastName != cH2.LastName) {
//        cout << "The last names do not match.\n";
//        return false;
//    }
//    if ((cH1.DayBirth[Day] != cH2.DayBirth[Day]) ||
//        (cH1.DayBirth[Month] != cH2.DayBirth[Month]) ||
//        (cH1.DayBirth[Year] != cH2.DayBirth[Year])) {
//        cout << "Birth dates don't match.\n";
//        return false;
//    }
//    return true;
//}

void HumanClass::menuObj() {
    int menuInput = 0;
    while (menuInput < 8) {
        
        cout << "\nWhat do you want to do in this Human object?\n";
        cout << "1. Change Name.\n" << "2. Change Last Name.\n";
        cout << "3. Change date of birth.\n" << "4. Print Obj.\n";
        cout << "5. Exit.\n" << "Answer: ";
        menuInput = MyExcep_Input::check_int(5, 1);
        string Line;
        vector<int> newData(3);
        
        switch (menuInput) {
            case 1:
                this->Name.clear();
                cout << "Enter a new name: ";
                Line = MyExcep_Input::check_string(15);
                setNewName(Line);
                break;
                
            case 2:
                this->LastName.clear();
                cout << "Enter a new last name: ";
                Line = MyExcep_Input::check_string(15);
                setNewLastName(Line);
                break;
                
            case 3:
                this->DayBirth.clear();
                cout << "Enter new date of birth\n";
                SetData(newData);
                setDayBitrh(newData);
                break;
                
            case 4:
                cout << *this; //??
                break;
                
            default:
                cout << "Close menu." << endl;
                break;
        }
    }
}
