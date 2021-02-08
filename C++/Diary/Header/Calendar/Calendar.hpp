//
//  Calendar.hpp
//  Diary
//
//  Created by Belousov Ilya on 13.12.20.
//

#ifndef Calendar_hpp
#define Calendar_hpp

#include "ExceptionInput.hpp"

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <ctime>
 
using namespace std;
 
class Calendar {
public:
    Calendar();
    ~Calendar();
    
    time_t getYear() const;
    time_t getMonth() const;
    time_t getDay() const;
    
    time_t getHour() const;
    time_t getMinutes() const;
//    time_t getSeconds() const;
    
    time_t getData(int type) const;
    
    void setYear(time_t value);
    void setMonth(time_t value);
    void setDay(time_t value);
    
    void setData();
    void setTime();
    
    void setHour(time_t value);
    void setMinutes(time_t value);
//    void setSeconds(time_t value);
    
    string getDayWeek() const;
    void showDate() const;
    void showTime() const;
//    double timeСheck();
    Calendar& clearData();
    Calendar& clearTime();
    
    bool emptyData();
    bool emptyTime();
    
    void getSisTime();
    
private:
    time_t tm_day;
    time_t tm_month;
    time_t tm_year;
    
    time_t tm_minutes;
    time_t tm_hour;
//    time_t tm_seconds;
};

#endif /* Calendar_hpp */
