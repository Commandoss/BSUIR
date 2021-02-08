//
//  Everyday.hpp
//  Diary
//
//  Created by Belousov Ilya on 11.12.20.
//

#ifndef Everyday_hpp
#define Everyday_hpp

#include "Event.hpp"

class cEveryday: public cEvent {
protected:
    string info;
    Calendar data;
public:
    cEveryday();
    ~cEveryday() override;
    
    void setEvent() override;
    void changeEvent();
    void setData();
    void setTime();

    string getEvent() override;
    time_t getData(int position);
    time_t getTime(int position);
    
    bool emptyData();
    bool emptyTime();
    
    void remove();
};

#endif /* Everyday_hpp */
