//
//  Calendar.cpp
//  Diary
//
//  Created by Belousov Ilya on 13.12.20.
//

#include "Calendar.hpp"

Calendar::Calendar() {
}

Calendar::~Calendar() {
}

time_t Calendar::getYear() const {
    return tm_year;
}

time_t Calendar::getMonth() const {
    return tm_month;
}

time_t Calendar::getDay() const {
    return tm_day;
}

time_t Calendar::getHour() const {
    return tm_hour;
}

time_t Calendar::getMinutes() const {
    return tm_minutes;
}

time_t Calendar::getData(int type) const {
    switch (type) {
        case 1:
            return getDay();
            break;
            
        case 2:
            return getMonth();
            break;
            
        case 3:
            return getYear();
            break;
            
        case 4:
            return getHour();
            break;
            
        case 5:
            return getMinutes();
            break;
            
        default:
            break;
    }
    return 0;
}

//time_t Calendar::getSeconds() const {
//    return tm_seconds;
//}

void Calendar::setYear(time_t value) {
    tm_year = value;
}

void Calendar::setMonth(time_t value) {
    tm_month = value;
}

void Calendar::setDay(time_t value) {
    tm_day = value;
}

void Calendar::setHour(time_t value) {
    tm_hour = value;
}

void Calendar::setMinutes(time_t value) {
    tm_minutes = value;
}

//void Calendar::setSeconds(time_t value) {
//    tm_seconds = value;
//}

void Calendar::setData() {
    cout << "Set day: ";
    tm_day = ExceptionInput::check_day();
    cout << "Set month: ";
    tm_month = ExceptionInput::check_month();
    cout << "Set year: ";
    tm_year = ExceptionInput::check_year(tm_day, tm_month);
}

void Calendar::setTime() {
    cout << "Set Hour: ";
    tm_hour = ExceptionInput::check_time(1);
    cout << "Set minutes: ";
    tm_minutes = ExceptionInput::check_time(2);
}

string Calendar::getDayWeek() const {

    string dayOfWeek[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    short countDayOfWeek[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    long a = (14 - tm_month) / 12;
    long y = tm_year - a;
    long m = tm_month + 12 * a - 2;

    return dayOfWeek[(tm_day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7];

}

void Calendar::showDate() const {
    cout << tm_day << "." << tm_month << "." << tm_year << endl;
}

void Calendar::showTime() const {
    cout << tm_hour << ":" << tm_minutes << endl;
}

Calendar& Calendar::clearData() {
    tm_day = -1;
    tm_month = -1;
    tm_year = -1;
    tm_hour = -1;
    tm_minutes = -1;
    return *this;
}

Calendar& Calendar::clearTime() {
    tm_hour = -1;
    tm_minutes = -1;
    return *this;
}

bool Calendar::emptyData() {
    if (tm_day == -1) return true;
    return false;
}

bool Calendar::emptyTime() {
    if (tm_hour == -1) return true;
    return false;
}

void Calendar::getSisTime() {
    struct tm *t;
    time_t ltime;
    time(&ltime);
    t = localtime(&ltime);
    tm_day = t->tm_mday;
    tm_month = t->tm_mon + 1;
    tm_year = t->tm_year + 1900;
    tm_hour = t->tm_hour;
    tm_minutes = t->tm_min;
}
