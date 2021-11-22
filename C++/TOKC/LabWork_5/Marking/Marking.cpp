//
//  Marking.cpp
//  main
//
//  Created by Belousov Ilya on 15.11.21.
//

#include "Marking.hpp"

void Marking::start() {
    this->set_start_delimiter();
    this->set_ending_delimiter();
    this->set_frame_check_sequence();
    this->set_inter_frame_gap();
}

void Marking::set_start_delimiter() {

}

void Marking::set_access_control(const unsigned int &priority, const unsigned int &token) {
    this->value.set_access(priority, token);
}

std::pair<unsigned int, unsigned int> Marking::get_access_control() {
    return this->value.get_access();
}

void Marking::set_source_adress(const std::string &adress) {
    memcpy(this->value.SourceAddress, adress.c_str(), sizeof(this->value.SourceAddress));
}

void Marking::set_destination_address(const std::string &adress) {
    memcpy(this->value.DestinationAddress, adress.c_str(), sizeof(this->value.DestinationAddress));
}

void Marking::set_frame_check_sequence() {
    this->value.FrameCheckSequence = sizeof(this->value);
}

void Marking::set_ending_delimiter() {

}

void Marking::set_frame_status(const unsigned int &flag) {
    this->value.set_frame_status(flag);
}

void Marking::set_inter_frame_gap() {

}


