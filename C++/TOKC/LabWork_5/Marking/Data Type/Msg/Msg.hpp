//
//  Msg.hpp
//  main
//
//  Created by Belousov Ilya on 9.11.21.
//

#ifndef Msg_hpp
#define Msg_hpp

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/split_member.hpp>

#include <string>

const size_t MAX_SIZE_MSG_DATA = 100;
const size_t MSG_ADRESS_SIZE = 13;

struct Msg {
    char Sender[MSG_ADRESS_SIZE];
    char Destination[MSG_ADRESS_SIZE];
    std::string Data;
    size_t Size;

    void set_data(const std::string &data) {
        this->Data = data;
        this->Size = data.size();
    }

    void set_sender(const std::string &device) {
        strcpy(this->Sender, device.c_str());
    }

    void set_destination(const std::string &device) {
        strcpy(this->Destination, device.c_str());
    }

    template<class Archive>
    void save(Archive &ar, const unsigned int version) const {
        ar & this->Data;
        ar & this->Size;
    }

    template<class Archive>
    void load(Archive &ar, const unsigned int version) {
        ar & this->Data;
        ar & this->Size;
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
    friend class boost::serialization::access;

    friend std::ostream& operator<<(std::ostream &out, const struct Msg &msg) {
        out << "\t---MSG---\n";
        out << "Data: " << msg.Data << "\n";
        out << "Size data: " << msg.Size << "\n";
        out << "\t---END PACK---\n";
        return out;
    }
};

const size_t MAX_SIZE_MSG = MAX_SIZE_MSG_DATA + sizeof(struct Msg);

#endif /* Msg_hpp */
