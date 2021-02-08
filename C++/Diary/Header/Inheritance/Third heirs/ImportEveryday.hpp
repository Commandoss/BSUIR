//
//  ImportEveryday.hpp
//  Diary
//
//  Created by Belousov Ilya on 11.12.20.
//

#ifndef ImportEveryday_hpp
#define ImportEveryday_hpp

#include "Everyday.hpp"

class cImportEveryday: public cEveryday {
protected:
    string type;
public:
    cImportEveryday();
    ~cImportEveryday() override;
    
    void changeType();
    string getTypeEvent();
    
    void menuObj();
    
    void printEvent();
    
    friend ostream& operator<<(ostream &os, cImportEveryday &cIW);
    friend istream& operator>>(istream &is, cImportEveryday &cIW);
};

#endif /* ImportEveryday_hpp */
