//
//  Entrepreneur.hpp
//  Lab5
//
//  Created by Belousov Ilya on 10/9/20.
//

#ifndef EntrepreneurClass_hpp
#define EntrepreneurClass_hpp

#include "HumanClass.hpp"

struct Payment {
    vector<int> DayPay;
    double Sum;
};

class EntrepreneurClass : virtual public HumanClass {
protected:
    string Licence;
    string AdressReg;
    vector<struct Payment> Pay;
public:
    explicit EntrepreneurClass();
    explicit EntrepreneurClass(string licence, string adressReg, vector<struct Payment> P);
    ~EntrepreneurClass() override;
    
    string getLicence();
    string getAdressReg();
    vector<struct Payment> getVPayment();
    int getDayPay(const int cellNum_1, const int cellNum_2);
    vector<int> getDayPay(const int cellNum);
    double getSum(const int cellNum);
    struct Payment getCellVPay(const int cell);
    
    void setLicence(string licence);
    void setAdressReg(string adressReg);
    void setCellVPay(struct Payment P);
    void setPayment(vector<struct Payment> P);
    void setPayment(vector<struct Payment> &P, int counter);
    void setVDayPay(int cellNum, vector<int> NewVDayPay);
    void setSum(int cellNum, double value);
    
    void Table() override;
    void menuObj() override;
    
    friend ostream& operator<<(ostream &os, EntrepreneurClass &cE);
    friend istream& operator>>(istream &is, EntrepreneurClass &cE);
    friend bool operator==(const EntrepreneurClass &cE1, const EntrepreneurClass &cE2);
};

#endif /* Entrepreneur_hpp */
