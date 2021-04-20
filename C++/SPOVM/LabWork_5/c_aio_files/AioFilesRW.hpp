//
//  AioFilesRW.hpp
//  AioFilesRW
//
//  Created by Belousov Ilya on 16.04.21.
//

#ifndef AioFilesRW_hpp
#define AioFilesRW_hpp

#include <string>
#include <filesystem>
#include "Header.h"

namespace fs = std::__fs::filesystem;

#define SIZE_READ_BUFFER 200

class cAioFiles {
private:
    int descriptor;
    off_t offset;
    long numButes;
    std::string buffer;
    
public:
    cAioFiles();
    
    bool findFile(std::string filePath, std::string readFolderPath);
    bool findFiles(std::vector<std::string> &filesPath, std::string readFolderPath);
    
    bool createFile(const char *filePath);
    bool openFile(const char *filePath, const int mode);
    
    int getDescriptor();
    off_t getOffset();
    long getNumButes();
    std::string getBuffer();
    
    void setDescriptor(const int newDescriptor);
    void setOffset(const off_t newOffset);
    void setNumButes(const long newNumButes);
    void setBuffer(const std::string newBuffer);
    
    bool aioRead(const char *filePath);
    bool aioWrite(const char *filePath);
    
    bool closeFile();
    bool closeFile(const int usrDescriptor);
    
    bool removeFile(const char *path);
    
    void aioErrors(const char *msg, const int code);
    
    void nextFile();
    
    std::mutex mut;
    std::condition_variable condition;
    
    int threadFlag;
};

#endif /* AioFilesRW_hpp */


// 1297437786
// 1297437786
