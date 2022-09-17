//
//  serialization.hpp
//  TCP
//
//  Created by Belousov Ilya on 17.09.22.
//

#pragma once

#include <sstream>
#include <bit>
#include <bitset>
#include <ranges>

#include <fstream>
#include <array>
#include <cstddef>
#include <iostream>

template <class To, class From>
std::enable_if_t<
    sizeof(To) == sizeof(From) &&
    std::is_trivially_copyable_v<From> &&
    std::is_trivially_copyable_v<To>, To> bit_cast(const From& src) noexcept
{
    To dst;
    std::memcpy(&dst, &src, sizeof(To));
    return dst;
}

std::ostream& operator<<(std::ostream& os, std::byte b);
 

class Serialization
{
private:
    std::stringstream stream;
    
public:
    Serialization() {}
    explicit Serialization(std::stringstream ss) : stream(std::move(ss)) {}
    explicit Serialization(std::stringstream &&ss) : stream(std::move(ss)) {}
 
    template <std::integral Type>
    friend Serialization &operator<<(Serialization &sr, Type data)
    {
        std::array<std::byte, sizeof(Type)> bytes_array;
        bytes_array = bit_cast<std::array<std::byte, sizeof(Type)>>(data);
        
//        std::byte byte;
//        std::cout << byte;
        
        auto str(sr.stream.str());
        
        std::ofstream ifs("/Users/ilya/Projects/BSUIR/C++/SPOLKS/LabWork_1/serialization/data.txt");
        
        ifs << sr.stream.rdbuf() << std::endl;
        
        return sr;
    }
};
