//
//  cBusCompany.cpp
//  Bus_Stop
//
//  Created by Belousov Ilya on 19.06.21.
//

#include "cBusCompany.hpp"

string pathFile = "/Users/ilya/Projects/Bus_Stop/Bus_Stop/file/Timetable";

cBusCompany::cBusCompany() {
}

cBusCompany::cBusCompany(string newName) {
    name = newName;
}

cBusCompany::cBusCompany(const cBusCompany &copyCBC) {
    name = copyCBC.name;
    timetable = copyCBC.timetable;
}

cBusCompany::~cBusCompany() {
}

void cBusCompany::setName(string newName) {
    name = newName;
}

void cBusCompany::setBus(bus addBus) {
    timetable.push_back(addBus);
}

bool cBusCompany::timetableUpdate() {
    cFile cF;
    timetable = cF.readFileToBC(pathFile, name);
    return false;
}

string cBusCompany::getName() {
    return name;
}

void cBusCompany::addNewBus() {
    if (timetable.size() <= 50) {
        bus b;
        string line;
        cout << "\nSet time departure (exp: 08:33): ";
        cin >> line;
        b.setDeparture(line);
        
        cout << "Set time arrival (exp: 08:33): ";
        cin >> line;
        b.setArrival(line);
        if (!b.checkTime()) {
            cout << "\nThe time of one flight cannot be more than 50 minutes!";
            cout << "\nTry again.";
            return;
        }
        timetable.push_back(b);
    } else {
        cout << "\nThe limit on the number of buses in the schedule has been exceeded!";
        cout << "\nPlease delete at least one entry and try again.";
    }
    
}

void cBusCompany::deleteBus() {
    int answer = 0;
    cout << "\nWhich of the following buses do you want to remove?";
    cout << *this;
    cout << "Answer: ";
    cin >> answer;
    answer--;
    if (answer <= timetable.size()) {
        timetable.erase(timetable.begin() + answer, timetable.begin() + (answer + 1));
    }
}

bus cBusCompany::findBus(bus &userBus) {
    for (auto b : timetable) {
        if (abs(int (userBus.getDeparture().getHour() - b.getDeparture().getHour())) >= 1) continue;
        else if (userBus.getDeparture().getHour() < b.getDeparture().getHour()) return b;
        else if (userBus.getDeparture().getHour() == b.getDeparture().getHour()) {
            if (userBus.getDeparture().getMin() <= b.getDeparture().getMin()) return b;
        }
    }
    return userBus;
}

bool cBusCompany::timetableSave() {
    cFile cF;
    return cF.writeBCToFile(pathFile, name, timetable);;
}

void cBusCompany::timetableSort() {
    sort(timetable.begin(), timetable.end(), [](bus a, bus b) {
        if (a.getDeparture().getHour() < b.getDeparture().getHour()) return true;
        else if (a.getDeparture().getHour() == b.getDeparture().getHour()) {
            return (a.getDeparture().getMin() < b.getDeparture().getMin());
        }
        return false;});
}

ostream& operator<<(ostream &os, cBusCompany &cBC) {
    int counter = 1;
    os << "\nBus company: " << cBC.name;
    os << "\nTimetable:\n";
    for (auto bus : cBC.timetable) {
        os << counter << ". ";
        bus.printBus();
        os << "\n";
        counter++;
    }
    return os;
}

ofstream& operator<<(ofstream &of, cBusCompany &cBC) {
    for (auto bus : cBC.timetable) {
        of << cBC.name;
        bus.printBus();
        of << "\n";
    }
    return of;
}

istream& operator>>(istream &in, cBusCompany &cBC) {
    cBC.addNewBus();
    return in;
}
