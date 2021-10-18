//
//  Event.hpp
//  Diary
//
//  Created by Belousov Ilya on 11.12.20.
//

#ifndef Event_hpp
#define Event_hpp

#include "ExceptionInput.hpp"

#include "Calendar.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

enum menu {
    ChangeAllEvent = 1,
    ChangeEvent,
    ChangeType,
    ChangeData,
    ChangeTime,
};

enum TypeImport {
    Common = 1,
    Important,
    VeryImportant,
    Nothing,
};

class cEvent {
public:
    cEvent();
    virtual ~cEvent();
    
    virtual void setEvent() = 0;
    virtual string getEvent() = 0;
};

#endif /* Event_hpp */
