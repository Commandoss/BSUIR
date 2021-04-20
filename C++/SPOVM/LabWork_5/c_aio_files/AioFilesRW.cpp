//
//  AioFilesRW.cpp
//  AioFilesRW
//
//  Created by Belousov Ilya on 16.04.21.
//

#include "AioFilesRW.hpp"
#include <iostream>
#include <vector>
#include <fcntl.h>
#include <cstdio>
#include <unistd.h>
#include <aio.h>
#include <condition_variable>
#include <mutex>

//using namespace::async_read_write;

cAioFiles::cAioFiles() {
    descriptor = -1;
    offset = 0;
    numButes = 0;
    buffer.clear();
}

int cAioFiles::getDescriptor() {
    return descriptor;
}

off_t cAioFiles::getOffset() {
    return offset;
}

long cAioFiles::getNumButes() {
    return numButes;
}

std::string cAioFiles::getBuffer() {
    return buffer;
}

void cAioFiles::setBuffer(const std::string newBuffer) {
    buffer = newBuffer;
}

void cAioFiles::setOffset(const off_t newOffset) {
    offset = newOffset;
}

void cAioFiles::setDescriptor(const int newDescriptor) {
    descriptor = newDescriptor;
}

void cAioFiles::setNumButes(const long newNumButes) {
    numButes = newNumButes;
}

bool cAioFiles::findFile(std::string filePath, std::string readFolderPath) {
    if (fs::is_directory(fs::path(readFolderPath))) {
        aioErrors("This directory does not exist!", 404);
    }
    
    for (const auto & entry : fs::directory_iterator(readFolderPath)) {
        std::string filePath = entry.path();
        if (filePath.compare(filePath.size() - 4, 4, ".txt") == 0) {
            return true;
        }
    }
    return false;
}

bool cAioFiles::findFiles(std::vector<std::string> &filesPath, std::string readFolderPath) {
    if (!fs::is_directory(readFolderPath)) {
        aioErrors("This directory does not exist!", 404);
    }
    
    for (const auto & entry : fs::directory_iterator(readFolderPath)) {
        std::string Path = entry.path();
        if (Path.compare(Path.size() - 4, 4, ".txt") == 0 && Path.compare(writePath) != 0) {
            filesPath.push_back(Path);
        }
    }
    if (filesPath.empty()) return false;
    
    return true;
}

bool cAioFiles::createFile(const char *filePath) {
    descriptor = creat(filePath, PERMS);
    if (descriptor == -1) {
        std::cout << "Failed to create file on path: " << filePath << std::endl;
        return false;
    }
    closeFile();
    return true;
}

bool cAioFiles::aioRead(const char *filePath) {
    struct aiocb cb;
    
    openFile(filePath, O_RDONLY);
    numButes = (long)lseek(descriptor, 0, SEEK_END);
    char *readBuffer = new char [(int) getNumButes()];
    
    memset(&cb, 0, sizeof(aiocb));
    cb.aio_nbytes = (int) getNumButes();
    cb.aio_fildes = descriptor;
    cb.aio_offset = 0;
    cb.aio_buf = readBuffer;
    
    if (aio_read(&cb) == -1) {
        std::cout << "Unable to create request!" << std::endl;
        closeFile();
        return false;
    }
    
    while(aio_error(&cb) == EINPROGRESS);
    
    numButes = aio_return(&cb);
    if (numButes == -1) {
        return false;
    }
    
    buffer += readBuffer;
    delete [] readBuffer;
    closeFile();
    return true;
}

bool cAioFiles::aioWrite(const char *filePath) {
    std::unique_lock<std::mutex> uq(mut);
    while (true) {
        condition.wait(uq, [this]{ return threadFlag == READ_FILE_COMPLETED || threadFlag == THREAD_END_EXECUTION;});
        if (threadFlag == THREAD_END_EXECUTION) {
            threadFlag = THREAD_END_COMPLETED;
            condition.notify_one();
            break;
        }
        
        struct aiocb cb;
        openFile(filePath, O_WRONLY);
        
        memset(&cb, 0, sizeof(aiocb));
        cb.aio_nbytes = getNumButes();
        cb.aio_buf = (char*) getBuffer().c_str();
        cb.aio_fildes = getDescriptor();
        cb.aio_offset = getOffset();
        
        if (aio_write(&cb) == -1) {
            std::cout << "Unable to create request!" << std::endl;
            closeFile();
            return false;
        }
        
        while(aio_error(&cb) == EINPROGRESS);
        
        numButes = aio_return(&cb);
        if (numButes == -1) {
            return false;
        }
        offset += (off_t) numButes;
        buffer.clear();
        closeFile();
        
        threadFlag = WRITE_FILE_COMPLETED;
        condition.notify_one();
    }
    return true;
}

bool cAioFiles::openFile(const char *filePath, const int mode) {
    descriptor = open(filePath, mode);
    if (descriptor == -1) {
        std::cout << "Failed to open file on path: " << filePath << std::endl;
        return false;
    }
    return true;
}

bool cAioFiles::closeFile() {
    descriptor = close(descriptor);
    if (descriptor != 0) {
        std::cout << "Failed to close file. Invalid handle or file is already closed!" << std::endl;
        return false;
    }
    return true;
}

bool cAioFiles::closeFile(const int usrDescriptor) {
    if (close(usrDescriptor) != 0) {
        std::cout << "Failed to close file. Invalid handle or file is already closed!" << std::endl;
        return false;
    }
    return true;
}

bool cAioFiles::removeFile(const char *path) {
    if (remove(path) != 0) {
        std::cout << "The file was not deleted!" << std::endl;
        return false;
    }
    return true;
}

void cAioFiles::aioErrors(const char *msg, const int code) {
    std::cout << "Error: " << msg << std::endl;
    std::cout << "Code: " << msg << std::endl;
    exit(code);
}


void cAioFiles::nextFile() {
    buffer.clear();
    numButes = 0;
    descriptor = 0;
}
