//
//  Entrepreneur.cpp
//  Lab5
//
//  Created by Belousov Ilya on 10/9/20.
//

#include "EntrepreneurClass.hpp"

EntrepreneurClass::EntrepreneurClass() {
}

EntrepreneurClass::EntrepreneurClass(string licence, string adreessReg, vector<struct Payment> P) {
    this->Licence = licence;
    this->AdressReg = adreessReg;
    this->Pay = P;
    licence.clear();
    adreessReg.clear();
    P.clear();
}

EntrepreneurClass::~EntrepreneurClass() {
    Licence.clear();
    AdressReg.clear();
    Pay.clear();
}


string EntrepreneurClass::getLicence() {
    return Licence;
}

string EntrepreneurClass::getAdressReg() {
    return AdressReg;
}

struct Payment EntrepreneurClass::getCellVPay(const int cell) {
    return Pay[cell];
}

vector<struct Payment> EntrepreneurClass::getVPayment() {
    return Pay;
}

vector<int> EntrepreneurClass::getDayPay(const int cellNum) {
    return Pay[cellNum].DayPay;
}

int EntrepreneurClass::getDayPay(const int cellNum_1, const int cellNum_2) {
    return Pay[cellNum_1].DayPay[cellNum_2];
}

double EntrepreneurClass::getSum(const int cellNum) {
    return Pay[cellNum].Sum;
}

void EntrepreneurClass::setLicence(string licence) {
    Licence.clear();
    Licence = licence;
}

void EntrepreneurClass::setAdressReg(string adressReg) {
    AdressReg.clear();
    AdressReg = adressReg;
}

void EntrepreneurClass::setCellVPay(struct Payment P) {
    Pay.push_back(P);
}

void EntrepreneurClass::setPayment(vector<struct Payment> P) {
    Pay.clear();
    Pay = P;
}

void EntrepreneurClass::setPayment(vector<struct Payment> &P, int counter) {
    P.clear();
    P.resize(counter);
    for (int cell = 0; cell < P.size(); cell++) {
        Payment newP;
        cout << "Set Sum: ";
        newP.Sum = MyExcep_Input::check_double(100000, 0);
        cout << "Set Date Payment\n";
        SetData(newP.DayPay);
        P[cell] = newP;
    }
}

void EntrepreneurClass::setVDayPay(int cellNum, vector<int> NewVDayPay) {
    Pay[cellNum].DayPay.clear();
    Pay[cellNum].DayPay = NewVDayPay;
}

void EntrepreneurClass::setSum(int cellNum, double value) {
    Pay[cellNum].Sum = value;
}

ostream& operator<<(ostream &os, EntrepreneurClass &cE) {
//    cE.Table();
    os << "|" << setw(15) << cE.getName() << "|";
    os << setw(20) << cE.getLastName() << "|";
    os << setw(5);
    if (cE.getBirthDay() < 10) cout << 0;
    os << cE.getBirthDay() << ".";
    if (cE.getBirthMonth() < 10) cout << "0";
    os << cE.getBirthMonth() << "." << cE.getBirthYear() << "|";
    os << setw(14) << cE.getLicence() << "|";
    os << setw(39) << cE.getAdressReg() << "|";
    for (int cell = 0; cell < cE.Pay.size(); cell++) {
        if (cell == 1)
            cout << "|-----------------------------------------------------------"
                 << "----------------------------------------------|";
        
        if (cell > 1) cout << "|" << setw(106) << "|";
        
        os << setw(14) << cE.getSum(cell) << "|";
        os << setw(4);
        os << cE.getDayPay(cell, Day) << ".";
        if (cE.getDayPay(cell, Month) < 10) {
            os << "0";
        }
        os << cE.getDayPay(cell, Month) << ".";
        os << cE.getDayPay(cell, Year) << "|" << endl;
    }
    cout << "|---------------------------------------------------------------------------"
    << "----------------------------------------------------------|\n";
    return os;
}

istream& operator>>(istream &is, EntrepreneurClass &cE) {
    int counter = 0;
    Payment P;
    HumanClass *H = &cE;
    is >> *(dynamic_cast<HumanClass *>(H));
    cout << "Set Licence (ex. LIC123456): ";
    cE.Licence = MyExcep_Input::check_Lic();
    cout << "Set Adress Registration (ex. St. H. F.): ";
    cE.AdressReg = MyExcep_Input::check_Adress(40);
    cout << "\nHow many elem do you want to create?\n" << "Answer: ";
    counter = MyExcep_Input::check_int(10, 1);
    cE.setPayment(cE.Pay, counter);
    return is;
}

void EntrepreneurClass::Table() {
    cout << "\n|---------------------------------------------------------------------------"
    << "----------------------------------------------------------|\n";
    cout << "|" << setw(67) << "Entrepreneur" << setw(68) << "|\n";
    cout << "|---------------------------------------------------------------------------"
    << "----------------------------------------------------------|\n";
    cout << "|" << setw(16) << "Name|" << setw(21) << "Last Name|" << setw(14) << "Bithday|"
    << setw(15) << "Licence|" << setw(40) << "Adress Registration|" << setw(15) << "Sum|"
    << setw(14) << "Day Pay|\n";
    cout << "|---------------------------------------------------------------------------"
    << "----------------------------------------------------------|\n";
}

void EntrepreneurClass::menuObj() {
    int menuInput = 0;
    while (menuInput < 8) {
        
        cout << "\nWhat do you want to do in this Human object?\n";
        cout << "1. Change Name.\n" << "2. Change Last Name.\n";
        cout << "3. Change date of birth.\n" << "4. Print Obj.\n";
        cout << "5. Change Licence.\n" << "6. Change Adress Registration.\n";
        cout << "7. Change Payment";
        cout << "8. Exit.\n" << "Answer: ";
        menuInput = MyExcep_Input::check_int(8, 1);
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
                Table();
                cout << *this;
                break;
                
            case 5:
                cout << "Enter new licence: ";
                Line = MyExcep_Input::check_string(9);
                setLicence(Line);
                break;
                
            case 6:
                cout << "Enter new adress registration: ";
                Line = MyExcep_Input::check_string(30);
                setAdressReg(Line);
                break;
                
            case 7:
                cout << "How many element do you want create?" << "Answer: ";
                counter = MyExcep_Input::check_int(10, 1);
                Pay.resize(counter);
                setPayment(Pay, counter);
                break;
                
            default:
                cout << "Close menu." << endl;
                break;
        }
    }
}

