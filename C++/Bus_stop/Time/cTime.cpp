//
//  cTime.cpp
//  Bus_Stop
//
//  Created by Belousov Ilya on 19.06.21.
//

#include "cTime.hpp"

cTime::cTime() {
    hour = 0;
    min = 0;
}

cTime::cTime(const unsigned int newHour, const unsigned int newMin) {
    hour = newHour;
    min = newMin;
}

void cTime::setMin(const unsigned int newMin) {
    min = newMin;
}

void cTime::setHour(const unsigned int newHour) {
    hour = newHour;
}

void cTime::setTime(const unsigned int newHour, const unsigned int newMin) {
    hour = newHour;
    min = newMin;
}

unsigned int cTime::getMin() {
    return min;
}

unsigned int cTime::getHour() {
    return hour;
}

//ostream& operator<<(ostream &os, cTime &cT) {
//    os << cT.hour << ":" << cT.min;
//    return os;
//}

void cTime::printTime() {
    if (getHour() < 10 && getMin() < 10) {
        cout << "0" << getHour() << ":" << "0" << getMin();
    }
    else if (getHour() < 10) {
        cout << "0" << getHour() << ":" << getMin();
    } else if (getMin() < 10) {
        cout << getHour() << ":" << "0" << getMin();
    } else
        cout << getHour() << ":" << getMin();
    return;
}
