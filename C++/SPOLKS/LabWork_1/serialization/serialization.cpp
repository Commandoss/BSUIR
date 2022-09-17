//
//  serialization.cpp
//  TCP
//
//  Created by Belousov Ilya on 17.09.22.
//

#include "serialization.hpp"

std::ostream& operator<< (std::ostream& os, std::byte b) {
    return os << std::to_integer<uint16_t>(b);
}


