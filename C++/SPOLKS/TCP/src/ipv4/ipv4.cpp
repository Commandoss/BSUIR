//
//  ipv4.cpp
//  TCP
//
//  Created by Belousov Ilya on 16.09.22.
//

#include "ipv4.hpp"

std::string IPv4::to_string() const
{
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

uint32_t IPv4::to_uint32() const noexcept
{
    return (static_cast<uint32_t>(data[0]) << 24) |
    (static_cast<uint32_t>(data[1]) << 16) |
    (static_cast<uint32_t>(data[2]) << 8) |
    static_cast<uint32_t>(data[3]);
}

std::ostream &operator<<(std::ostream &os, const IPv4 &ip)
{
    os << static_cast<uint16_t>(ip.data.at(0)) << "."
    << static_cast<uint16_t>(ip.data.at(1)) << "."
    << static_cast<uint16_t>(ip.data.at(2)) << "."
    << static_cast<uint16_t>(ip.data.at(3));
    return os;
}

std::istream &operator>>(std::istream &is, IPv4 &ip)
{
    char d1, d2, d3;
    int b1, b2, b3, b4;
    
    is >> b1 >> d1 >> b2 >> d2 >> b3 >> d3 >> b4;
    if (d1 == '.' && d2 == '.' && d3 == '.')
    {
        ip = IPv4(b1, b2, b3, b4);
    }
    else
    {
        is.setstate(std::ios_base::failbit);
        return is;
    }

        
    return is;
}
