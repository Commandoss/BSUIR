//
//  TouristClass.hpp
//  Lab5
//
//  Created by Belousov Ilya on 10/9/20.
//

#ifndef TouristClass_hpp
#define TouristClass_hpp

#include "HumanClass.hpp"

struct History {
    vector<int> DayVis;
    string Country;
    string TargetVis;
};

class TourisClass : virtual public HumanClass {
protected:
    string PassportID;
    vector<struct History> VStrct;
public:
    explicit TourisClass();
    explicit TourisClass(string PassID, vector<struct History> VecHis);
    explicit TourisClass(string PassID, string country, string Target, vector<int> data);
    ~TourisClass() override;
    
    string getPassportID();
    string GetCountry(const int cellNum);
    string getTargetVis(const int cellNum);
    vector<int> getVDayVisit(const int cellNum);
    struct History getHisElem(const int cellNum);
    int getElemVDayVisit(const int cellNum_1, const int cellNum_2);
    vector<struct History> getVstr();
    
    void setPassportID(string PassID);
    void setElemVDayVisit(struct History H);
    void setVStrct(vector<struct History> VecHis);
    void setVStrct(vector<struct History> &VecHis, int counter);
    void setCountry(const int cellNum, const string str);
    void setTargetVis(const int cellNum, const string str);
    void setToEndVDayVisit(const int cellNum, const int value);
    
    void Table() override;
    void menuObj() override;
    
    friend ostream& operator<<(ostream &os, TourisClass &cT);
    friend istream& operator>>(istream &in, TourisClass &cT);
    friend bool operator==(const TourisClass &cT1, const TourisClass &CT);
};

#endif /* TouristClass_hpp */
