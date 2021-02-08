//
//  Exception.hpp
//  Diary
//
//  Created by Belousov Ilya on 11.12.20.
//

#ifndef Exception_hpp
#define Exception_hpp

#define STRING_LEN 255
#define FILENAME_LEN 20

#include <string>
#include <iostream>

using namespace std;

class MyException {
protected:
    string msg;
    int date;
public:
    MyException();
    MyException(int date);
    ~MyException();
    
    virtual int gateDate();
    virtual string What();
};

#endif /* Exception_hpp */
