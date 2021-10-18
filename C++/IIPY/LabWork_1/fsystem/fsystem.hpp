//
//  fsystem.hpp
//  LabWork_1
//
//  Created by Belousov Ilya on 5.09.21.
//

#ifndef fsystem_hpp
#define fsystem_hpp

#include <filesystem>
#include <fstream>
#include <string.h>
#include <vector>

namespace fs = std::__fs::filesystem;

class fsystem {
private:
    fs::path path;
    
    FILE *descriptor;
    
public:
    fsystem();
    fsystem(fs::path path);
    
    std::vector<fs::directory_entry> directory_content();
    
    size_t free_memory_info();
    size_t busy_memory_info();
    size_t total_memory_info();
    
//private:
    
    void open_file(const char *mode);
    bool close_file();
    bool isOpen();
};

#endif /* fsystem_hpp */
