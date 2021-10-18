//
//  Socket.hpp
//  LabWork_2
//
//  Created by Belousov Ilya on 11.10.21.
//

#ifndef Socket_hpp
#define Socket_hpp

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>

class Socket {
protected:
    int sDescriptor;

    int domain;
    int type;
    int protocol;
    int port;

    struct sockaddr_in sAddr;

public:
    constexpr Socket() : domain{AF_INET}, protocol{SOCK_STREAM}, type{0}, port(8080), sDescriptor{-1} {
        memset(&sAddr, 0, sizeof(sockaddr));
    }
    constexpr Socket(const int domain, const int protocol,
                     const int type, const unsigned int port) : domain{domain}, protocol{protocol}, type{type}, port(port), sDescriptor{-1} {
        memset(&sAddr, 0, sizeof(sockaddr));
    }

    ~Socket() {
        shutdown(this->sDescriptor, 0);
    }
    // нужно сделать shutdown();
    void change_domain(const int domain) noexcept;
    void change_type(const int type) noexcept;
    void change_protocol(const int protocol) noexcept;

    virtual void start();

protected:
    void create();
    void init_server_sockaddr() noexcept;
    void set_sockaddr();

    void error(const std::string &msg) const;
};

#endif /* Socket_hpp */
