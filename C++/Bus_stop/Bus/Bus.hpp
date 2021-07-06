//
//  Bus.hpp
//  Bus_Stop
//
//  Created by Belousov Ilya on 19.06.21.
//

#ifndef Bus_hpp
#define Bus_hpp

#include <string>
#include "cTime.hpp"
#include <cmath>

using namespace::std;

class bus {
private:
    cTime departure;
    cTime arrival;
    string route;
    
public:
    bus();
    
    void setRoute(string line);
    void setDeparture(string line);
    void setArrival(string line);
    bool checkTime();
    
    string getRoute();
    cTime getDeparture();
    cTime getArrival();
    
//    friend ostream& operator<<(ostream &os, bus &cb);
    void printBus();
        
};

#endif /* Bus_hpp */
