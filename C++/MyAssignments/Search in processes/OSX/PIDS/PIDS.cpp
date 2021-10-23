//
//  PIDS.cpp
//  Search in processes
//
//  Created by Belousov Ilya on 19.10.21.
//

#include "PIDS.hpp"

PIDS::PIDS() : amount(-1), buffer(nullptr) {
}

PIDS::~PIDS() {
    free_buffer();
}

void PIDS::alloc_buffer(const int &size) {
    if (this->buffer != nullptr)
        free_buffer();

    this->buffer = new int[size];
    if (this->buffer == nullptr)
        error("Func: PIDS::alloc_buffer\nInfo: memory allocation error.");
}

void PIDS::free_buffer() {
    if (this->buffer != nullptr) {
        delete [] buffer;
        this->buffer = nullptr;
    }
}

std::list<pid_t> PIDS::get_list_pids() {
    list_pids();

    std::list<pid_t> list;
    for (int i = 0; i < this->amount; i++) {
        list.push_back(this->buffer[i]);
    }

    return list;
}

void PIDS::list_pids() {
    int count = proc_listpids(PROC_ALL_PIDS, 0, NULL, 0);
    if (count < 0)
        error("Func: PIDS::list_pids\nInfo: proc_listpids() return -1");

    alloc_buffer(count);

    this->amount = proc_listpids(PROC_ALL_PIDS, 0, this->buffer, sizeof(int) * count);
    if (this->amount < 0)
        error("Func: PIDS::list_pids\nInfo: proc_listpids(buffer) return -1");
}

void PIDS::pid_info(const pid_t &pid) {
    if (proc_pidinfo(pid, PROC_PIDTBSDINFO, 0, &info, sizeof(info)) < 0)
        error("Func: PIDS::pid_info(const pid_t &pid)\nInfo: proc_pidinfo return -1");
}

std::string PIDS::get_pid_name(const pid_t &pid) {
    char name[2*MAXCOMLEN];
    if (proc_name(pid, name, sizeof(name)) < 0)
        error("Func: PIDS::pid_name(const pid_t &pid)\nInfo: proc_name(pid, name, sizeof(name)) return -1");

    return name;
}

std::string PIDS::get_pid_path(const pid_t &pid) {
    char path[PROC_PIDPATHINFO_MAXSIZE];
    if (proc_pidpath(pid, path, sizeof(path)) < 0)
        error("Func: PIDS::pid_path(const pid_t &pid)\nInfo: proc_pidpath return -1");

    return path;
}

//void PIDS::pid_region_info(const pid_t &pid) {
//    struct proc_regioninfo reg;
//    proc_pidinfo(pid, PROC_PIDREGIONINFO, 0, &reg, sizeof(reg));
//    uint64_t *a = &reg.pri_address;
//}

void PIDS::error(const std::string &msg) const {
    throw msg;
}

#include <sys/proc.h>

