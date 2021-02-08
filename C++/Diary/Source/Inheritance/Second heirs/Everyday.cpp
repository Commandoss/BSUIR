//
//  Everyday.cpp
//  Diary
//
//  Created by Belousov Ilya on 11.12.20.
//

#include "Everyday.hpp"

cEveryday::cEveryday() {
}

cEveryday::~cEveryday() {
    remove();
}

void cEveryday::changeEvent() {
    this->info.clear();
    cout << "Enter event information: " << endl;
    this->info = ExceptionInput::check_string(STRING_LEN);
}

void cEveryday::setEvent() {
    remove();
    cout << "Enter event information: " << endl;
    this->info = ExceptionInput::check_string(STRING_LEN);
    setData();
    setTime();
}

void cEveryday::setData() {
    data.setData();
}

void cEveryday::setTime() {
    data.setTime();
}

string cEveryday::getEvent() {
    return this->info;
}

time_t cEveryday::getTime(int position) {
    return data.getData(position);
}

time_t cEveryday::getData(int position) {
    return data.getData(position);
}


void cEveryday::remove() {
    data.clearData();
    this->info.clear();
    data.clearTime();
}

bool cEveryday::emptyData() {
    return data.emptyData();
}

bool cEveryday::emptyTime() {
    return data.emptyData();
}
