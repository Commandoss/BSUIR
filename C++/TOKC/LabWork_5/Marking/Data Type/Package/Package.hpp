//
//  Package.hpp
//  LabWork_4
//
//  Created by Belousov Ilya on 28.10.21.
//

#ifndef Package_hpp
#define Package_hpp

#include "Pack.hpp"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/split_member.hpp>

#include <array>
#include <typeinfo>

class Package {
private:
    struct Pack value;

public:
    constexpr Package() : value{} {}

    void start() noexcept;

    char* get_data() noexcept;

    std::string get_recipient();
    std::string get_sender();

    void set_sender(const std::string &sender) noexcept;
    void set_recipiend(const std::string &recipiend) noexcept;

    template <typename T>
    void change_data(const T &data) {
        this->value.Fother = typeid(data).hash_code();

        memset(this->value.Data, '\0', MAX_SIZE_PACK_DATA);
        memcpy(this->value.Data, data, sizeof(data) * sizeof(*data));

        this->value.SizeData = sizeof(data);
    }
    
private:
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

    friend std::ostream& operator<<(std::ostream &out, const Package &P) {
        out << P.value;
        return out;
    }

private:
    void set_flag() noexcept;
    void set_other_flag() noexcept;
    void set_size_pack() noexcept;

private:
    const unsigned long fstart = 02001;
};

#endif /* Package_hpp */
