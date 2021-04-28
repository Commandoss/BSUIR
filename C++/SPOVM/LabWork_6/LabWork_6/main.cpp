//
//  main.cpp
//  LabWork_6
//
//  Created by Belousov Ilya on 20.04.21.
//

#include <iostream>
#include <stdio.h>
#include <sys/mman.h>
#include "memory.hpp"
#include <string>
#include <ctime>

using namespace::std;

void clearIostreamBuff() {
    cin.ios_base::clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void inputLine(char *line, const int &size) {
    cin.getline(line, size);
    clearIostreamBuff();
}

template <typename type>
void outputMas(const type *array, const int &size) {
    for (int i = 0; i < size; i++) {
        cout << "[" << i << "] = ";
        cout << array[i] << " ";
    }
    cout << endl;
}

template <typename type>
void inputMas(type *array, const int &size) {
    srand((unsigned int) time(NULL));
    for (int i = 0; i < size; i++) {
        cout << "[" << i << "] = ";
        cin >> array[i];
//        array[i] = 0 + rand() % 1000;
    }
}

typedef double typeMas;

int main(int argc, const char * argv[]) {
//    char *a = nullptr,
//         *b = nullptr,
//         *c = nullptr;
//
//    int size_a = 8,
//        size_b = 16,
//        size_c = 8;
//
//    int lineRealocSize = 500;
//
//    a = (char *) cMemory::illoc(sizeof(char) * size_a);
//    b = (char *) cMemory::illoc(sizeof(char) * size_b);
//    c = (char *) cMemory::illoc(sizeof(char) * size_c);
//
//    cout << "Input line #1: ";
//    inputLine(a, size_a);
//
//    cout << "Input line #2: ";
//    inputLine(b, size_b);
//
//    cout << "Input line #3: ";
//    inputLine(c, size_c);
//
//
//    cout << "\n\t------INPUT------" << endl;
//    cMemory::illoc_print_block();
//
//    cMemory::ifree(b);
//
//    a = (char *) cMemory::rilloc(a, lineRealocSize);
//    cout << "\t------REALLOC------" << endl;
//    cMemory::illoc_print_block();
//
//    cMemory::memoryRAM;
//
//    cMemory::ifree(a);
//    cMemory::ifree(b);
//    cMemory::ifree(c);
//
//    cout << "\t------FREE------" << endl;
//    cMemory::illoc_print_block();
    
    typeMas *mas1 = nullptr,
            *mas2 = nullptr,
            *mas3 = nullptr;

    int size_mas1 = 10,
        size_mas2 = 4,
        size_mas3 = 2;

    int masRealocSize = 8;


    mas1 = (typeMas *) cMemory::illoc(sizeof(typeMas) * size_mas1);
//    mas1 = (typeMas *) cMemory::illoc(0);
    mas2 = (typeMas *) cMemory::illoc(sizeof(typeMas) * size_mas2);
    mas3 = (typeMas *) cMemory::illoc(sizeof(typeMas) * size_mas3);

    cout << "Input mas #1: " << endl;
    inputMas(mas1, size_mas1);

    cout << "Input mas #2: " << endl;
    inputMas(mas2, size_mas2);

    cout << "Input mas #3: " << endl;
    inputMas(mas3, size_mas3);


    cout << "\t------INPUT------" << endl;
    cMemory::illoc_print_block();

    cout << "Output mas #1: " << endl;
    outputMas(mas1, size_mas1);

    cout << "Output mas #2: " << endl;
    outputMas(mas2, size_mas2);

    cout << "Output mas #3: " << endl;
    outputMas(mas3, size_mas3);

    mas2 = (typeMas *) cMemory::rilloc(mas2, sizeof(typeMas) * masRealocSize);
    cout << "\t------REALLOC------" << endl;
    cMemory::illoc_print_block();

    cout << "Realoc Input mas #2: " << endl;
    inputMas(mas2, masRealocSize);

    cout << "Output mas #2: " << endl;
    outputMas(mas2, masRealocSize);

    cMemory::ifree(mas1);
    cMemory::ifree(mas2);
    cMemory::ifree(mas3);

    cout << "\n\t------FREE------" << endl;
    cMemory::illoc_print_block();

    return 0;
}


// 123456789012345678901234567890
// hello_world
