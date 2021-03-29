//
//  Header.h
//  LabWork_3
//
//  Created by Belousov Ilya on 18.03.21.
//

#ifndef Header_h
#define Header_h

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>


#define SEM_ID 111
#define SHM_ID 112


#define MSG_EMPTY 0
#define MSG_STRING 1
#define MSG_END 2
#define MSG_SIZE 255

#define PERMS 0777

typedef struct {
    int flag;
    char str[MSG_SIZE];

    struct semid_ds * buf;
    unsigned short * array;
    struct seminfo * __buf;
    struct sembuf sop;
    union semun *sem1;
} senum_t;

void sys_err (std::string msg) {
    std::cout << msg << std::endl;
    exit(EXIT_FAILURE);
}


#endif /* Header_h */
