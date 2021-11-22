//
//  Error.hpp
//  LabWork_4
//
//  Created by Belousov Ilya on 28.10.21.
//

#ifndef Error_hpp
#define Error_hpp

#include <string>
#include <exception>

class Error : public std::exception {
private:
    std::string message;
    std::string function;
public:
    explicit Error(const char* where, const char* msg) : message(msg), function(where) {}
    explicit Error(const std::string &msg, const std::string &where) : message(msg), function(where) {}

    virtual ~Error() noexcept {}

    virtual const char* what() const noexcept {
        return message.c_str();
    }

    const char* where() const noexcept {
        return function.c_str();
    }
};

#endif /* Error_hpp */
