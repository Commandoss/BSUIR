//
//  main.cpp
//  Lab 1.1
//
//  Created by Belousov Ilya on 9/5/20.
//  Copyright © 2020 Belousov Ilya. All rights reserved.
//

//Лаба 1.1
//1. Реализовать класс для работы с матрицами, в классе реализовать функции:
//1) сложение
//2) умножение
//2. Использовать конструктор с параметрами конструктор функции вывода массивов на экран.
//Память под массивы отводить динам.

#include "Matrix.hpp"

int main() {
    int answer = 0, value = 0;
    
    cout << "Specify Matrix Size (Type N^2) = ";
    cin >> value;
    
    cMatrix cM1(value), cM2(value), cM3(value);
    
    cout << "Filling the matrix #1:\n";
    cM1.initialization();
    cout << "Filling the matrix #2:\n";
    cM2.initialization();
    cout << "Matrix output #1\n";
    cM1.output();
    cout << "Matrix output #2\n";
    cM2.output();
    
    cout << "What operation do you want to perform?" << endl;
    cout << "1. Matrix multiplication.\n"
         << "2. Matrix addition\n"
         << "Answer: ";
    cin >> answer;
//    if (answer == 1) cM3.multiplication(cM1, cM2);
//    else cM3 = cM1.summation(cM2);
    if (answer == 1) {
        cM3 = 10 + cM1 * cM2 + 15; // cM1.operator*(cM2);
    }
    else {
        cM3 = cM1 + cM2; // cM1.operator+(cM2)
    }
//    cM1 = cM2 = cM3;
    cout << "Matrix output #1\n"; cM1.output();
    cout << "Matrix output #2\n"; cM2.output();
    cout << "Matrix output #3\n"; cM3.output();
}




