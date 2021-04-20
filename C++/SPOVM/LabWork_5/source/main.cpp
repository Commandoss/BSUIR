//
//  main.cpp
//  Main
//
//  Created by Belousov Ilya on 16.04.21.
//

#include <iostream>
#include "AioFilesRW.hpp"
#include "Header.h"

using namespace::std;

int main(int argc, char *argv[]) {
    void *soHandle = dlopen("/Users/ilya/Library/Developer/Xcode/DerivedData/LabWork_5-gcubiwvnmkgvfuflrgtrxeexjxvc/Build/Products/Debug/libAioFilesRW.dylib", RTLD_GLOBAL);

    if (soHandle != NULL) {
        cAioFiles *aio = new cAioFiles;
        thread writer(&cAioFiles::aioWrite, aio, writePath.c_str());
        std::vector<std::string> vPath;

        aio->removeFile(writePath.c_str());
        aio->createFile(writePath.c_str());
        aio->findFiles(vPath, readFolderPath);

        for (const auto &file : vPath) {
            if (aio->aioRead(file.c_str())) {
                {
                    lock_guard<mutex> lq(aio->mut);
                    aio->threadFlag = READ_FILE_COMPLETED;
                    aio->condition.notify_one();
                }
                
                unique_lock<mutex> uq(aio->mut);
                aio->condition.wait(uq, [&aio]{return aio->threadFlag == WRITE_FILE_COMPLETED;});
            } else {
                {
                    lock_guard<mutex> lq(aio->mut);
                    aio->threadFlag = THREAD_END_EXECUTION;
                    aio->condition.notify_one();
                }
                writer.join();
                dlclose(soHandle);
            }
        }
        {
            unique_lock<mutex> uq(aio->mut);
            aio->threadFlag = THREAD_END_EXECUTION;
            aio->condition.notify_one();
        }
        writer.join();
        if (dlclose(soHandle) != 0) {
            sys_err("Failed to delete the called space", 3);
        }
    }
    else {
        sys_err("Can't open dynamic library!", 3);
    }
    return 0;
}
