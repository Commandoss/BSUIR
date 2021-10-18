//
//  Client.cpp
//  LabWork_2
//
//  Created by Belousov Ilya on 10.10.21.
//

#include "Client.hpp"

void Client::start() {
    create();
    init_server_sockaddr();
    set_ip();
    connect_to_server();
}

void Client::set_ip() {
    if (inet_pton(AF_INET, this->ip.to_string().c_str(), &this->sAddr.sin_addr) != 1) {
        error("Func: Client::set_ip()\nInfo: inet_pton error");
    }
}

void Client::connect_to_server() {
    if (connect(this->sDescriptor, reinterpret_cast<struct sockaddr *>(&this->sAddr),
                sizeof(sAddr)) < 0)
        error("Func: Client::connect_to_server()\nInfo: Error connect");
}

void Client::send_message(const std::string msg) const {
    if (send(this->sDescriptor, msg.c_str(), msg.size(), 0) < 0)
        error("Func: Client::send_message()\nInfo: Failed to send message.");
}

std::string Client::get_message(const size_t size) const {
    char msg[size];
    if (recv(this->sDescriptor, msg, size, 0) < 0)
        error("Func: Client::get_message()\nInfo: Failed to receive message");

    return msg;
}

void Client::send_pack(const Package &pack) const {
    std::stringstream ss;
    boost::archive::text_oarchive writer(ss);
    writer & pack;

    size_t a = ss.str().size();
    if (send(this->sDescriptor, ss.str().c_str(), ss.str().size(), 0) < 0)
        error("Func: Client::send_message()\nInfo: Failed to send message.");
}

Package& Client::get_pack() const {
    char msg[MAX_SIZE_PACK];

    if (recv(this->sDescriptor, msg, MAX_SIZE_PACK, 0) < 0)
        error("Func: Server::get_message()\nInfo: Failed to receive message");

    Package P;
    std::stringstream ss(msg);
    boost::archive::text_iarchive reader(ss);
    reader & P;

    return P;
}
