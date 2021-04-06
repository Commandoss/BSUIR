//
//  Matrix.hpp
//  Lab 1.1
//
//  Created by Belousov Ilya on 9/5/20.
//  Copyright © 2020 Belousov Ilya. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp


#endif /* Matrix_hpp */
#include <iostream>
#include <iomanip>

using namespace std;

class cMatrix {
private:
    int size; // size matrix
    int **mas = nullptr; // pointer
    
public:
    
    cMatrix(int value); // constructors (memory allocation)
    ~cMatrix() ; // destructors
    void initialization(); // fill matrix
    void output(); // print matrix
//    cMatrix& multiplication(cMatrix &cM1, cMatrix &cM2);
//    cMatrix summation(cMatrix &cM1);
//    cMatrix& summation(cMatrix &cM1, cMatrix &cM2);
    cMatrix operator+(const cMatrix &cM);
    cMatrix operator*(const cMatrix &cM);
    friend cMatrix operator+(int value, const cMatrix &cM);
    cMatrix operator+(int value);
    void operator=(const cMatrix &cM);
//    cMatrix& operator=(const cMatrix &cM);
};

