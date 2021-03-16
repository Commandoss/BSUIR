//
//  child.cpp
//  LabWork_1
//
//  Created by Belousov Ilya on 3.03.21.
//

#include <iostream>
#include <curses.h>

using namespace std;

int main(int argc, const char * argv[]) {
    initscr();
    printw("Parent's time:                     Child's time: \n");
    refresh();

    time_t now;
    for (int i = 0; i < 15; i++) {
        now = time(0);
        now += 86400;
        printw("                            %s", ctime(&now));
        refresh();
        napms(500);
    }

    getch();
    return 0;
}
