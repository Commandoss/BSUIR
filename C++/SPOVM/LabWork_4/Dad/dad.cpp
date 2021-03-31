//
//  dad.cpp
//  LabWork_4
//
//  Created by Belousov Ilya on 22.03.21.
//

#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <list>
#include <system_error>
#include <ctime>
#include <chrono>
#include <condition_variable>
//#include <curses.h>
#include "kbhit.h"

#define THREAD_RUN 1
#define THREAD_WAIT 0
#define THREAD_DEL -1
#define THREAD_END 2;


using namespace::std;

std::mutex mut;
std::condition_variable condition;

thread::id processed;
int ready = -1;

void threadID(const time_t tim) {
    unique_lock<mutex> uq(mut);  // сделать проверку
    while (true) {
        condition.wait(uq, []{ return processed == this_thread::get_id() && (ready == THREAD_RUN || ready == THREAD_DEL);});
        
        if (ready == THREAD_DEL) {
            ready = THREAD_END;
            condition.notify_all();
            cout << "The process id = " << this_thread::get_id() << " has ended.\n";
            break;
        }
        cout << "This thread id = " << this_thread::get_id() << " Created in " << ctime(&tim);
        
        this_thread::sleep_for(chrono::milliseconds(600));
        ready = THREAD_WAIT;
        condition.notify_all();
    }
    return;
}

int main(int argc, char *argv[]) {
    keyboard k;
    list<thread> threadList;
    
    std::cout << "\nMenu programm:" << std::endl;
    std::cout << "If you want to create new thread, please press '+'" << std::endl;
    std::cout << "If you want to delete last thread, please press '-'" << std::endl;
    std::cout << "If you want to quit, please press 'q'" << std::endl;
    std::cout << ">";
    
    while (true) {
        if (k.kbhit()) {
            switch (k.getch()) {
                case '+':
                    threadList.push_back(thread(threadID, time(NULL)));
                    continue;
//                    break;
                    
                case '-':
                    if (threadList.empty()) std::cout << "No active thread!" << std::endl;
                    else {
                        {
                            lock_guard<mutex> lq(mut);
                            processed = threadList.back().get_id();
                            ready = THREAD_DEL;
                            condition.notify_all();
                        }
                        unique_lock<mutex> uq(mut);
                        condition.wait(uq, []{ return ready == THREAD_END; });
                        threadList.back().join();
                        threadList.pop_back();
                        
                        std::cout << "Thread was removed" << std::endl;
                        std::cout << std::endl;
                        this_thread::sleep_for(chrono::milliseconds(600));
                        continue;
                    }
                    break;
                    
                case 'q':
                case 'Q':
                    if (threadList.empty()) cout << "No active thread!" << endl;
                    else {
                        for (auto &threadChild : threadList) { // запускаем по очереди
                            {
                                lock_guard<mutex> lq(mut);
                                processed = threadChild.get_id();
                                ready = THREAD_DEL;
                                condition.notify_all();
                            }
                            
                            unique_lock<mutex> uq(mut);
                            condition.wait(uq, []{ return ready == THREAD_END;});
                            threadChild.join();
                        }
                        
                        threadList.clear();
                        std::cout << "All thread delete!" << std::endl;
                    }
                    return 0;
            }
        } else if (!threadList.empty()) {
            
            for (auto &threadChild : threadList) {
                {
                    lock_guard<mutex> lq(mut);
                    processed = threadChild.get_id();
                    ready = THREAD_RUN;
                    condition.notify_all();
                }
                
                unique_lock<mutex> uq(mut); // ставим в ожидание процесс
                condition.wait(uq, []{ return ready == THREAD_WAIT; });
            }
            cout << "\n" << endl;
        }
    }

    return 0;
}

