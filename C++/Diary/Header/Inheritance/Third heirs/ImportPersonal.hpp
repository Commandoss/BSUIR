//
//  ImportPersonal.hpp
//  Diary
//
//  Created by Belousov Ilya on 11.12.20.
//

#ifndef ImportPersonal_hpp
#define ImportPersonal_hpp

#include "Personal.hpp"

class cImportPersonal: public cPersonal {
protected:
    string type;
public:
    cImportPersonal();
    ~cImportPersonal() override;
    
    void changeType();
    string getTypeEvent();
    
    void menuObj();
    
    void printEvent();
    
    friend ostream& operator<<(ostream &os, cImportPersonal &cIP);
    friend istream& operator>>(istream &is, cImportPersonal &cIP);
};

#endif /* ImportPersonal_hpp */
