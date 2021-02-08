//
//  Work.cpp
//  Diary
//
//  Created by Belousov Ilya on 11.12.20.
//

#include "Work.hpp"

cWork::cWork() {
}

cWork::~cWork() {
    remove();
}

void cWork::changeEvent() {
    this->info.clear();
    cout << "Enter event information: " << endl;
    this->info = ExceptionInput::check_string(STRING_LEN);
}

void cWork::setEvent() {
    remove();
    cout << "\nEnter event information: " << endl;
    this->info = ExceptionInput::check_string(STRING_LEN);
        setData();
}

cWork& cWork::setData() {
    data.setData();
    return *this;
}

string cWork::getEvent() {
    return this->info;
}

time_t cWork::getData(int position) {
    return data.getData(position);
}

void cWork::remove() {
    this->data.clearData();
    this->info.clear();
}

