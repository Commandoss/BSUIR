//
//  cTime.hpp
//  Bus_Stop
//
//  Created by Belousov Ilya on 19.06.21.
//

#ifndef cTime_hpp
#define cTime_hpp

#include <iostream>

using namespace::std;

class cTime {
private:
    unsigned int hour;
    unsigned int min;
    
public:
    cTime();
    cTime(const unsigned int newHour, const unsigned int newMin);
    
    void setTime(const unsigned int newHour, const unsigned int newMin);
    void setHour(const unsigned int newHour);
    void setMin(const unsigned int newMin);
    
    unsigned int getHour();
    unsigned int getMin();
    
//    friend ostream& operator<<(ostream &os, cTime &cT);
    void printTime();
};

#endif /* cTime_hpp */
