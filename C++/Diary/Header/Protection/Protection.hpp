//
//  Protection.hpp
//  Diary
//
//  Created by Belousov Ilya on 13.12.20.
//

#ifndef Protection_hpp
#define Protection_hpp

#include <iostream>
#include <string>

using namespace std;

class cProtection {
private:
    string key = {'X', '1', '2', 'j', 'n', 'P'};
    string getKey();
public:
    cProtection();
    ~cProtection();
    
    void encryptStr(string &line);
    void decryptStr(string &line);
};

#endif /* Protection_hpp */
