//
//  cBusCompany.hpp
//  Bus_Stop
//
//  Created by Belousov Ilya on 19.06.21.
//

#ifndef cBusCompany_hpp
#define cBusCompany_hpp

#include "Bus.hpp"
#include "cFile.hpp"
#include <iostream>
#include <algorithm>

class cBusCompany {
protected:
    string name;
    vector<bus> timetable;
    
public:
    cBusCompany();
    cBusCompany(string name);
    cBusCompany(const cBusCompany &copyCBC);
    ~cBusCompany();
    
    bool timetableUpdate();
    bool timetableSave();
    void timetableSort();
    
    void setName(string newName);
    void setBus(bus addBus);
    
    bus findBus(bus &userBus);
    
    void addNewBus();
    void deleteBus();
    string getName();
    
    friend ostream& operator<<(ostream &os, cBusCompany &cBC);
    friend ofstream& operator<<(ofstream &of, cBusCompany &cBC);
    friend istream& operator>>(istream &in, cBusCompany &cBC);
    
};

#endif /* cBusCompany_hpp */
