//
//  TouristClass.cpp
//  Lab5
//
//  Created by Belousov Ilya on 10/9/20.
//

#include "TouristClass.hpp"

TourisClass::TourisClass() {
}

TourisClass::TourisClass(string PassID, string country, string Target, vector<int> data) {
    History newHis;
    PassportID = PassID;
    newHis.Country = country;
    newHis.TargetVis = Target;
    newHis.DayVis = data;
}

TourisClass::~TourisClass() {
    PassportID.clear();
    VStrct.clear();
}

string TourisClass::getPassportID() {
    return PassportID;
}

string TourisClass::GetCountry(const int cellNum) {
    string str = VStrct[cellNum].Country;
    return str;
}

string TourisClass::getTargetVis(const int cellNum) {
    string str = VStrct[cellNum].TargetVis;
    return str;
}

vector<int> TourisClass::getVDayVisit(const int cellNum) {
    return VStrct[cellNum].DayVis;
}

vector<struct History> TourisClass::getVstr() {
    return VStrct;
}

int TourisClass::getElemVDayVisit(const int cellNum_1, const int cellNum_2) {
    return VStrct[cellNum_1].DayVis[cellNum_2];
}

struct History TourisClass::getHisElem(const int cellNum) {
    return VStrct[cellNum];
}

void TourisClass::setPassportID(string PassID) {
    PassportID.clear();
    PassportID = PassID;
}

void TourisClass::setElemVDayVisit(struct History H) {
    VStrct.push_back(H);
}

void TourisClass::setVStrct(vector<struct History> &VecHis , int counter) {
    VecHis.clear();
    VecHis.resize(counter);
    for (int cell = 0; cell < counter; cell++) {
        History newHis;
        cout << "Set country (ex. Belarus): ";
        newHis.Country = MyExcep_Input::check_string(15);
        cout << "Set Target visit (ex. TAG1234UI): ";
        newHis.TargetVis = MyExcep_Input::check_Target();
        cout << "Set Day Visit\n";
        SetData(newHis.DayVis);
        VecHis[cell] = newHis;
    }
}

void TourisClass::setVStrct(vector<struct History> VecHis) {
    VStrct.clear();
    VStrct = VecHis;
}

void TourisClass::setCountry(int cellNum, string str) {
    VStrct[cellNum].Country.clear();
    VStrct[cellNum].Country = str;
}

void TourisClass::setTargetVis(int cellNum, string str) {
    VStrct[cellNum].TargetVis.clear();
    VStrct[cellNum].TargetVis = str;
}

void TourisClass::setToEndVDayVisit(int cellNum, int value) {
    VStrct[cellNum].DayVis.push_back(value);
}


ostream& operator<<(ostream &os, TourisClass &cT) {
//    cT.Table();
    os << "|" << setw(15) << cT.getName() << "|";
    os << setw(20) << cT.getLastName() << "|";
    os << setw(5) << cT.getBirthDay() << ".";
    if (cT.getBirthMonth() < 10) {
        cout << "0";
    }
    os << cT.getBirthMonth() << "." << cT.getBirthYear() << "|";
    os << setw(14) << cT.getPassportID() << "|";
    
    for(int cell = 0; cell < cT.VStrct.size(); cell++) {
        if (cT.VStrct.size() > 1 && cell == 1) {
            cout << "|----------------------------------------------------"
            << "-------------|";
        }
        if (cell > 1) {
            cout << "|" << setw(66) << "|";
        }
        os << setw(14) << cT.GetCountry(cell) << "|";
        os << setw(14) << cT.getTargetVis(cell) << "|";
        os << setw(5);
        os << cT.getElemVDayVisit(cell, Day) << ".";
        if (cT.getElemVDayVisit(cell, Month) < 10) {
            cout << "0";
        }
        os << cT.getElemVDayVisit(cell, Month) << "." << cT.getElemVDayVisit(cell, Year) << "|\n" ;
    }
    cout << "|-----------------------------------------------------------------------------"
    << "--------------------------------|\n";
    return os;
}

istream& operator>>(istream &in, TourisClass &cT) {
    HumanClass *H = &cT;
    int counter = 0;
    in >> *(dynamic_cast<HumanClass *>(H));
    cout << "Set Passport ID (ex. MC2978929): ";
    cT.PassportID = MyExcep_Input::check_Pass();
    cout << "\nHow many elem do you want to create?\n" << "Answer: ";
    counter = MyExcep_Input::check_int(10, 1);
    cT.setVStrct(cT.VStrct, counter);
    return in;
}

void TourisClass::Table() {
    cout << "\n|-----------------------------------------------------------------------------"
    << "--------------------------------|\n";
    cout << "|" << setw(55) << "Tourist" << setw(56) << "|\n";
    cout << "|-----------------------------------------------------------------------------"
    << "--------------------------------|\n";
    cout << "|" << setw(16) << "Name|" << setw(21) << "Last Name|" << setw(14) << "Bithday|"
    << setw(15) << "Passport ID|" << setw(15) << "Country|" << setw(15) << "Target Visit|"
    << setw(15) << "Data Visit|\n";
    cout << "|-----------------------------------------------------------------------------"
    << "--------------------------------|\n";
}

//bool operator==(const TourisClass &cT1, const TourisClass &cT2) {
//    if (cT1.PassportID != cT2.PassportID) return false;
//    if (cT1.VStrct.)
//    return true;
//}


void TourisClass::menuObj() {
    int menuInput = 0;
    while (menuInput < 8) {
        
        cout << "\nWhat do you want to do in this Human object?\n";
        cout << "1. Change Name.\n" << "2. Change Last Name.\n";
        cout << "3. Change date of birth.\n" << "4. Print Obj.\n";
        cout << "5. Change PassportID.\n" << "6. Change History.\n";
        cout << "7. Exit.\n" << "Answer: ";
        menuInput = MyExcep_Input::check_int(7, 1);
        int counter = 0;
        string Line;
        vector<int> newData(3);
        
        switch (menuInput) {
            case 1:
                cout << "Enter a new name: ";
                Line = MyExcep_Input::check_string(15);
                setNewName(Line);
                break;
                
            case 2:
                cout << "Enter a new last name: ";
                Line = MyExcep_Input::check_string(15);
                setNewLastName(Line);
                break;
                
            case 3:
                cout << "Enter new date of birth\n";
                SetData(newData);
                setDayBitrh(newData);
                break;
                
            case 4:
                cout << *this; 
                break;
                
            case 5:
                cout << "Enter new passport id: ";
                Line = MyExcep_Input::check_string(9);
                setPassportID(Line);
                break;
                
            case 6:
                cout << "How many element do you want create?" << "Answer: ";
                counter = MyExcep_Input::check_int(10, 1);
                VStrct.resize(counter);
                setVStrct(VStrct, counter);
                break;
                
            default:
                cout << "Close menu." << endl;
                break;
        }
    }
}
