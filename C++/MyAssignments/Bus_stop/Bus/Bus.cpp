//
//  Bus.cpp
//  Bus_Stop
//
//  Created by Belousov Ilya on 19.06.21.
//

#include "Bus.hpp"

bus::bus() {
    
}

void bus::setRoute(string line) {
    route = line;
}


void bus::setArrival(string line) {
    arrival.setHour(stoi(line.substr(0, line.find(':'))));
    arrival.setMin(stoi(line.substr(line.find(':') + 1, line.size())));
}

void bus::setDeparture(string line) {
    departure.setHour(stoi(line.substr(0, line.find(':'))));
    departure.setMin(stoi(line.substr(line.find(':') + 1, line.size())));
}

bool bus::checkTime() {
    if (departure.getHour() > arrival.getHour()) return false;
    else if (departure.getHour() == arrival.getHour()) {
        if ((arrival.getMin() - departure.getMin()) > 50) return false;
    }
    else if (departure.getHour() < arrival.getHour() && abs(int(arrival.getHour() - departure.getHour())) > 1) return false;
    else if (departure.getHour() < arrival.getHour()) {
        if ((arrival.getMin() + (60 - departure.getMin())) > 50) return false;
    }
    
    return true;
}

string bus::getRoute() {
    return route;
}

cTime bus::getDeparture() {
    return departure;
}

cTime bus::getArrival() {
    return arrival;
}

void bus::printBus() {
    getDeparture().printTime();
    cout << " ";
    getArrival().printTime();
    return;
}
