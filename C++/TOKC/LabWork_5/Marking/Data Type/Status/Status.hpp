//
//  Status.hpp
//  main
//
//  Created by Belousov Ilya on 4.11.21.
//

#ifndef Status_hpp
#define Status_hpp

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/split_member.hpp>

const size_t STATUS_ADRESS_SIZE = 13;
const size_t STATUS_INFO_SIZE = 15;

const char collision[STATUS_INFO_SIZE] = "$$$$$$$$$$$$$$";

enum status_flags {
    connect = 0,
    disconnect,
    error,
};

struct Status {
    unsigned int Flag;

    template<class Archive>
    void save(Archive &ar, const unsigned int version) const {
        ar & this->Flag;
    }

    template<class Archive>
    void load(Archive &ar, const unsigned int version) {
        ar & this->Flag;
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
    friend class boost::serialization::access;

//    void set_connect(const std::string &device) {
//        strcpy(this->Sender, device.c_str());
//        this->Flag = connect;
//    }

    void set_disconnect() {
        this->Flag = disconnect;
    }
//
//    void set_error(const std::string &device) {
//        strcpy(this->Sender, device.c_str());
//        strcpy(this->Info, collision);
//        this->Flag = error;
//    }
};

#endif /* Status_hpp */
