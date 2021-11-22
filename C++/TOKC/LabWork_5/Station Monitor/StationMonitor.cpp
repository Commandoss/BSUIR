//
//  StationMonitor.cpp
//  main
//
//  Created by Belousov Ilya on 16.11.21.
//

#include "StationMonitor.hpp"

StationMonitor::StationMonitor() {
}

StationMonitor::~StationMonitor() {
    stop();
}

bool StationMonitor::start(const std::string &adress) {
//    create_port();
//    сompound(adress);
//    create_marker();
//    add_to_queue(adress, "sdfsdfsdf");
    return true;
}

void StationMonitor::stop() {
    close_port();
}

void StationMonitor::create_marker() {
    Marking M;
    M.set_access_control(PRIORITY_BITS_SIMPLE, TOKEN_BIT_MARKER);
    M.set_frame_status(FRAME_COPIED_OFF);
    M.start();

    this->marker = M;
    THREAD_SET_FLAG_RUN(this->mutWrite, this->condition, this->fwrite);
}

void StationMonitor::checkRing() {
//    std::unique_lock<std::mutex> uq(this->mut);
//    while(true) {
//        condition.wait(uq, [this] {
//            return this->thFlag == THREAD_RUN
//                || this->thFlag == THREAD_STOP;
//        });
//        if (this->thFlag == THREAD_STOP)
//            return;
//
//        this->buffer << read_port(1023);
//
//        if(!toMarker())
//            continue;
//
//
//    }
}

