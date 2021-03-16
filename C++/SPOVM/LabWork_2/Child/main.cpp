//
//  main.cpp
//  Main
//
//  Created by Belousov Ilya on 9.03.21.


#include <iostream>
#include <cstdio>
#include <csignal>
#include <cstring>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sstream>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

int main(int argc, char ** argv)
{
    int reciver = 0;

    std::string message = "My 21 fingers are long: ";
    std::string pidStr = patch::to_string((int)getpid());
    message += pidStr;

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGKILL);
    sigprocmask(SIG_BLOCK, &set, NULL);

    while (true)
    {
        sigwait(&set, &reciver);

        std::cout << message.c_str() << std::endl;;

        kill(getppid(), SIGUSR2);
    }
    return 0;
}
