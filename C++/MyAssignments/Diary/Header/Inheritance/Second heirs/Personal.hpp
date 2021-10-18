//
//  Personal.hpp
//  Diary
//
//  Created by Belousov Ilya on 11.12.20.
//

#ifndef Personal_hpp
#define Personal_hpp

#include "Event.hpp"

class cPersonal: public cEvent {
protected:
    string info;
public:
    cPersonal();
    ~cPersonal() override;
    
    void setEvent() override;
    string getEvent() override;
    
    void remove();
};

#endif /* Personal_hpp */
