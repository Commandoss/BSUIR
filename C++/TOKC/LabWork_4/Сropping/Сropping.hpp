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

//    void start() noexcept;

    char* get_data() noexcept;

    template <typename Type>
    void change_data(Type &data) {

    }

    template<class Archive>
    void save(Archive &ar, const unsigned int version) const {
        ar & this->value;
    }

    template<class Archive>
    void load(Archive &ar, const unsigned int version) {
        ar & this->value;
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
    friend class boost::serialization::access;

    friend std::ostream& operator<<(std::ostream &out, Cropping &C);
//    friend std::istream& operator>>(std::istream &in, Cropping &C);

    void set_sender(const std::string &sender) noexcept;
    void set_recipiend(const std::string &recipiend) noexcept;

private:
    void set_preamble() noexcept;
    void set_SDF() noexcept;
    void set_size_frame() noexcept;

    const unsigned int fstart = 00101;
};

#endif /* _ropping_hpp */
