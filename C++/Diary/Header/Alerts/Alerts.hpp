//
//  Alerts.hpp
//  Diary
//
//  Created by Belousov Ilya on 13.12.20.
//

#ifndef Alerts_hpp
#define Alerts_hpp

#include <iostream>
#include <ctime>

#include "Calendar.hpp"
#include "ImportEveryday.hpp"
#include "ImportWork.hpp"

#include "ExceptionInput.hpp"

using namespace std;

class cAlerts {
private:
    Calendar Current_Data;
public:
    cAlerts();
    ~cAlerts();
    
    bool checkEvents(cImportWork &data);
    bool checkEvents(cImportEveryday &data);
};

#endif /* Alerts_hpp */
