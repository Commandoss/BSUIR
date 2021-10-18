//
//  Work.hpp
//  Diary
//
//  Created by Belousov Ilya on 11.12.20.
//

#ifndef Work_hpp
#define Work_hpp

#include "Event.hpp"

class cWork: public cEvent {
protected:
    string info;
    Calendar data;
public:
    cWork();
    ~cWork() override;
    
    void setEvent() override;
    void changeEvent();
    cWork& setData();
    
    string getEvent() override;
    time_t getData(int position);
    
    void remove();
};

#endif /* Work_hpp */
