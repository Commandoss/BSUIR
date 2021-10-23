//
//  Fsystem.cpp
//  Search in processes
//
//  Created by Belousov Ilya on 18.10.21.
//

#include "Fsystem.hpp"

Fsystem::Fsystem() : file{}, path{}, mode{} {
}

Fsystem::Fsystem(const fs::path &path, const std::ios_base::openmode &mode) : file{}, path{path}, mode{mode} {
    open_file();
}

Fsystem::~Fsystem() {
    if (is_open())
        file.close();
}

int Fsystem::file_type(const fs::path &path) noexcept {
    if(fs::is_regular_file(path))
        return Regular_File;
    if(fs::is_directory(path))
        return Directory;
    if(fs::is_block_file(path))
        return Block_File;
    if(fs::is_character_file(path))
        return Character_File;
    if(fs::is_fifo(path))
        return Fifo;
    if(fs::is_socket(path))
        return Socket;
    if(fs::is_symlink(path))
        return Symlink;
    if(!fs::exists(path))
        return Exists;
    return -1;
}

std::list<fs::path> Fsystem::get_directory_content(const fs::path &path) const {
    if (!fs::is_directory(path))
        error("Fsystem::get_directory_content(const fs::path &path)\nThe given path is not a directory.");

    std::list<fs::path> lDirectory;
    for (const fs::directory_entry &file : fs::directory_iterator{path}) {
        lDirectory.push_back(file.path());
    }


    return lDirectory;
}

void Fsystem::open_file() {
    this->file.open(this->path, this->mode);

    if (!is_open())
        error("Fsystem::open_file()\nThe file was not opened.");
}

void Fsystem::open_file(const fs::path &path, const std::ios_base::openmode &mode) {
    if (is_open())
        error("Fsystem::open_file(const fs::path &path, const std::ios_base::openmode &mode)\nThe file was not opened.\nThis object already has an open stream");

    this->path = path;
    this->mode = mode;

    open_file();
}

bool Fsystem::is_open() const noexcept {
    return this->file.is_open();
}

void Fsystem::close() {
    this->file.close();
}

void Fsystem::error(const std::string &msg) const {
    throw msg;
}

std::string Fsystem::read_file_all() const {
    std::stringstream ss;
    ss << this->file.rdbuf();
    return ss.str();
}

std::string Fsystem::read_file_line() {
    std::string buffer;
    std::getline(this->file, buffer);
    return buffer;
}

//std::string Fsystem::read_file_symbol() {
//    std::string buffer();
//    return buffer;
//}

void Fsystem::write_file(const std::string &str) {
    if (!is_open())
        error("Fsystem::write_file(const std::string &str)\nThe file was not opened.");

    this->file << str;
}

bool Fsystem::find_in_file(const std::string &str) {
    if (!is_open())
        error("Fsystem::find_in_file(const std::string &str)\nThe file was not opened.");

    std::string buffer;
    while (!this->file.eof()) {
        buffer = read_file_line();
        if (buffer.find(str) != std::string::npos)
            return true;

        buffer.clear();
    }
    return false;
}

void Fsystem::set_offset(const std::fpos_t offset) {
    if (!is_open())
        error("Fsystem::set_offset(const std::fpos_t offset)\nThe file was not opened.");

    this->file.seekg(offset);
}

std::fpos_t Fsystem::get_offset() {
    return this->file.tellg();
}
