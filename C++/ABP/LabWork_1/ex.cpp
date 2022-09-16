//
//  ex.cpp
//  LabWork_1
//
//  Created by Belousov Ilya on 22.02.22.
//

#include <iostream>
#include <array>

#include "matrix/matrix.hpp"
#include "logger.h"

using namespace::std;

#define SIZE_ROW 5
#define SIZE_COLOMN 1
#define SIZE_MAS 10
#define SIZE_COUNTER 300

using classic = int [SIZE_ROW][SIZE_COLOMN];
using invert = int [SIZE_COLOMN][SIZE_ROW];
using total = int [SIZE_ROW][SIZE_ROW];

classic mm1;
invert mm2;
total mm3;

void foo()
{
    LOG_DURATION("Enable.");
#pragma clang loop vectorize(enable) interleave(enable)
    for (int e = 0; e < 12; ++e)
    {
        for (int i = 0; i < SIZE_ROW; ++i)
        {
            for (int j = 0; j < SIZE_ROW; ++j)
            {
                mm3[i][j]  = 0;
                for (int k = 0; k < SIZE_COLOMN; ++k)
                {
                    mm3[i][j] += mm1[i][k] * mm2[k][j] + 1;
                }
            }
        }
    }
}

void foo2()
{
    LOG_DURATION("Disable.");
#pragma clang loop vectorize(disable) interleave(disable)
    for (int e = 0; e < SIZE_COUNTER; ++e)
    {
        for (int i = 0; i < SIZE_ROW; ++i)
        {
            for (int j = 0; j < SIZE_ROW; ++j)
            {
                mm3[i][j]  = 0;
                for (int k = 0; k < SIZE_COLOMN; ++k)
                {
                    mm3[i][j] += mm1[i][k] * mm2[k][j] + 1;
                }
            }
        }
    }
}

//classic mmm1[SIZE_MAS];
//invert mmm2[SIZE_MAS];
//total mmm3[SIZE_MAS];
//
//void foo3()
//{
//    LOG_DURATION("Enable.");
//#pragma clang loop vectorize(enable)
//    for (int u = 0; u < SIZE_COUNTER; ++u)
//    {
//        for (int e = 0; e < SIZE_MAS; ++e)
//        {
//            for (int i = 0; i < SIZE_ROW; ++i)
//            {
//                for (int j = 0; j < SIZE_ROW; ++j)
//                {
//                    mmm3[e][i][j] = 0;
//                    for (int k = 0; k < SIZE_COLOMN; ++k)
//                    {
//                        mmm3[e][i][j] += mmm1[e][k][j] * mmm2[e][i][k];
//                    }
//                }
//            }
//        }
//    }
//}
//
//void foo4()
//{
//    LOG_DURATION("Disable.");
//#pragma clang loop vectorize(disable)
//    for (int u = 0; u < SIZE_COUNTER; ++u)
//    {
//        for (int e = 0; e < SIZE_MAS; ++e)
//        {
//            for (int i = 0; i < SIZE_ROW; ++i)
//            {
//                for (int j = 0; j < SIZE_ROW; ++j)
//                {
//                    mmm3[e][i][j] = 0;
//                    for (int k = 0; k < SIZE_COLOMN; ++k)
//                    {
//                        mmm3[e][i][j] += mmm1[e][k][j] * mmm2[e][i][k];
//                    }
//                }
//            }
//        }
//    }
//}

template <typename Type>
void Generate(Type matrix)
{
    std::random_device rd;
    std::mt19937 e{rd()}; // or std::default_random_engine e{rd()};
    std::uniform_int_distribution<int> dist{1, 50};
    
    for (int i = 0; i < SIZE_ROW; ++i)
    {
        for (int j = 0; j < SIZE_ROW; ++j)
        {
            matrix[i][j] = dist(rd);
        }
    }
}

int main()
{
    
    LOG_DURATION("Main.");
//    Matrix<double, 5, 1> m1;
//    Matrix<double, 1, 5> m2;
//    Matrix<double, 5, 5> m3;
    
    Generate(mm1);
    
    
    for (int i = 0; i < 10; ++i)
    {
        //        m3 = m1 * m2;
        //        m3 = m1 / m2;
        foo();
        foo2();
        
//        foo3();
//        foo4();
    }
    //
    //    //    Matrix<Matrix<double, 5, 1>, 5, 1> mm1;
    //    //    Matrix<Matrix<double, 1, 5>, 1, 5> mm2;
    
    //#pragma clang loop vectorize(disable)
    
    return 0;
}

// в 2 раза ускорение
using classic1 = int [SIZE_ROW];
classic1 cmm1, cmm2, cmm3;
void foo()
{
    LOG_DURATION("Enable.");
#pragma clang loop interleave_count(2) vectorize_width(8)
    for (int i = 0; i < SIZE_ROW; ++i)
    {
        cmm3[i] += cmm1[i] * cmm2[i];
    }
}

void foo2()
{
    LOG_DURATION("Disable.");
#pragma clang loop vectorize(disable)
    for (int i = 0; i < SIZE_ROW; ++i)
    {
        cmm3[i] += cmm1[i] * cmm2[i];
    }
}

// матрица с ускорение в 2 раза
using classic = int [SIZE_ROW][SIZE_COLOMN];
classic mm1, mm2, mm3;

void foo()
{
    LOG_DURATION("Enable.");
#pragma clang loop vectorize(enable) interleave_count(4) vectorize_width(8)
    for (int i = 0; i < SIZE_ROW; ++i)
    {
        for (int j = 0; j < SIZE_COLOMN; ++j)
        {
            mm3[i][j] += mm1[i][j] * mm2[i][j];
        }
    }
}

void foo2()
{
    LOG_DURATION("Disable.");
#pragma clang loop vectorize(disable)
    for (int i = 0; i < SIZE_ROW; ++i)
    {
        for (int j = 0; j < SIZE_COLOMN; ++j)
        {
            mm3[i][j] += mm1[i][j] * mm2[i][j];
        }
    }
}


// умножение матриц

#define SIZE_ROW 256
#define SIZE_COLOMN 1

//#define SIZE_MAS 10
//#define SIZE_COUNTER 1

using classic = float [SIZE_ROW][SIZE_COLOMN];
using invert = float [SIZE_COLOMN][SIZE_ROW];
using total = float [SIZE_ROW][SIZE_ROW];

classic mm1;
invert mm2;
total mm3;

//interleave_count(4) кол-во итераций за раз
//vectorize_width(8) размер регистра

void foo()
{
    LOG_DURATION("Enable.");

    for (int i = 0; i < SIZE_ROW; ++i)
    {
#pragma clang loop vectorize(enable) interleave_count(4) vectorize_width(8)
        for (int j = 0; j < SIZE_ROW; ++j)
        {
            mm3[i][j] = 0;
            for (int k = 0; k < SIZE_COLOMN; ++k)
            {
                mm3[i][j] += mm1[i][k] * mm2[k][j];
            }
        }
    }
}

void foo2()
{
    LOG_DURATION("Disable.");
#pragma clang loop vectorize(disable)
    for (int i = 0; i < SIZE_ROW; ++i)
    {
#pragma clang loop vectorize(disable)
        for (int j = 0; j < SIZE_ROW; ++j)
        {
            mm3[i][j] = 0;
#pragma clang loop vectorize(disable)
            for (int k = 0; k < SIZE_COLOMN; ++k)
            {
                mm3[i][j] += mm1[i][k] * mm2[k][j];
            }
        }
    }
}

// массив матриц

#define SIZE_ROW 256
#define SIZE_COLOMN 1

#define SIZE_MAS 10
//#define SIZE_COUNTER 1

using classic = float [SIZE_ROW][SIZE_COLOMN];
using invert = float [SIZE_COLOMN][SIZE_ROW];
using total = float [SIZE_ROW][SIZE_ROW];

classic mm1[SIZE_MAS];
invert mm2[SIZE_MAS];
total mm3[SIZE_MAS];

//interleave_count(4) кол-во итераций за раз
//vectorize_width(8) размер регистра

void foo()
{
    LOG_DURATION("Enable.");
//#pragma clang loop vectorize(enable)
    for (int e = 0; e < SIZE_MAS; ++e)
    {
        for (int i = 0; i < SIZE_ROW; ++i)
        {
#pragma clang loop vectorize(enable) interleave_count(4) vectorize_width(8)
            for (int j = 0; j < SIZE_ROW; ++j)
            {
                mm3[e][i][j] = 0;
                for (int k = 0; k < SIZE_COLOMN; ++k)
                {
                    mm3[e][i][j] += mm1[e][i][k] * mm2[e][k][j];
                }
            }
        }
    }
}

void foo2()
{
    LOG_DURATION("Disable.");
#pragma clang loop vectorize(disable)
    for (int e = 0; e < SIZE_MAS; ++e)
    {
#pragma clang loop vectorize(disable)
        for (int i = 0; i < SIZE_ROW; ++i)
        {
#pragma clang loop vectorize(disable)
            for (int j = 0; j < SIZE_ROW; ++j)
            {
                mm3[e][i][j] = 0;
#pragma clang loop vectorize(disable)
                for (int k = 0; k < SIZE_COLOMN; ++k)
                {
                    mm3[e][i][j] += mm1[e][i][k] * mm2[e][k][j];
                }
            }
        }
    }
}
