//
//  Package.hpp
//  LabWork_2
//
//  Created by Belousov Ilya on 11.10.21.
//

#ifndef Package_hpp
#define Package_hpp

#include <array>
#include <typeinfo>
#include "IPv4.hpp"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/split_member.hpp>

const size_t MAX_SIZE_PACK_DATA = 1024;

struct Pack {
    unsigned long fstart;
    unsigned long recipient;
    unsigned long sender;
    unsigned long fother;
    size_t sizeData;
    char data[MAX_SIZE_PACK_DATA];
    size_t sizePack;

    template<class Archive>
    void save(Archive &ar, const unsigned int version) const {
        ar & this->fstart;
        ar & this->recipient;
        ar & this->sender;
        ar & this->fother;
        ar & this->sizeData;
        ar & this->sizePack;
        ar & this->data;
    }

    template<class Archive>
    void load(Archive &ar, const unsigned int version) {
        ar & this->fstart;
        ar & this->recipient;
        ar & this->sender;
        ar & this->fother;
        ar & this->sizeData;
        ar & this->sizePack;
        ar & this->data;
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
    friend class boost::serialization::access;
    friend std::ostream& operator<<(std::ostream &out, struct Pack &P) {
        out << "\t---PACK---\n";
        out << "Fstart: " << P.fstart << "\n";
        out << "Recipient: " << P.recipient << "\n";
        out << "Sender: " << P.sender << "\n";
        out << "Fother: " << P.fother << "\n";
        out << "Size data: " << P.sizeData << "\n";
        out << "Data: " << P.data << "\n";
        out << "Size pack: " << P.sizePack << "\n";
        out << "\t---END PACK---\n";
        return out;
    }
};

const size_t MAX_SIZE_PACK = sizeof(struct Pack) * 2 + 100; // 100 - boost info

class Package {
private:
    struct Pack value;
    IPv4 sender;
    IPv4 recipient;

public:
    constexpr Package() : sender{}, recipient{}, value{} {}
    constexpr Package(const IPv4 &sender, const IPv4 &recipient) : sender{sender}, recipient{recipient}, value{} {}

    void start() noexcept;

    char* get_data() noexcept;

    void change_sender(const IPv4 &sender) noexcept;
    void change_recipiend(const IPv4 &recipiend) noexcept;

    template <typename Type>
    void change_data(Type &data) {
        this->value.fother = typeid(data).hash_code();

        memset(this->value.data, '\0', MAX_SIZE_PACK_DATA);
        memcpy(this->value.data, data, sizeof(data) * sizeof(*data));
//        int k[20];
//        memcpy(k, this->value.data, sizeof(data) * sizeof(*data));

        this->value.sizeData = sizeof(data);
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

    friend std::ostream& operator<<(std::ostream &out, Package &P);
//    friend std::istream& operator<<(std::istream &in, Package &P);
private:
    void set_flag() noexcept;
    void set_sender() noexcept;
    void set_recipiend() noexcept;
    void set_other_flag() noexcept;
    void set_size_pack() noexcept;

    friend class boost::serialization::access;

private:
    const unsigned long fstart = 02001;
};

#endif /* Package_hpp */
