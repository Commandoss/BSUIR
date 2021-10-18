//
//  TextFile.cpp
//  Diary
//
//  Created by Belousov Ilya on 11.12.20.
//

#include "TextFile.hpp"

File::File() {
}

File::~File() {
//    fileName.clear();
    close();
}

void File::open(string name) {
    file.open(name, fstream::in | fstream::out);
    if (!isOpened()) file.open(name, fstream::app);
}

bool File::isOpened() {
    return file.is_open();
}

bool File::isEof() {
    if (file.peek() == EOF) {
        return true;
    }
    return false;
}

void File::close() {
    file.close();
}

long File::getPointerPos() {
    return file.tellg();
}

void File::setPointerPos(long position) {
    file.seekg(position, ios_base::beg);
}

void File::code(string name) {
    cProtection cP;
    string line;
    long current, back;
    open(name);
    while (!isEof()) {
        back = getPointerPos();
        
        getline(file, line);
        cP.encryptStr(line);
        
        current = getPointerPos();
        setPointerPos(back);
        write(line);
        setPointerPos(current);
    }
    close();
}

void File::decode(string name) {
    cProtection cP;
    string line;
    long current, back;
    open(name);
    while (!isEof()) {
        back = getPointerPos();
        
        getline(file, line);
        cP.encryptStr(line);
        
        current = getPointerPos();
        setPointerPos(back);
        write(line);
        setPointerPos(current);
    }
    close();
}

void File::removeFile(string name) {
    remove(name.c_str());
}
