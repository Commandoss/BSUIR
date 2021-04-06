//
//  MyExcep_Input.hpp
//  LabWork_6_Exception
//
//  Created by Belousov Ilya on 11/8/20.
//

#ifndef MyExcep_Input_hpp
#define MyExcep_Input_hpp

#include "MyException.hpp"

class MyExcep_Input: public MyException {
    
public:
    explicit MyExcep_Input();
    explicit MyExcep_Input(std::string msg, int date);
    ~MyExcep_Input();
    
    static int check_int(const int max, const int min);
    static std::string check_string(int length);
    static double check_double(const int max, const int min);
    static std::string check_Adress(const int length);
    static std::string check_Pass();
    static std::string check_Lic();
    static std::string check_Target();
    
    std::string What() override;
    int gateDate() override;
};


#endif /* MyExcep_Input_hpp */
