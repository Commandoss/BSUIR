//
//  Cropping.hpp
//  main
//
//  Created by Belousov Ilya on 3.11.21.
//

#ifndef Cropping_hpp
#define Cropping_hpp

#include "Frame.hpp"

class Cropping {
private:
    struct Frame value;

public:
    constexpr Cropping() : value{} {}

    void start() noexcept;

    char* get_data() noexcept;
    std::string get_recipient();
    std::string get_sender();

    void set_sender(const std::string &sender) noexcept;
    void set_recipiend(const std::string &recipiend) noexcept;

    template <typename T>
    void change_data(const T &data) {
        memset(this->value.Data, '\0', MAX_SIZE_FRAME_DATA);
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

    friend std::ostream& operator<<(std::ostream &out, const Cropping &C) {
        out << C.value;
        return out;
    }

private:
    void set_preamble() noexcept;
    void set_SFD() noexcept;
    void set_size_frame() noexcept;

    const unsigned int fstart = 00101;
};

#endif /* Cropping_hpp */
