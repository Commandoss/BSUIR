//
//  Header.h
//  Main
//
//  Created by Belousov Ilya on 16.04.21.
//

#ifndef Header_h
#define Header_h

#include <iostream>
#include <fcntl.h>
#include <thread>
#include <mutex>
#include <dlfcn.h>
#include <vector>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include <stdio.h>

const std::string readFolderPath = "/Users/ilya/Downloads/TextFile";
const std::string writePath = "/Users/ilya/Downloads/TextFile/Total.txt";


// flags
#define READ_FILE_COMPLETED 1
#define READ_FILE_PERFOMANCE 0

#define WRITE_FILE_COMPLETED 2

#define THREAD_END_EXECUTION -1
#define THREAD_END_COMPLETED -2

//sem
#define PERMS 0766
//
#define SEM_ID 111
#define SHM_ID 112

void sys_err(std::string msg, const int code) {
    std::cout << "Error code: " << code << std::endl;
    std::cout << "Error message: " << msg << std::endl;
    exit(code);
}

#endif /* Header_h */
