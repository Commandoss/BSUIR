//
//  Personal.cpp
//  Diary
//
//  Created by Belousov Ilya on 11.12.20.
//

#include "Personal.hpp"

cPersonal::cPersonal() {
    
}

cPersonal::~cPersonal() {
    remove();
}

void cPersonal::setEvent() {
    cout << "\nEnter event information: " << endl;
    this->info = ExceptionInput::check_string(STRING_LEN);
}

string cPersonal::getEvent() {
    return this->info;
}

void cPersonal::remove() {
    this->info.clear();
}

