//
//  main.cpp
//  LabWork_3
//
//  Created by Belousov Ilya on 16.03.21.
//

// По поводу 0644
//rwx oct    meaning
//--- ---    -------
//001 01   = execute
//010 02   = write
//011 03   = write & execute
//100 04   = read
//101 05   = read & execute
//110 06   = read & write
//111 07   = read & write & execute

//user,group,other == 644

#include <iostream>
#include <string>
#include "Header.h"

using  namespace::std;

int main(int argc, const char * argv[]) { // client
    int semid, shmid = 0;
    senum_t *sem;
    
    if ((semid = semget(SEM_ID, 1, PERMS | IPC_CREAT)) < 0) {
        sys_err("Client: Failed to get semaphore set ID.");
    }
    if ((shmid = shmget(SHM_ID, sizeof(MSG_SIZE), PERMS | IPC_CREAT)) < 0) {
        sys_err("Server: Memory for the segment was not allocated.\n");
    }
    if ((sem = (senum_t *) shmat(shmid, 0, 0)) == NULL) {
        sys_err("Client: Memory not connect.");
    }
    if (semctl(semid, 0, SETVAL, 0) < 0) {
        sys_err("Client: comand SETVAL not fulfilled");
    }
    sem->flag = MSG_EMPTY;
    
    cout << "\n\nSHMID = " << shmid << "\nSEMID = " << semid << endl;
    
    while (true) {
        if (sem->flag != MSG_EMPTY) {
            if (semctl(semid, 0, GETVAL, 0)) {
                continue;
            }
            if (semctl(semid, 0, SETVAL, 1) < 0) {
                sys_err("Client: comand SETVAL not fulfilled.");
            }
            if (sem->flag == MSG_STRING) {
                cout << "\nClient: The resulting string: ";
                printf("%s", sem->str);

            }
            if (sem->flag == MSG_END) {
                break;
            }
            sem->flag = MSG_EMPTY;
            semctl(semid, 0, SETVAL, 0);
        }
    }
    shmdt(sem);
    return 0;
}
