//
//  Mas.cpp
//  Lab 1.1
//
//  Created by Belousov Ilya on 9/21/20.
//  Copyright © 2020 Belousov Ilya. All rights reserved.
//

#include "Matrix.hpp"

cMatrix::cMatrix(int value) { // constructors
    size = value;
    mas = new int * [size];
    for (int i = 0; i < size; i++)
        mas[i] = new int [size];
}

cMatrix::~cMatrix() { // destructors
    for (int i = 0; i < size; i++)
        delete [] mas[i];
    delete [] mas;
    
    cout << "Dynamic memory has been freed." << endl;
}

void cMatrix::initialization() { // field
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << "Enter the value for the cell [" << i << "][" << j << "] = ";
            cin >> mas[i][j];
            
        }
    }
}

void cMatrix::output() { // print
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << setw(5) << mas[i][j];
        }
        cout << "\n";
    }
}

cMatrix& cMatrix::multiplication(cMatrix &cM1, cMatrix &cM2) {
    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                mas[k][i] += cM1.mas[k][j] * cM2.mas[j][i];
            }
        }
    }
    return *this;
}

cMatrix cMatrix::summation(cMatrix &cM1) {
    cMatrix resultSum(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            resultSum.mas[i][j] = cM1.mas[i][j] + this -> mas[i][j];
        }
    }

    return resultSum;
}

cMatrix cMatrix::operator+(const cMatrix &cM) {
    cMatrix cM3(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cM3.mas[i][j] = this -> mas[i][j] + cM.mas[i][j];
        }
    }
    return cM3;
}

cMatrix cMatrix::operator+(const int value) {
    cMatrix cM3(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cM3.mas[i][j] = this -> mas[i][j] + value;
        }
    }
    return cM3;
}

cMatrix operator+(int value, const cMatrix &cM) {
    cMatrix cM3(cM.size);
    for (int i = 0; i < cM.size; i++) {
        for (int j = 0; j < cM.size; j++) {
            cM3.mas[i][j] = cM.mas[i][j] + value;
        }
    }
    return cM3;
}

cMatrix cMatrix::operator*(const cMatrix &cM) {
    cMatrix resultSum(size);
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    resultSum.mas[i][j] = this -> mas[i][j] * cM.mas[i][j];
                }
            }
    return resultSum;
}

void cMatrix::operator=(const cMatrix &cM) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            this -> mas[i][j] = cM.mas[i][j];
        }
    }
}

//cMatrix& cMatrix::operator=(const cMatrix &cM) {
//    for (int i = 0; i < size; i++) {
//        for (int j = 0; j < size; j++) {
//            this -> mas[i][j] = cM.mas[i][j];
//        }
//    }
//    return *this;
//}
