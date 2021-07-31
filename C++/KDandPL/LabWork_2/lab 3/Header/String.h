//
//  Stringr.h
//  lab 3
//
//  Created by Belousov Ilya on 9/11/20.
//  Copyright © 2020 Belousov Ilya. All rights reserved.
//

#ifndef String_h
#define String_h

#include <iostream>
#include <string.h>
#include <cstring>
#include <limits>

using namespace std;

class cString {
private:
    size_t size;
    char *line;
    
public:
    explicit cString();
    explicit cString(unsigned long value);
    explicit cString(const char *ptr);
    cString(const cString &cS);
    ~cString();
    
    cString operator+(const cString &cS);
    cString operator+(const int number);
    cString operator+(const string str);
    cString operator+(const char *ptr);
    friend cString operator+(const int number, const cString &cS);
    friend cString operator+(const string str, const cString &cS);
    friend cString operator+(const char *ptr, const cString &cS);
    
    cString operator-(const cString &cS);
    char* operator-(const int number);
    char* operator-(const string str);
    char* operator-(const char *ptr);
    friend char* operator-(int number, const cString &cS);
    friend char* operator-(string str, const cString &cS);
    friend char* operator-(char *ptr, const cString &cS);
    
    cString& operator+=(const cString &cS);
    cString& operator+=(const int number);
    cString& operator+=(const string str);
    cString& operator+=(const char *ptr);
    friend cString operator+=(const int number, cString &cS);
    friend cString operator+=(const string str, cString &cS);
    friend cString operator+=(const char *ptr, cString &cS);
    
    cString& operator=(const cString &cS); 
    cString& operator=(const int number);
    cString& operator=(const string str);
    cString& operator=(const char *ptr);
    
    bool operator==(const cString &cS);
    bool operator==(const char *ptr);
    bool operator==(string str);
    
    bool operator!=(const cString &cS);
    bool operator!=(const char *ptr);
    bool operator!=(string str);
    
    
    bool operator[](const char symbol);
    bool operator[](const string symbol);
    
    bool operator>(const cString &cS);
    bool operator>(const char *ptr);
    bool operator>(const string str);
    
    bool operator<(const cString &cS);
    bool operator<(const char *ptr);
    bool operator<(const string str);
    
    cString& operator++();
    cString& operator--();
    
    cString operator()(int pos1, int pos2);
    
    ostream& show(ostream &os) const;
    
    friend ostream& operator<<(ostream &os, const cString &s);
    friend istream& operator>>(istream &in, cString &i); // нужен второй ввод по 80 символов (с продолжением)
    
    cString& input(char *ptr);
    
    size_t getsize();
};

#endif /* String_h */
