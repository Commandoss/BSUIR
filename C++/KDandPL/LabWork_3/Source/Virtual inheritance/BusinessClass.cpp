//
//  BusinessClass.cpp
//  LabWork_5_Human
//
//  Created by Belousov Ilya on 10/14/20.
//

#include "BusinessClass.hpp"

BusinessClass::BusinessClass() {
}

BusinessClass::BusinessClass(string str) {
    Adress.push_back(str);
}

BusinessClass::BusinessClass(vector<string> Vstr) {
    Adress = Vstr;
}

BusinessClass::~BusinessClass() {
    Adress.clear();
}

void BusinessClass::SetAdress(int cellNum, string str) {
    Adress[cellNum].clear();
    Adress[cellNum] = str;
}

void BusinessClass::SetVAdress(vector<string> Vstr) {
    Adress.clear();
    Adress = Vstr;
}

void BusinessClass::SettoAndAdress(string str) {
    Adress.push_back(str);
}

string BusinessClass::getElemVAdress(int cellNum) {
    return Adress[cellNum];
}

vector<string> BusinessClass::getVAdress() {
    return Adress;
}

ostream& operator<<(ostream &os, BusinessClass &cB) {
//    cB.Table();
    int cellNum_1 = 0, cellNum_2 = 0, cellNum_3 = 0;
    os << "|" << setw(12) << cB.getName() << "|";
    os << setw(17) << cB.getLastName() << "|";

    if (cB.getBirthDay() < 10)  cout << setw(4) << "0";
    else {
        os << setw(5);
    }
    os << cB.getBirthDay() << ".";
    if (cB.getBirthMonth() < 10) cout << "0";
    os << cB.getBirthMonth() << "." << cB.getBirthYear() << "|";
    os << setw(12) << cB.getPassportID() << "|";
    os << setw(24) << cB.getAdressReg() << "|";
    os << setw(12)<< cB.getLicence() << "|";
    
    while (true) {
        if (cellNum_1 == cB.VStrct.size() && cellNum_2 == cB.Pay.size()) break;
        
        if (cellNum_1 < cB.VStrct.size()) {
            os << setw(12) << cB.GetCountry(cellNum_1) << "|";
            os << setw(15) << cB.getTargetVis(cellNum_1) << "|";
            if (cB.getElemVDayVisit(cellNum_1, Day) < 10) cout << setw(5) << "0";
            else {
                os << setw(6);
            }
            os << cB.getElemVDayVisit(cellNum_1, Day) << ".";
            if (cB.getElemVDayVisit(cellNum_1, Month) < 10) cout << "0";
            os << cB.getElemVDayVisit(cellNum_1, Month) << "." << cB.getElemVDayVisit(cellNum_1, Year) << "|";
            cellNum_1++;
        } else {
            os << setw(13) << "|";
            os << setw(16) << "|";
            os << setw(15) << "|";
        }
            
        if (cellNum_2 < cB.Pay.size()) {
            os << setw(7) << cB.getSum(cellNum_2) << "|";

            if (cB.getDayPay(cellNum_2, Day) < 10) cout << setw(5) << "0";
            else {
                os << setw(6);
            }
            os << cB.getDayPay(cellNum_2, Day) << ".";
            if (cB.getDayPay(cellNum_2, Month) < 10) cout << "0";
            os << cB.getDayPay(cellNum_2, Month) << ".";
            os << cB.getDayPay(cellNum_2, Year) << "|";
            cellNum_2++;
        } else {
            os << setw(8) << "|";
            os << setw(15) << "|";
        }
        
        if (cellNum_3 < cB.Adress.size()) {
            os << setw(20) << cB.Adress[cellNum_3] << "|";
            cellNum_3++;
        } else {
            os << setw(21) << "|";
        }
        if ((cellNum_1 != cB.VStrct.size()) ||
            (cellNum_2 != cB.Pay.size())    ||
            (cellNum_3 != cB.Adress.size()  )) {
            os << "\n|" << setw(96) << "|";
            
        }
    }
    cout << "\n|-----------------------------------------------------------------------------"
    << "-----------------------------------------------------------------------------------"
    << "-----------------------|\n";
    return os;
}

istream& operator>>(istream &in, BusinessClass &cB) {
    int counter = 0;
    EntrepreneurClass *E = &cB;
    string str;
    in >> *(dynamic_cast<EntrepreneurClass *>(E));
    cout << "Set Passport ID (ex. MC2940789): ";
    cB.PassportID = MyExcep_Input::check_Pass();
    cout << "How many elem do you want to create?\n" << "Answer: ";
    counter = MyExcep_Input::check_int(10, 1);
    cB.setVStrct(cB.VStrct, counter);
    cout << "How many elem do you want to create?\n" << "Answer: ";
    counter = MyExcep_Input::check_int(10, 1);
    cB.Adress.resize(counter);
    for (int cell = 0; cell < cB.Adress.size(); cell++) {
        cout << "Set adress (ex. St. H. F.) #" << cell << "\n";
        fflush(stdin);
        cB.Adress[cell] = MyExcep_Input::check_Adress(30);
    }
    return in;
}

void BusinessClass::Table() {
    cout << "\n|-----------------------------------------------------------------------------"
    << "-----------------------------------------------------------------------------------"
    << "-----------------------|\n";
    cout << "|" << setw(90) << "Business" << setw(95) << "|\n";
    cout << "|-----------------------------------------------------------------------------"
    << "-----------------------------------------------------------------------------------"
    << "-----------------------|\n";
    cout << "|" << setw(13) << "Name|" << setw(18) << "Last Name|" << setw(14) << "Bithday|"
    << setw(13) << "Passport ID|" << setw(25) << "Adress Registration|"<< setw(13) << "Licence|"
    << setw(13) << "Country|" << setw(16) << "Target Visit|" << setw(15) << "Data Visit|"
    << setw(8) << "Sum|" << setw(15) << "DayPay|" << setw(22) << "Adress|\n";
    cout << "|-----------------------------------------------------------------------------"
    << "-----------------------------------------------------------------------------------"
    << "-----------------------|\n";
}

void BusinessClass::menuObj() {
    int menuInput = 0;
    while (menuInput < 8) {
        
        cout << "\nWhat do you want to do in this Human object?\n";
        cout << "1. Change Name.\n" << "2. Change Last Name.\n";
        cout << "3. Change date of birth.\n" << "4. Print Obj.\n";
        cout << "5. Change PassportID.\n" << "6. Change History.\n";
        cout << "7. Change Licence.\n" << "8. Change Adress Registration.\n";
        cout << "9. Change Payment.\n";
        cout << "10. Exit.\n" << "Answer: ";
        menuInput = MyExcep_Input::check_int(10, 1);
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
                
            case 7:
                cout << "Enter new licence: ";
                Line = MyExcep_Input::check_string(9);
                setLicence(Line);
                break;
                
            case 8:
                cout << "Enter new adress registration: ";
                Line = MyExcep_Input::check_string(30);
                setAdressReg(Line);
                break;
                
            case 9:
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


