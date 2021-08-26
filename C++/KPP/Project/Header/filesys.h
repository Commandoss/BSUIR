//
//  filesys.h
//  LLL
//
//  Created by Belousov Ilya on 15.08.21.
//

#ifndef filesys_h
#define filesys_h

#include <filesystem>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace::std;
namespace fs = std::__fs::filesystem;

bool check_path(const string path) {
    if (fs::is_regular_file(path))
        return true;
    return false;
}

fstream create_file(const string name) {
    fstream fion;
    fion.open(name, ios_base::in | ios_base::out | ios_base::app);
    
    if (!fion.is_open()) {
        cout << "Unable to create file" << name << endl;
        return fion;
    }
    return fion;
}

bool remove_file(const string path) {
    if (remove(path.c_str())) {
        cout << "Failed to remove file: " << endl;
        return false;
    }
    return true;
}

bool rename_file(const string oldName, const string newName) {
    if (rename(oldName.c_str(), newName.c_str())) {
        cout << "Failed to rename file: " << oldName << endl;
        return false;
    }
    return true;
}

fstream open_file(const string path) {
    fstream fion;
    fion.open(path, ios_base::in | ios_base::out);
    
    if (!fion.is_open())
        cout << "File along the path: " << path
            << " cannot be opened!" << endl;
    
    return fion;
}

bool close_file(fstream &fion) {
    fion.close();
    if (!fion.is_open()) return false;
    return true;
}

string read_file(fstream &fRead) {
    string buffer;
    char symbol;
    while (fRead.get(symbol) && !fRead.eof()) {
        if (symbol == ' ')
            return buffer;
        
        buffer.push_back(symbol);
    }
    
    return buffer;
}

void write_file(fstream &fWrite, const string value) {
    fWrite << value;
}

#endif /* filesys_h */
