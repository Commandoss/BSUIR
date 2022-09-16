//
//  main.cpp
//  LabWork_2
//
//  Created by Belousov Ilya on 28.02.22.
//

#include <iostream>
#include <random>
#include <sstream>
#include <memory>
#include <array>

#include "logger.h"

constexpr uint64_t MIN_ASSOCIATIVITY = 1;
constexpr uint64_t MAX_ASSOCIATIVITY = 60;

constexpr uint64_t ELEMENT_SIZE = 32;
constexpr uint64_t CACHE_SIZE = 6 * 1024 * 1024;

constexpr uint64_t COUNT_ITERATION = INT_MAX / 8;
constexpr uint64_t MAX_BLOCK_COUNT = CACHE_SIZE / ELEMENT_SIZE;

std::unique_ptr<char[]> buffer(new char[(MAX_ASSOCIATIVITY * CACHE_SIZE)]);

char *Init(size_t associativity)
{
    uint64_t BLOCK_SIZE = CACHE_SIZE / associativity;
    uint64_t BLOCK_COUNT = BLOCK_SIZE / ELEMENT_SIZE;
    
    using element_t = uint8_t[ELEMENT_SIZE];
    using block_t = element_t[MAX_BLOCK_COUNT];
    std::memset(buffer.get(), '\0', CACHE_SIZE * MAX_ASSOCIATIVITY);
    
    block_t *cache = reinterpret_cast<block_t*>(buffer.get());
    
    for (size_t index_bank = 0; index_bank < associativity; ++index_bank)
    {
        for (size_t index_block = 0; index_block < BLOCK_COUNT; ++index_block)
        {
            if (index_bank < associativity - 1)
            {
                reinterpret_cast<uint64_t&>(cache[index_bank][index_block]) = (index_block + ((index_bank + 1) * MAX_BLOCK_COUNT)) * ELEMENT_SIZE;
            }
            else
            {
                reinterpret_cast<uint64_t&>(cache[index_bank][index_block]) = (index_block + 1) * ELEMENT_SIZE;
            }
        }
    }
    reinterpret_cast<uint64_t&>(cache[associativity - 1][BLOCK_COUNT - 1]) = 0;
    
    return reinterpret_cast<char*>(cache[0][0]);
}


int main()
{
    std::stringstream ss;
    std::chrono::steady_clock::time_point start, finish;
    
    uint64_t t = 0;
    for (size_t associativity = MIN_ASSOCIATIVITY; associativity <= MAX_ASSOCIATIVITY; ++associativity)
    {
        char *ptr = Init(associativity);
        
        start = std::chrono::steady_clock::now();
        
        for (uint64_t k = 0; k < COUNT_ITERATION; ++k)
        {
            t = reinterpret_cast<uint64_t&>(ptr[t]);
        }
        
        finish = std::chrono::steady_clock::now();
        ss << "Associativity = " << associativity << " " << t
        << " Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << " millis" << std::endl;
    }
    std::cout << ss.rdbuf();
}
