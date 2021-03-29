//
//  main.cpp
//  server
//
//  Created by Belousov Ilya on 17.03.21.
//

#include <string>
#include <iostream>
#include <stdio.h>

#include "Header.h"

using namespace::std; // Server...

int main(int argc, char * argv[]) {
    char line[MSG_SIZE];
    int semid, shmid = 0;
    senum_t *sem = nullptr;
    
    if ((semid = semget(SEM_ID, 1, PERMS | IPC_CREAT)) < 0) {
        sys_err("Server: Failed to get semaphore set ID.");
    }
    if ((shmid = shmget(SHM_ID, sizeof(MSG_SIZE), PERMS | IPC_CREAT)) < 0) {
        sys_err("Server: Memory for the segment was not allocated.\n");
    }
    if ((sem = (senum_t *) shmat(shmid, 0, 0)) == NULL) {
        sys_err("Client: Memory not connect.");
    }
    
    cout << "\n\nSHMID = " << shmid << "\nSEMID = " << semid << endl;
    
    while (true) {
        cout << "\n\nServer...." << endl;
        cout << "Enter line: ";
        cin.getline((line), MSG_SIZE);
        
        while (semctl(semid, 0, GETVAL, 0) || sem->flag != MSG_EMPTY);
        semctl(semid, 0, SETVAL, 1);
        
        if (strlen(line) != 0) {
            sem->flag = MSG_STRING;
            strcpy(sem->str, line);
        } else {
            sem->flag = MSG_END;
            cout << "Incorrect entry for successful transmission, enter at least one character." << endl;
            if (semctl(semid, 0, SETVAL, 0) < 0) { // ???
                sys_err("Server: comand SETVAL not fulfilled.");
            }
            break;
        }
        if (semctl(semid, 0, SETVAL, 0) < 0) { // ???
            sys_err("Server: comand SETVAL not fulfilled.");
        }
    }
    
    // удаление семафора
    if (semctl(semid, 0, IPC_RMID, 0) < 0) {
        sys_err("Server: Semaphore not delete.");
    }
    shmdt(sem);
    // удаление сегмента
    if (shmctl(shmid, IPC_RMID, 0) < 0) {
        sys_err("Server: Segment not delete.");
    }
    return 0;
}


