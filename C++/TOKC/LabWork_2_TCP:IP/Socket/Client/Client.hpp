//
//  Client.hpp
//  LabWork_2
//
//  Created by Belousov Ilya on 10.10.21.
//

#ifndef Client_hpp
#define Client_hpp

#include <arpa/inet.h>
#include "Socket.hpp"
#include "IPv4.hpp"
#include "Package.hpp"

class Client : public Socket {
private:
    IPv4 ip;
public:
    constexpr Client() : ip{} {
        memset(&sAddr, 0, sizeof(sAddr));
    }
    constexpr Client(const IPv4 &ip) : ip(ip) {
        memset(&sAddr, 0, sizeof(sAddr));
    }

    void change_ip(const IPv4 &ip) noexcept;

    void start() override;

    void send_message(const std::string msg) const;
    std::string get_message(const size_t size) const;

    void send_pack(const Package &pack) const;
    Package& get_pack() const;

private:
    void set_ip();
    void connect_to_server();
};

#endif /* Client_hpp */
