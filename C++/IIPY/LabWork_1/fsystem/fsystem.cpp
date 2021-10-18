//
//  fsystem.cpp
//  LabWork_1
//
//  Created by Belousov Ilya on 5.09.21.
//

#include "fsystem.hpp"

fsystem::fsystem() {
    this->descriptor = nullptr;
}

//fsystem::fsystem(const std::string path) {
//    this->path = path;
//}

fsystem::fsystem(const fs::path path) {
    this->path = path;
}

std::vector<fs::directory_entry> fsystem::directory_content() {
    std::vector<fs::directory_entry> dirContent;
    if (fs::is_directory(this->path)) {
        for (const auto & entry : fs::directory_iterator(this->path)) {
            dirContent.push_back(entry);
        }
    }
    return dirContent;
}


size_t fsystem::free_memory_info() {
    return fs::space("/").available;
}

size_t fsystem::busy_memory_info() {
    fs::space_info sp = fs::space("/");
    return sp.capacity - sp.available;
}

size_t fsystem::total_memory_info() {
    return fs::space("/").capacity;
}

void fsystem::open_file(const char *mode) {
    this->descriptor = fopen(this->path.c_str(), "r");
}

bool fsystem::close_file() {
    fclose(this->descriptor);
    return this->isOpen();
}

bool fsystem::isOpen() {
    return this->descriptor;
}
