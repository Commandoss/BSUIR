//
//  TextFile.hpp
//  Diary
//
//  Created by Belousov Ilya on 11.12.20.
//

#ifndef TextFile_hpp
#define TextFile_hpp

#include "ExceptionInput.hpp"
#include "List.hpp"

#include "Protection.hpp"

#include <string>
#include <fstream>
#include <fcntl.h>

using namespace std;

class File {
private:
    fstream file;
//    string fileName;
public:
    File();
    ~File();
    
    void open(string name);
    bool isOpened();
    bool isEof();
    
    void close();
    
    void removeFile(string name);
    
    template<class Type>
    void read(Type &vault);
    
    template <class Type>
    void write(Type vault);
    
    long getPointerPos();
    void setPointerPos(long position);
    
    template <class Type>
    void writeListFile(OwnIterator<Type> ite, OwnIterator<Type> endite, string name);
    
    template <class Type>
    void readListFile(cList<Type> &node, string name);
    
    void code(string name);
    void decode(string name);
};


template <class Type>
void File::read(Type &vault) {
    if (isOpened()) {
        file >> vault;
    }
    else {
        cout << "File not open" << endl;
    }
}

template <class Type>
void File::write(Type vault) {
    if (file.is_open()) {
        file << vault;
    }
    else cout << "File not open" << endl;
}

template <class Type>
void File::writeListFile(OwnIterator<Type> ite, OwnIterator<Type> endite, string name) {
    removeFile(name);
    open(name);
    for(; ite != endite; ++ite) {
        write(*ite);
    }
    close();
}

template <class Type>
void File::readListFile(cList<Type> &node, string name) {
    open(name);
    if (!isOpened()) return;
    while (!isEof()) {
        Type Obj;
        read(Obj);
        node.addNode(Obj);
        if (isEof()) break;
    }
    close();
}

#endif /* TextFile_hpp */
