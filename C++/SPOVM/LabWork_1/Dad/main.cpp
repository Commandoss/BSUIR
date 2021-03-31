//
//  dad.cpp
//  DOTCHER
//
//  Created by Belousov Ilya on 3.03.21.
//

#include <iostream>
#include <curses.h>

#include <sys/wait.h>
#include <unistd.h>

void printTime(){
    initscr();

    time_t now;
    for (int i = 0; i < 15; i++) {
        now = time(0);
        addstr(ctime(&now));
        refresh();
        napms(500);
    }
    
}


int main(int argc, const char * argv[]) {
    initscr();
    pid_t pid;
    int counter = 0;
    while (counter != 10) {
        pid = fork();
        if (pid == -1) {
            printw("\nError terminal not open.\n");
            return -1;
        }
        
        if (pid == 0){
            execv("/Users/ilya/Library/Developer/Xcode/DerivedData/LabWork_1-cwtdviqyigcoitcqabssgvdwqods/Build/Products/Debug/Child", NULL);
        } else{
            printTime();
            
            int status;
            waitpid(pid, &status, 0);
            endwin();
            return 0;
        }
        counter++;
    }
}
