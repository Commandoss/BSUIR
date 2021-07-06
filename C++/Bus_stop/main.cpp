//
//  main.cpp
//  Bus_Stop
//
//  Created by Belousov Ilya on 19.06.21.
//

#include <iostream>
#include "cBusCompany.hpp"

void findBusUser(bus &userBus, cBusCompany &pComp, cBusCompany &gComp);
int checkTime(bus &checkBus);

string pathFile1 = "/Users/ilya/Projects/Bus_Stop/Bus_Stop/file/Timetable";

int main(int argc, const char * argv[]) {
    cBusCompany poshCompany("Posh");
    cBusCompany grottyCompany("Grotty");
    
    poshCompany.timetableUpdate();
    grottyCompany.timetableUpdate();
    
    poshCompany.timetableSort();
    grottyCompany.timetableSort();

    bus userBus;
    string lineTime;
    
    int menuAnswer = 0;
    while (menuAnswer != 5) {
        menuAnswer = 0;
        cout << "\nWhat do you want to do?";
        cout << "\n1. Find out the full schedule.";
        cout << "\n2. Find out the bus by time.";
        cout << "\n3. Add a bus to the schedule.";
        cout << "\n4. Remove bus from schedule.";
        cout << "\n5. Exit.";
        cout << "\nAnswer: ";
        cin >> menuAnswer;
        
        switch (menuAnswer) {
            case 1:
                cout << poshCompany;
                cout << grottyCompany;
                break;
                
            case 2:
                cout << "\nEnter the time at which the bus should be (exp: 07:33 answer: 07:45): ";
                cin >> lineTime;
                userBus.setDeparture(lineTime);
                cout << "\nFound route:\n";
                findBusUser(userBus, poshCompany, grottyCompany);
                cout << endl;
                break;
                
            case 3:
                cout << "\nFor which company do you want to add buses?";
                cout << "\n1." << poshCompany.getName();
                cout << "\n2." << grottyCompany.getName();
                cout << "\nAnswer: ";
                cin >> menuAnswer;
                
                if (menuAnswer == 1) {
                    cin >> poshCompany;
                    poshCompany.timetableSort();
                }
                else if (menuAnswer == 2) {
                    cin >> grottyCompany;
                    grottyCompany.timetableSort();
                }
                break;
                
            case 4:
                cout << "\nFor which company do you want to delete buses?";
                cout << "\n1." << poshCompany.getName();
                cout << "\n2." << grottyCompany.getName();
                cout << "\nAnswer: ";
                cin >> menuAnswer;
                
                if (menuAnswer == 1)
                    poshCompany.deleteBus();
                else if (menuAnswer == 2)
                    grottyCompany.deleteBus();
                break;
                
            default:
                remove(pathFile1.c_str());
                poshCompany.timetableSave();
                grottyCompany.timetableSave();
                break;
        }
    }
    return 0;
}

int checkTime(bus &checkBus) {
    if (checkBus.getDeparture().getHour() == checkBus.getArrival().getHour()) {
        return checkBus.getArrival().getMin() - checkBus.getDeparture().getMin();
    }
//    else if (checkBus.getDeparture().getHour() < checkBus.getArrival().getHour() && abs(int (checkBus.getArrival().getHour() - checkBus.getDeparture().getHour())) > 1) return 0;
    else if (checkBus.getDeparture().getHour() < checkBus.getArrival().getHour()) {
        return checkBus.getArrival().getMin() + (60 - checkBus.getDeparture().getMin());
    }
    return 0;
}

void findBusUser(bus &userBus, cBusCompany &pComp, cBusCompany &gComp) {
    bus poshBus, grottyBus;
    cBusCompany findCBus;
    poshBus = pComp.findBus(userBus); // он важней
    grottyBus = gComp.findBus(userBus);
    
    if (checkTime(poshBus) == 0) {
        cout << "Grotty ";
        grottyBus.printBus();
        return;
    }
    else if (checkTime(grottyBus) == 0) {
        cout << "Posh ";
        poshBus.printBus();
        return;
    }
    else if (poshBus.getDeparture().getHour() == grottyBus.getDeparture().getHour() &&
        poshBus.getDeparture().getMin() == grottyBus.getDeparture().getMin()) {
        if (checkTime(poshBus) <= checkTime(grottyBus)) {
            cout << "Posh ";
            poshBus.printBus();
        }
        else {
            cout << "Grotty ";
            grottyBus.printBus();
        }
    } //Если он начинается в то же время и достигает более раннего срока
    else if (poshBus.getArrival().getHour() == grottyBus.getArrival().getHour() &&
             poshBus.getArrival().getMin() == grottyBus.getArrival().getMin()) {
        if (checkTime(poshBus) <= checkTime(grottyBus)) {
            cout << "Posh ";
            poshBus.printBus();
        }
        else {
            cout << "Grotty ";
            grottyBus.printBus();
        }
    } // Если он начнется позже и достигнет в то же время
    else if (poshBus.getArrival().getHour() <= grottyBus.getArrival().getHour() &&
             poshBus.getArrival().getMin() < grottyBus.getArrival().getMin()) {
        cout << "Posh ";
        poshBus.printBus();
        
    } // Если он начнется позже и достигнет раньше.
    else if (poshBus.getArrival().getHour() >= grottyBus.getArrival().getHour() &&
             poshBus.getArrival().getMin() > grottyBus.getArrival().getMin()) {
        cout << "Grotty ";
        grottyBus.printBus();
    }
    else {
        cout << "\nNo found...404";
    }
}
