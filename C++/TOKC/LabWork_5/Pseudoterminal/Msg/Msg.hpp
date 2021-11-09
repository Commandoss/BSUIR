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

const size_t MAX_SIZE_MSG_DATA = 1024;

struct MSG {
    std::string data;
    size_t size;

    void set_data(const std::string &data) {
        this->data = data;
        this->size = data.size();
    }

    template<class Archive>
    void save(Archive &ar, const unsigned int version) const {
        ar & this->data;
        ar & this->size;
    }

    template<class Archive>
    void load(Archive &ar, const unsigned int version) {
        ar & this->data;
        ar & this->size;
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
    friend class boost::serialization::access;

    friend std::ostream& operator<<(std::ostream &out, struct MSG &msg) {
        out << "\t---MSG---\n";
        out << "Data: " << msg.data << "\n";
        out << "Size data: " << msg.size << "\n";
        out << "\t---END PACK---\n";
        return out;
    }
};

#endif /* Msg_hpp */
