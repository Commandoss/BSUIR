//
//  Exception.hpp
//  LabWork_5_Human
//
//  Created by Belousov Ilya on 10/21/20.
//

#ifndef Exception_hpp
#define Exception_hpp

#include "Header.h"
#include <exception>
#include <iterator>
#include <istream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>

class MyException {
protected:
    std::string msg;
    int date;
public:
    MyException();
    MyException(int date);
    
    virtual int gateDate();
    virtual std::string What();
    //для файла новый exception 
};

#endif /* Exception_hpp */
