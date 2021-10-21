//
//  Package.cpp
//  LabWork_2
//
//  Created by Belousov Ilya on 11.10.21.
//

#include "Package.hpp"


void Package::set_sender() noexcept {
//    this->value.sender = this->sender.to_unlong();
}

void Package::set_recipiend() noexcept {
//    this->value.recipient = this->recipient.to_unlong();
}

void Package::set_size_pack() noexcept {
    this->value.sizePack = sizeof(this->value);
}

void Package::set_flag() noexcept {
    this->value.fstart = this->fstart;
}

void Package::set_other_flag() noexcept {

}

void Package::start() noexcept {
    set_flag();
//    set_other_flag();
    set_recipiend();
    set_sender();
    set_size_pack();
}

char* Package::get_data() noexcept {
    return this->value.data;
}

std::ostream& operator<<(std::ostream &out, Package &P) {
    out << P.value;
    return out;
}


