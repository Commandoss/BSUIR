#include <iostream>
#include <array>
#include <random>
#include <immintrin.h>

#include "logger.h"

using namespace::std;

#define SIZE_ADDITIONAL_SIZE 62

#define SIZE_ROW 2 + SIZE_ADDITIONAL_SIZE
#define SIZE_COLOMN 1

#define SIZE_MAS_ROW 16
#define SIZE_MAS_COLOMN 1

using classic = float[SIZE_ROW][SIZE_COLOMN];
using invert = float[SIZE_COLOMN][SIZE_ROW];
using total = float[SIZE_ROW][SIZE_ROW];

classic mm1[SIZE_MAS_ROW][SIZE_MAS_COLOMN];
invert mm2[SIZE_MAS_COLOMN][SIZE_MAS_ROW];
total mm3[SIZE_MAS_ROW][SIZE_MAS_ROW];

void automatic_vectorization_enable()
{
    LOG_DURATION("Automatic vectorization enable.");
    

    for (int o = 0; o < SIZE_MAS_ROW; ++o)
    {
        for (int u = 0; u < SIZE_MAS_ROW; ++u)
        {
            for (int i = 0; i < SIZE_ROW; i++)
            {
#pragma clang loop vectorize(enable) interleave(enable)
                for (int j = 0; j < SIZE_ROW; j++)
                {
//                    mm3[o][u][i][j] = 0;
                    mm3[o][u][i][j] += mm1[o][0][i][0] * mm2[0][u][0][j];
                }
            }
        }
    }
}

void automatic_vectorization_disable()
{
    LOG_DURATION("Automatic vectorization disable.");
    for (int o = 0; o < SIZE_MAS_ROW; ++o)
    {
        for (int u = 0; u < SIZE_MAS_ROW; ++u)
        {
            for (int i = 0; i < SIZE_ROW; ++i)
            {
#pragma clang loop vectorize(disable)
                for (int j = 0; j < SIZE_ROW; ++j)
                {
//                    mm3[o][u][i][j] = 0;
                    mm3[o][u][i][j] += mm1[o][0][i][0] * mm2[0][u][0][j];
                }
            }
        }
    }
}

void manual_vectorization()
{
    LOG_DURATION("Manual vectorization.");
#pragma clang loop vectorize(disable)
    for (int o = 0; o < SIZE_MAS_ROW; ++o)
    {
#pragma clang loop vectorize(disable)
        for (int u = 0; u < SIZE_MAS_ROW; ++u)
        {
#pragma clang loop vectorize(disable)
            for (int i = 0; i < SIZE_ROW; i += 8)
            {
#pragma clang loop vectorize(disable)
                for (int j = 0; j < SIZE_ROW; j += 8)
                {
//                    mm3[o][u][i][j] = 0;
                    __m256 m1_mul_m2 = _mm256_mul_ps(_mm256_load_ps(&mm1[o][0][i][0]), _mm256_set1_ps(mm2[0][u][0][j]));
                    __m256 sum_m3 = _mm256_add_ps(_mm256_load_ps(&mm3[o][u][i][j]), m1_mul_m2);
                    _mm256_storeu_ps(&mm3[o][u][i][j], sum_m3);
                
                }
            }
        }
    }
}


template <typename Type>
void generate_matrix(Type matrix)
{
    std::random_device rd;
    std::mt19937 e{rd()};
    std::uniform_real_distribution<> dist{1, 500};

    for (int u = 0; u < SIZE_MAS_ROW; ++u)
    {
        for (int e = 0; e < SIZE_MAS_COLOMN; ++e)
        {
            for (int i = 0; i < SIZE_ROW; ++i)
            {
                for (int j = 0; j < SIZE_ROW; ++j)
                {
                    matrix[u][e][i][j] = dist(rd);
                }
            }
        }
    }
}

int main()
{
    generate_matrix(mm1);
    generate_matrix(mm2);
    generate_matrix(mm3);

    for (int i = 0; i < 6; ++i)
    {
        automatic_vectorization_enable();
        automatic_vectorization_disable();
        manual_vectorization();
    }
    return 0;
}
