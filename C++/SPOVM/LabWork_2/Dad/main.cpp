//
//  main.cpp
//  Dad
//
//  Created by Belousov Ilya on 15.03.21.
//

#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> // нужно для работы форка
#include <signal.h>
#include <list>

int main(int argc, char ** argv) {
    pid_t pid;
    std::list<pid_t> pidList;

    int reciver = 0;

    sigset_t waitSet;   // создать набор сигналов
    sigemptyset(&waitSet); // установить набор сигналов пустым
    sigaddset(&waitSet, SIGUSR2);
    sigprocmask(SIG_BLOCK, &waitSet, NULL);

    char symbol;
    while (true) {

        std::cout << "Menu programm:" << std::endl;
        std::cout << "If you want to create new process, please press '+'" << std::endl;
        std::cout << "If you want to delete last process, please press '-'" << std::endl;
        std::cout << "If you want to quit, please press 'q'" << std::endl;
        std::cout << ">";

        std::cin.get(symbol);

        switch (symbol) {
            case '+':
                pid = fork();
                switch (pid) {
                    case -1:
                        std::cout << "Error creating child process!\n" << std::endl;
                        exit(EXIT_FAILURE);

                    case 0:
                        execv("/Users/ilya/Library/Developer/Xcode/DerivedData/LabWork_2-croxhxorsrigwrgjdhgmjfjeacio/Build/Products/Debug/Main", NULL);
                        std::cout << "Error not find child process!\n" << std::endl;
                        exit(127);

                    default:
                        pidList.push_back(pid);
                        sleep(1);
                        break;
                }
                break;

            case '-':
                if (pidList.empty()) std::cout << "No active processes!" << std::endl;
                else {
                    kill(pidList.back(), SIGKILL);
                    pidList.pop_back();
                    sleep(1);
                    std::cout << "Process was removed" << std::endl;
                    std::cout << std::endl;
                }
                break;

            case 'q':
            case 'Q':
                if (pidList.empty()) std::cout << "No active processes!" << std::endl;
                else {
                    for (auto &childPid : pidList) {
                        kill(childPid, SIGKILL);
                    }
                    pidList.clear();
                    std::cout << "All processes delete!" << std::endl;
                }
                return 0;

            default:
                continue;
        }
        std::cin.ignore();

//        std::cout << "\n\n" << std::endl;

        for (auto &childPid : pidList) {
            kill(childPid, SIGUSR1);
            sigwait(&waitSet, &reciver);
        }
        sleep(1);
        std::cout << "\n" << std::endl;
    }
}
