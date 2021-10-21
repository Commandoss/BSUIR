//
//  Server.hpp
//  LabWork_2
//
//  Created by Belousov Ilya on 10.10.21.
//

#ifndef Server_hpp
#define Server_hpp

#include "Socket.hpp"
#include "IPv4.hpp"
#include "Package.hpp"

class Server : public Socket {
private:
    int cDescriptor;
    unsigned int queue;
public:
    constexpr Server() : cDescriptor(-1), queue(20) {}
    constexpr Server(const unsigned int queue) : cDescriptor(-1), queue(queue) {
    }

    void change_queue(const unsigned int queue) noexcept;

    void start() override;

    void send_message(const std::string msg) const;
    std::string get_message(const size_t size) const;

    void send_bath(const Package &pack) const;
    Package& get_bath() const;

private:
    void set_queue_connect() const;
    void accept_connection();
};

#endif /* Server_hpp */
