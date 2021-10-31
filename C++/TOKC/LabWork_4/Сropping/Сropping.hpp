//
//  Сropping.hpp
//  main
//
//  Created by Belousov Ilya on 31.10.21.
//

#ifndef _ropping_hpp
#define _ropping_hpp

#include "Frame.hpp"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/split_member.hpp>

class Cropping {
private:
    struct Frame value;

public:
    constexpr Cropping() : value{} {}

    void start() noexcept;

    char* get_data() noexcept

    template <typename Type;
    void change_data(type &data) {

    }
    
};

#endif /* _ropping_hpp */
