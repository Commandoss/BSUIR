//
//  cString.cpp
//  lab 3
//
//  Created by Belousov Ilya on 9/21/20.
//  Copyright © 2020 Belousov Ilya. All rights reserved.
//

#include "String.h"
#include "function.h"

cString::cString() {
    size = 0;
    line = 0;
}

cString::cString(unsigned long value) : size(value) {
    line = new char [size + 1];
}

cString::cString(const char *ptr) : size(strlen(ptr)), line(new char [size + 1]) {
    strcpy(line, ptr);
}

cString::cString(const cString &cS) : size(strlen(cS.line)), line(new char[size + 1]) {
    strcpy(line, cS.line);
}

cString::~cString() {
    delete [] line;
}

cString cString::operator()(int pos1, int pos2) {
    if (pos1 > pos2) {
        int save = pos2;
        pos2 = pos1;
        pos1 = save;
    }

    int newLen = pos2 - pos1;
    cString newLine(newLen);
    newLine.size = newLen;

    for(int i = pos1, j = 0; i < pos2 && i < size; i++, j++) {
        newLine.line[j] = line[i];
    }
    return newLine;
}

cString cString::operator+(const cString &cS) {
    unsigned long newLen = size + cS.size;
    cString result(newLen);
    strcpy(result.line, line);
    strcat(result.line, cS.line);
    return result;
}

cString cString::operator+(int number) {
    char *ptr = new char [sizeof(int)];
    ptr = itoa(number, ptr, 10);
    unsigned long newLen = size + sizeof(number);
    char *newLine = new char [newLen + 1];
    strcpy(newLine, line);
    strcat(newLine, ptr);
    delete [] line;
    delete [] ptr;
    line = newLine;
    size = newLen;
    return *this;
}

cString cString::operator+(const string str) {
    unsigned long newLen = str.size() + size;
    cString newLine(newLen);
    strcpy(newLine.line, line);
    strcat(newLine.line, str.c_str());
    return newLine;
}

cString cString::operator+(const char *ptr) {
    unsigned long newLen = size + strlen(ptr);
    cString newLine(newLen);
    strcpy(newLine.line, line);
    strcat(newLine.line, ptr);
    return newLine;
}

cString operator+(const char *ptr, const cString &cS) {
    unsigned long newLen = cS.size + strlen(ptr);
    cString newLine(newLen);
    strcpy(newLine.line, ptr);
    strcat(newLine.line, cS.line);
    return newLine;
}

cString operator+(const string str, const cString &cS) {
    unsigned long newLen = str.size() + cS.size;
    cString newLine(newLen);
    strcpy(newLine.line, str.c_str());
    strcat(newLine.line, cS.line);
    return newLine;
}

cString operator+(const int number, const cString &cS) {
    char *ptr = new char [sizeof(int)];
    ptr = itoa(number, ptr, 10);
    unsigned long newLen = cS.size + sizeof(number);
    cString newLine(newLen);
    strcpy(newLine.line, ptr);
    strcat(newLine.line, cS.line);
    delete [] ptr;
    return newLine;
}

//---

cString cString::operator-(const cString &cS) {
    char *ptr;
    if ((ptr = strstr(line, cS.line)) == NULL)
        return cS;
    else {
        cString newLine(ptr);
        return newLine;
    }
}

char* cString::operator-(int number) {
    char *redefinition = new char [sizeof(number)];
    redefinition = itoa(number, redefinition, 10);
    
    char *newLine = strstr(line, redefinition);
    return newLine;
}

char* cString::operator-(const string str) {
    char *newLine;
    return newLine = strstr(line, str.c_str());;
}

char* cString::operator-(const char *ptr) {
    char *newLine;
    return newLine = strstr(line, ptr);;
}

char* operator-(char *ptr, const cString &cS) {
    char *newLine;
    return newLine = strstr(ptr, cS.line);
}

char* operator-(string str, const cString &cS) {
    char *newLine = new char [str.size() + 1];
    strcpy(newLine, str.c_str());
    return newLine = strstr(newLine, cS.line);
}

char* operator-(const int number, const cString &cS) {
    char *redefinition = new char [sizeof(number)];
    redefinition = itoa(number, redefinition, 10);
    char *newLine;
    return newLine = strstr(redefinition, cS.line);
}


//--

cString& cString::operator+=(const cString &cS) {
    unsigned long newLen = size + cS.size;
    char *newLine = new char [newLen + 1];
    strcpy(newLine, line);
    strcat(newLine, cS.line);
    delete [] line;
    line = newLine;
    size = newLen;
    return *this;
}

cString& cString::operator+=(const int number) {
    char *ptr = new char [sizeof(int)];
    ptr = itoa(number, ptr, 10);
    unsigned long newLen = size + sizeof(int);
    cString newLine(newLen);
    strcpy(newLine.line, line);
    strcat(newLine.line, ptr);
    delete [] ptr;
    return *this;
}

cString& cString::operator+=(const string str) {
    unsigned long newLen = str.size() + size;
    cString newLine(newLen);
    strcpy(newLine.line, line);
    strcat(newLine.line, str.c_str());
    delete [] line;
    line = newLine.line;
    return *this;
}

cString& cString::operator+=(const char *ptr) {
    unsigned long newLen = strlen(ptr) + size;
    cString newLine(newLen);
    strcpy(newLine.line, line);
    strcpy(newLine.line, ptr);
    delete [] line;
    line = newLine.line;
    return *this;
}

cString operator+=(const int number, cString &cS) {
    char *ptr = new char [sizeof(int)];
    ptr = itoa(number, ptr, 10);
    unsigned long newLen = cS.size + strlen(ptr);
    cString newLine(newLen);
    strcpy(newLine.line, ptr);
    strcat(newLine.line, cS.line);
    delete [] cS.line;
    delete [] ptr;
    cS.line = newLine.line;
    return cS;
}

cString operator+=(const string str, cString &cS) {
    unsigned long newLen = str.size() + cS.size;
    cString newLine(newLen);
    strcpy(newLine.line, str.c_str());
    strcat(newLine.line, cS.line);
    delete [] cS.line;
    cS.line = newLine.line;
    return cS;
}

cString operator+=(const char *ptr, cString &cS) {
    unsigned long newLen = strlen(ptr) + cS.size;
    cString newLine(newLen);
    strcpy(newLine.line, ptr);
    strcat(newLine.line, cS.line);
    delete [] cS.line;
    cS.line = newLine.line;
    return cS;
}

cString& cString::operator=(const cString &cS) {
    unsigned long newLen = cS.size;
    char *newLine = new char [newLen + 1];
    strcpy(newLine, cS.line);
    delete [] line;
    this -> line = newLine;
    size = newLen;
    return *this;
}

cString& cString::operator=(const int number) {
    char *ptr = new char [sizeof(int)];
    ptr = itoa(number, ptr, 10);
    delete [] line;
    line = ptr;
    size = strlen(ptr);
    return *this;
}

cString& cString::operator=(const string str) {
    char *ptr = new char [str.size() + 1];
    strcpy(ptr, str.c_str());
    delete [] line;
    line = ptr;
    size = str.size();
    return *this;
}

cString& cString::operator=(const char *ptr) {
    size = strlen(ptr);
    char *CopPtr = new char [size + 1];
    strcpy(CopPtr,ptr);
    delete [] line;
    line = CopPtr;
    return *this;
}

//---

bool cString::operator==(const cString &cS) {
    return size = cS.size && strcmp(line, cS.line) == 0; //сравнивает строку s1 со строкой s2 и возвращает результат типа int: 0 –если строки эквивалентны, >0 – если s1<s2,  <0  — если s1>s2 С учётом регистра
}

bool cString::operator==(const char *ptr) {
    return size = strlen(ptr) && strcmp(line, ptr) == 0;
}

bool cString::operator==(const string str) {
    return size = str.size() && strcmp(line, str.c_str()) == 0;
}

//---

bool cString::operator!=(const cString &cS) {
    return size != cS.size && strcmp(line, cS.line) != 0;
}

bool cString::operator!=(const char *ptr) {
    return size != strlen(ptr) && strcmp(line, ptr) != 0;
}

bool cString::operator!=(const string str) {
    return size != str.size() && strcmp(line, str.c_str()) != 0;
}

//---

bool cString::operator[](const char symbol) {
    return strchr(line, symbol) != 0;
}

//---

bool cString::operator>(const cString &cS) {
    return size > cS.size && strcmp(line, cS.line) > 0;
}

bool cString::operator>(const char *ptr) {
    return size > strlen(ptr) && strcmp(line, ptr) > 0;
}

bool cString::operator>(const string str) {
    return size > str.size() && strcmp(line, str.c_str()) > 0;
}

//---

bool cString::operator<(const cString &cS) {
    return size < cS.size && strcmp(line, cS.line) < 0;
}

bool cString::operator<(const char *ptr) {
    return size < strlen(ptr) && strcmp(line, ptr) < 0;
}

bool cString::operator<(const string str) {
    return size < str.size() && strcmp(line, str.c_str()) < 0;
}

//--

cString& cString::operator++() {
    char key[4] = {'H', 'Y', 'S', 'M'};
    char *output = line;
    
    for (int i = 0; i < strlen(line); i++) {
        output[i] = line[i] ^ key[i % (sizeof(key) / sizeof(char))];
    }
    line = output;
    
    return *this;
}

//---

cString& cString::operator--() {
    return ++(*this);;
}

//---


cString& cString::input(char *ptr) {
    delete [] line;
    size = strlen(ptr);
    char *newLine = new char [size + 1];
    strcpy(newLine, ptr);
    line = newLine;
    return *this;
}

ostream & cString::show(ostream & os) const {
    return os << "" << (line ? line : "") << "";
}

istream& operator>>(istream &in, cString &i) {
    string cop;
    getline(cin, cop);
    cString n(cop.c_str());
    i = n;
    return in;
}

//istream& operator>>(istream &in, cString &i) {
//    string cop;
//    strncpy(cop, cin, 80);
//    cString n(cop.c_str());
//    i = n;
//    return in;
//}

ostream& operator<<(ostream & os, const cString & s)
{
  return s.show(os);
}


size_t cString::getsize() {
    return this -> size;
}

// Перегрузка ввода вывода
