//
//  HumanClass.hpp
//  Lab5
//
//  Created by Belousov Ilya on 10/9/20.
//

#ifndef HumanClass_hpp
#define HumanClass_hpp

#include "MyException.hpp"
#include "MyExcep_Input.hpp"

#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class HumanClass
{
protected:
    string Name;
    string LastName;
    vector<int> DayBirth;
public:
    explicit HumanClass();
    explicit HumanClass(string name, string lastname, vector<int>birth);
    virtual ~HumanClass();
    
    string getName();
    string getLastName();
    vector<int> getVDayBirth();
    
    unsigned int getElemDayBirth(unsigned const int cellNum);
    
    void SetData(vector<int> &data);
    
    int getBirthDay();
    int getBirthMonth();
    int getBirthYear();
        
    void setNewName(string name);
    void setNewLastName(string lastname);
    void setToEndVDayBirth(int num);
    void setElemDayBirth(int cellNum, int num);
    void setDayBitrh(vector<int> birth);
    
    virtual void Table();
    virtual void menuObj();
    
    friend ostream& operator<<(ostream &os, HumanClass &cH);
    friend istream& operator>>(istream &in, HumanClass &cH);
};

#endif /* HumanClass_hpp */
