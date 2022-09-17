//
//  ipv4.hpp
//  TCP
//
//  Created by Belousov Ilya on 16.09.22.
//

#pragma once

#include <cstdint>
#include <array>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <ranges>

class IPv4
{
    std::array<uint8_t, 4> data;
    
public:
    constexpr IPv4() : data { 0 } {}
    constexpr IPv4(uint8_t a, uint8_t b,
                   uint8_t c, uint8_t d): data{{ a, b, c, d }} {}
                
    explicit constexpr IPv4(uint32_t address)
        : data {{ static_cast<uint8_t>((address >> 24) & 0xFF),
                  static_cast<uint8_t>((address >> 16) & 0xFF),
                  static_cast<uint8_t>((address >> 8) & 0xFF),
                  static_cast<uint8_t>(address & 0xFF) }} {}
    
    IPv4(const IPv4 &other) = default;
    IPv4(IPv4 &&other) = default;
    

    IPv4& operator=(const IPv4 &other) = default;
    IPv4& operator=(IPv4 &&other) = default;
    
    std::string to_string() const;
    uint32_t to_uint32() const noexcept;
    
    friend std::ostream &operator<<(std::ostream &os, const IPv4 &ip);
    friend std::istream &operator>>(std::istream &is, IPv4 &ip);
};
