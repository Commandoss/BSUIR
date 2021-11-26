//
//  StationMonitor.cpp
//  main
//
//  Created by Belousov Ilya on 16.11.21.
//

#include "StationMonitor.hpp"

StationMonitor::StationMonitor() {
    this->id = 0;
}

StationMonitor::~StationMonitor() {
    stop();
}

void StationMonitor::stop() {
    if (is_open()) {
        Status S(disconnection);
        send_status(S);
        close_port();
    }
}

void StationMonitor::create_marker() {
    this->id += 1;
    
    Marking M;
    M.set_priority(0);
    M.set_reservation(this->priority);
    M.set_token(TOKEN_BIT_MARKER);
    M.set_frame_status(FRAME_COPIED_OFF);
    M.set_id(this->id);
    M.set_regime(this->regime);
    M.start();

    this->marker = M;
}

void StationMonitor::send_marker() {
    create_marker();

    std::stringstream ss;
    boost::archive::text_oarchive wr(ss);
    wr & this->marker;
}

void StationMonitor::check_marker() {
    if (this->marker.get_id() != this->id)
        send_marker();
    if (this->priority == 0 && this->priority)
    if (regime != this->marker.get_token())
        send_marker();
}

void StationMonitor::thread_start() {
    this->fwrite = THREAD_RUN;
    this->fread = THREAD_RUN;
    this->reader = std::thread(&StationMonitor::thread_read, this);
    this->writer = std::thread(&StationMonitor::thread_write, this);
}


void StationMonitor::thread_read() {
    std::unique_lock<std::mutex> uq(this->mutRead);
    while (true) {
        std::stringstream ss;

        condition.wait(uq, [this] { return this->fread == THREAD_RUN
            || this->fread == THREAD_STOP;
        });
        if (this->fread == THREAD_STOP)
            return;

        std::string buffer(read_port(SIZE_READ_PORT));
        ss << buffer;

        try {
            boost::archive::text_iarchive rd(ss);
            rd & this->marker;
            check_marker();
        } catch (const boost::archive::archive_exception &ex) {
            get_status(buffer);
            send_marker();
            continue;
        }
        THREAD_SET_FLAG_RUN(this->mutWrite, this->condition, this->fwrite);
    }
}

void StationMonitor::send_status(Status &S) {
    std::stringstream ss;
    boost::archive::text_oarchive wr(ss);
    wr & S;

    write_port(ss.str());
}

void StationMonitor::set_priority_mode(const unsigned int &priority) {
    this->priority = priority;
}

void StationMonitor::set_early_release_regime(const unsigned int &flag) {
    this->regime = flag;
}
