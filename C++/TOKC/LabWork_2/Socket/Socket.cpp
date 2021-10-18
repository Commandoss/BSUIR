//
//  Socket.cpp
//  LabWork_2
//
//  Created by Belousov Ilya on 11.10.21.
//

#include "Socket.hpp"

void Socket::change_domain(const int domain) noexcept {
    this->domain = domain;
}

void Socket::change_type(const int type) noexcept {
    this->type = type;
}

void Socket::change_protocol(const int protocol) noexcept {
    this->protocol = protocol;
}

void Socket::start() {
    create();
    init_server_sockaddr();
    set_sockaddr();
}

void Socket::create() {
    this->sDescriptor = socket(this->domain, this->protocol, this->type);

    if (this->sDescriptor < 0)
        error("Func: Socket::create()\nInfo: Unable to create socket");
}

void Socket::init_server_sockaddr() noexcept {
    this->sAddr.sin_family = this->domain;
    this->sAddr.sin_port = this->port;
    this->sAddr.sin_addr.s_addr = htonl(INADDR_ANY);
}

void Socket::set_sockaddr() {
    if (bind(this->sDescriptor, reinterpret_cast<struct sockaddr *>(&this->sAddr),
             sizeof(this->sAddr)) < 0)
        error("Func: bind");
}

void Socket::error(const std::string &msg) const {
    throw msg;
}
