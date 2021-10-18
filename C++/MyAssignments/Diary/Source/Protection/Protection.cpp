//
//  Protection.cpp
//  Diary
//
//  Created by Belousov Ilya on 13.12.20.
//

#include "Protection.hpp"

cProtection::cProtection() {
}

cProtection::~cProtection() {
}

string cProtection::getKey() {
    return key;
}

void cProtection::encryptStr(string &line) {
    string code = getKey();
    string output = line;
    
    for (int i = 0; i < output.size(); i++) {
        output[i] = line[i] ^ key[i % (sizeof(key) / sizeof(string))];
    }
    line = output;
}

void cProtection::decryptStr(string &line) {
    string code = getKey();
    string output = line;
    
    for (int i = 0; i < output.size(); i++) {
        output[i] = line[i] ^ key[i % (sizeof(key) / sizeof(string))];
    }
    line = output;
}


