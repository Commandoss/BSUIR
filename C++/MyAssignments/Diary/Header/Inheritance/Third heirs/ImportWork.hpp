//
//  ImportWork.hpp
//  Diary
//
//  Created by Belousov Ilya on 11.12.20.
//

#ifndef ImportWork_hpp
#define ImportWork_hpp

#include "Work.hpp"

class cImportWork: public cWork {
protected:
    string type;
public:
    cImportWork();
    cImportWork(cImportWork &cop);
    ~cImportWork() override;
    
    void changeType();
    string getTypeEvent();
    
    void menuObj();
    
    void printEvent();
    
    friend ostream& operator<<(ostream &os, cImportWork &cIW);
    friend istream& operator>>(istream &in, cImportWork &cIW);
};


#endif /* ImportWork_hpp */
