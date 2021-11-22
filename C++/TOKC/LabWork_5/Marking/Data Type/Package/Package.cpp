//
//  Package.cpp
//  LabWork_4
//
//  Created by Belousov Ilya on 28.10.21.
//

#include "Package.hpp"

void Package::set_sender(const std::string &sender) noexcept {
    memcpy(this->value.Sender, sender.c_str(), sizeof(this->value.Sender));
}

void Package::set_recipiend(const std::string &recipiend) noexcept {
    memcpy(this->value.Recipient, recipiend.c_str(), sizeof(this->value.Recipient));
}

void Package::set_size_pack() noexcept {
    this->value.SizePack = sizeof(this->value);
}

void Package::set_flag() noexcept {
    this->value.Fstart = this->fstart;
}

void Package::set_other_flag() noexcept {

}

void Package::start() noexcept {
    set_flag();
    set_other_flag();
    set_size_pack();
}

char* Package::get_data() noexcept {
    return this->value.Data;
}

std::string Package::get_sender() {
    return this->value.Sender;
}

std::string Package::get_recipient() {
    return this->value.Recipient;
}



