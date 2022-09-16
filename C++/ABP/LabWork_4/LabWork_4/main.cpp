//
//  main.cpp
//  LabWork_4
//
//  Created by Belousov Ilya on 14.04.22.
//

#include <iostream>
#include <random>
#include <iomanip>

using MTp = uint8_t;

MTp *init(size_t size)
{
    MTp *pointer = new MTp[size];
    std::memset(pointer, 0, size);
    
    return pointer;
}

void fill(MTp *matrix, size_t size)
{
    std::random_device rd;
    std::mt19937 e{rd()};
    std::uniform_int_distribution<> dist{1, 500};
    
    for (uint64_t i = 0; i < size; i += sizeof(int))
    {
        reinterpret_cast<int&>(matrix[i]) = dist(rd);
    }
}

void print(const MTp *matrix, size_t N, size_t M)
{
    for (uint64_t i = 0; i < N * sizeof(int); i += sizeof(int))
    {
        for (uint64_t j = 0; j < M  * sizeof(int); j += sizeof(int))
        {
            std::cout << std::setw(4) << std::setfill(' ') << static_cast<int>(matrix[i * M + j]);
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void trans(const MTp *matrix, MTp *total_matrix, size_t N, size_t M, size_t pice)
{
    int counter = 0;
    for (uint64_t i = 0; i < pice * sizeof(int); i += sizeof(int))
    {
        for (uint64_t j = 0; j < pice * sizeof(int); j += sizeof(int))
        {
            reinterpret_cast<int&>(total_matrix[i * M + j]) = static_cast<int>(matrix[counter]);
            counter += sizeof(int);
        }
    }
}

void transform(const MTp *matrix, MTp *total_matrix, size_t N, size_t M, size_t pice)
{
    uint64_t i_total = 0,
             j_total = 0;
    
    uint64_t N_total = N / 2,
             M_total = M * 2,
             pice_total = std::sqrt(pice);
    
    for (uint64_t i = 0; i < N * sizeof(int); i += sizeof(int))
    {
        for (uint64_t j = 0; j < M * sizeof(int); j += sizeof(int) * pice, j_total += sizeof(int) * pice_tota)
        {
            trans(matrix + (i * M + j),
                  total_matrix + (i_total * M_total + j_total),
                  N_total, M_total, pice_total);
        }
        return;
    }
}

int main(int argc, const char * argv[]) {
    constexpr size_t N = 16;
    constexpr size_t M = 8;
    constexpr size_t pice = 4;
    
    MTp *matrix = init(N * M * sizeof(int));
    fill(matrix, N * M * sizeof(int));
    print(matrix, N, M);
    
    MTp *total_matrix = init(N * M * sizeof(int));
    transform(matrix, total_matrix, N, M, pice);
    print(total_matrix, N / 2, M * 2);
    
    
    delete [] matrix;
    delete [] total_matrix;
    return 0;
}
