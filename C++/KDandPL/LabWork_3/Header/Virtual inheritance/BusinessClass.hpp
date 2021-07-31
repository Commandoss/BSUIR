//
//  BusinessClass.hpp
//  LabWork_5_Human
//
//  Created by Belousov Ilya on 10/14/20.
//

#ifndef BusinessClass_hpp
#define BusinessClass_hpp

#include "TouristClass.hpp"
#include "EntrepreneurClass.hpp"

class BusinessClass : public TourisClass, public EntrepreneurClass {
protected:
    vector<string> Adress;
public:
    explicit BusinessClass();
    explicit BusinessClass(string str);
    explicit BusinessClass(vector<string> Vstr);
    ~BusinessClass() override;
    
    void SettoAndAdress(string str);
    void SetAdress(int cellNum, string str);
    void SetVAdress(vector<string> Vstr);
    
    string getElemVAdress(int cellNum);
    vector<string> getVAdress();
    
    void Table() override;
    void menuObj() override;
    
    friend ostream& operator<<(ostream &os, BusinessClass &cB);
    friend istream& operator>>(istream &is, BusinessClass &cB);
    friend bool operator==(const BusinessClass &cB1, const BusinessClass &cB2);
};

#endif /* BusinessClass_hpp */
