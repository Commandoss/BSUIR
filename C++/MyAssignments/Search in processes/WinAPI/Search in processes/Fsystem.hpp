//
//  Fsystem.hpp
//  Search in processes
//
//  Created by Belousov Ilya on 18.10.21.
//

#ifndef Fsystem_hpp
#define Fsystem_hpp

#include <fstream>
#include <list>
#include <sstream>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

enum file_type {
    Regular_File = 0,
    Directory,
    Block_File,
    Character_File,
    Fifo,
    Socket,
    Symlink,
    Exists,
};

class Fsystem {
private:
    std::fstream file;
    fs::path path;
    std::ios_base::openmode mode;

public:
    Fsystem();
    Fsystem(const fs::path &path, const std::ios_base::openmode &mode);

    static int file_type(const fs::path &path) noexcept;

    void open_file(const std::string &path, const std::ios_base::openmode &mode);

    bool is_open() const noexcept;

    void close();

    std::list<fs::path> get_directory_content(const fs::path &path) const;
    std::string read_file_all() const;
    std::string read_file_line();
//    std::string read_file_symbol(offset...);

    //write...
    void write_file(const std::string &str);

    bool find_in_file(const std::string &str);

    void set_offset(const std::fpos_t offset);
    std::fpos_t get_offset();

private:
    void open_file();

    void error(const std::string &msg) const;
};

#endif /* Fsystem_hpp */
