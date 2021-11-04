//
//  PStatus.hpp
//  main
//
//  Created by Belousov Ilya on 4.11.21.
//

#ifndef PStatus_hpp
#define PStatus_hpp

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/split_member.hpp>

const size_t STATUS_ADRESS_SIZE = 13;
const size_t STATUS_INFO_SIZE = 15;

struct status {
    char sender[STATUS_ADRESS_SIZE];
    char info[STATUS_INFO_SIZE];

    template<class Archive>
    void save(Archive &ar, const unsigned int version) const {
        ar & this->sender;
        ar & this->info;
    }

    template<class Archive>
    void load(Archive &ar, const unsigned int version) {
        ar & this->sender;
        ar & this->info;
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
    friend class boost::serialization::access;
};

#endif /* PStatus_hpp */