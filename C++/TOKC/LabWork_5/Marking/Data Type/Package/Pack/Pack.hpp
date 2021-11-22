//
//  Pack.hpp
//  LabWork_4
//
//  Created by Belousov Ilya on 28.10.21.
//

#ifndef Pack_hpp
#define Pack_hpp

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/split_member.hpp>

const size_t MAX_SIZE_PACK_DATA = 150;
const size_t PACK_ADRESS_SIZE = 13;

struct Pack {
    unsigned long Fstart;
    char Recipient[PACK_ADRESS_SIZE];
    char Sender[PACK_ADRESS_SIZE];
    unsigned long Fother;
    size_t SizeData;
    char Data[MAX_SIZE_PACK_DATA];
    size_t SizePack;

    template<class Archive>
    void save(Archive &ar, const unsigned int version) const {
        ar & this->Fstart;
        ar & this->Recipient;
        ar & this->Sender;
        ar & this->Fother;
        ar & this->SizeData;
        ar & this->SizePack;
        ar & this->Data;
    }

    template<class Archive>
    void load(Archive &ar, const unsigned int version) {
        ar & this->Fstart;
        ar & this->Recipient;
        ar & this->Sender;
        ar & this->Fother;
        ar & this->SizeData;
        ar & this->SizePack;
        ar & this->Data;
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
    friend class boost::serialization::access;
    
    friend std::ostream& operator<<(std::ostream &out, const struct Pack &P) {
        out << "\t---PACK---\n";
        out << "Fstart: " << P.Fstart << "\n";
        out << "Recipient: " << P.Recipient << "\n";
        out << "Sender: " << P.Sender << "\n";
        out << "Fother: " << P.Fother << "\n";
        out << "Size data: " << P.SizeData << "\n";
        out << "Data: " << P.Data << "\n";
        out << "Size pack: " << P.SizePack << "\n";
        out << "\t---END PACK---\n";
        return out;
    }
};

const size_t MAX_SIZE_PACK = sizeof(struct Pack) * 3;

#endif /* Pack_hpp */
