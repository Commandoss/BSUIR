//
//  Marker.hpp
//  main
//
//  Created by Belousov Ilya on 15.11.21.
//

#ifndef Marker_hpp
#define Marker_hpp

#include "Access.hpp"
#include "FrameState.hpp"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/split_member.hpp>

const size_t MARKER_ADRESS_SIZE = 13;

struct Marker {
    unsigned int StartingDelimiter;
    Access AccessControl;
    unsigned char DestinationAddress[MARKER_ADRESS_SIZE];
    unsigned char SourceAddress[MARKER_ADRESS_SIZE];
    char Data[100];
    size_t FrameCheckSequence;
    unsigned int EndingDelimiter;
    FrameState FrameStatus;
    unsigned int InterFrameGap;

    template<class Archive>
    void save(Archive &ar, const unsigned int version) const {
        ar & this->StartingDelimiter;
        ar & this->AccessControl;
        ar & this->DestinationAddress;
        ar & this->SourceAddress;
        ar & this->Data;
        ar & this->FrameCheckSequence;
        ar & this->InterFrameGap;
    }

    template<class Archive>
    void load(Archive &ar, const unsigned int version) {
        ar & this->StartingDelimiter;
        ar & this->AccessControl;
        ar & this->DestinationAddress;
        ar & this->SourceAddress;
        ar & this->Data;
        ar & this->FrameCheckSequence;
        ar & this->InterFrameGap;
    }

    void set_access(const unsigned int &priority, const unsigned int &token) {
        this->AccessControl.set_token_bit(token);
        this->AccessControl.set_priority_bit(priority);
    }

    std::pair<unsigned int, unsigned int> get_access() {
        return {this->AccessControl.get_priority_bit(), this->AccessControl.get_token_bit()};
    }

    void set_frame_status(const unsigned int &flag) {
        this->FrameStatus.set_frame_copied(flag);
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
    friend class boost::serialization::access;

    friend std::ostream& operator<<(std::ostream &out, const struct Marker &M) {
        out << "\t---Marker---\n";
        out << "Starting Delimiter: " << M.StartingDelimiter << "\n";
        out << "\tAccess Control\n"  << M.AccessControl << "\t----------\n";
        out << "Destination Address: " << M.DestinationAddress << "\n";
        out << "Source Address: " << M.SourceAddress << "\n";
        out << "Data: " << M.Data << "\n";
        out << "Frame Check Sequence: " << M.FrameCheckSequence << "\n";
        out << "Ending Delimiter: " << M.EndingDelimiter << "\n";
        out << "\tFrame Status\n" << M.FrameStatus << "\t----------\n";
        out << "Inter Frame Gap: " << M.InterFrameGap << "\n";
        out << "\t---END MARKER---\n";
        return out;
    }
};

#endif /* Marker_hpp */
