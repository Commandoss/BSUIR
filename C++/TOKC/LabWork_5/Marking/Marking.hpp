//
//  Marking.hpp
//  main
//
//  Created by Belousov Ilya on 15.11.21.
//

#ifndef Marking_hpp
#define Marking_hpp

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/split_member.hpp>

#include "Status.hpp"
#include "Msg.hpp"
#include "Package.hpp"
#include "Cropping.hpp"
#include "Marker.hpp"

#include <sstream>
#include <string>


class Marking {
private:
    Marker value;

public:
    constexpr Marking() : value() {}

    void start();

    void set_source_adress(const std::string &adress);
    void set_destination_address(const std::string &adress);

    void set_start_delimiter();
    void set_access_control(const unsigned int &priority, const unsigned int &token);


    std::pair<unsigned int, unsigned int> get_access_control();

    template <class T>
    void set_data(const T &data) {
        std::stringstream ss;
        boost::archive::text_oarchive wr(ss);
        wr & data;

        size_t size = ss.str().size();

        memset(this->value.Data, '\0', sizeof(this->value.Data));
        memcpy(this->value.Data, ss.str().c_str(), size);

        this->value.FrameCheckSequence = size;
    }

    void set_frame_check_sequence();
    void set_ending_delimiter();
    void set_frame_status(const unsigned int &flag);
    void set_inter_frame_gap();

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

    friend std::ostream& operator<<(std::ostream &out, const Marking &M) {
        out << M.value;
        return out;
    }
};

#endif /* Marking_hpp */
