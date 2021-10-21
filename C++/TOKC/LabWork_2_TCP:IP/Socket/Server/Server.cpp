//
//  Server.cpp
//  LabWork_2
//
//  Created by Belousov Ilya on 10.10.21.
//

#include "Server.hpp"

void Server::change_queue(const unsigned int queue) noexcept {
    this->queue = queue;
}

void Server::set_queue_connect() const {
    if (listen(this->sDescriptor, this->queue) < 0)
        error("Func: Server::set_queue_connect()");
}

void Server::accept_connection() {
    socklen_t len = sizeof(this->sAddr);
    this->cDescriptor = accept(this->sDescriptor, reinterpret_cast<struct sockaddr *>(&this->sAddr), &len);

    if (this->cDescriptor < 0)
        error("Func: Server::accept_connection()\nInfo: Failed to accept connections");
}

void Server::start() {
    create();
    init_server_sockaddr();
    set_sockaddr();
    set_queue_connect();
    accept_connection();
}

void Server::send_message(const std::string msg) const {
    if (send(this->cDescriptor, msg.c_str(), msg.size(), 0) < 0)
        error("Func: Server::send_message()\nInfo: Failed to send message.");
}

std::string Server::get_message(const size_t size) const {
    char msg[size];
    if (recv(this->cDescriptor, msg, size, 0) < 0)
        error("Func: Server::get_message()\nInfo: Failed to receive message");

    return msg;
}

void Server::send_bath(const Package &pack) const {
    std::stringstream ss;
    boost::archive::text_oarchive writer(ss);
    writer & pack;

    if (send(this->cDescriptor, ss.str().c_str(), MAX_SIZE_PACK, 0) < 0)
        error("Func: Client::send_message()\nInfo: Failed to send message.");
}

Package& Server::get_bath() const {
    char msg[MAX_SIZE_PACK + 1];

    if (recv(this->cDescriptor, msg, MAX_SIZE_PACK, 0) < 0)
        error("Func: Server::get_message()\nInfo: Failed to receive message");

    Package pack;
    std::stringstream ss(msg);
    boost::archive::text_iarchive reader(ss);
    reader & pack;
    
    return pack;
}

