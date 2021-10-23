//
//  PIDS.hpp
//  Search in processes
//
//  Created by Belousov Ilya on 19.10.21.
//

#ifndef PIDS_hpp
#define PIDS_hpp

#include <libproc.h>
#include <stdlib.h>
#include <string>
#include <list>

class PIDS {
private:
    int amount;
    int *buffer;

    struct proc_bsdinfo info;

public:
    PIDS();
    ~PIDS();

    std::list<pid_t> get_list_pids();
    void pid_info(const pid_t &pid);

    std::string get_pid_name(const pid_t &pid);
    std::string get_pid_path(const pid_t &pid);
//    void

private:
    void list_pids();
//    void pid_region_info(const pid_t &pid);
    void alloc_buffer(const int &size);
    void free_buffer();

    void error(const std::string &msg) const;
};

#endif /* PIDS_hpp */
