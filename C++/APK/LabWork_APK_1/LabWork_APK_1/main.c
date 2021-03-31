//
//  main.c
//  LabWork_APK_1
//
//  Created by Belousov Ilya on 29.03.21.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int myOperation(int matr);

void printMatrix(int a, int b, int **matrix) {
    for (int i = 0; i < a; i++){
        printf(" ");
        for (int j = 0; j < b; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int** autoInputMatrix(int a, int b) {
    int **matrix = (int **)malloc(a*sizeof(int *));
    for(int i = 0; i < a; i++) {
        matrix[i] = (int *)malloc(b*sizeof(int));
    }
    srand(time(NULL));
    for (int i = 0; i < a; i++){
        for (int j = 0; j < b; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
    return matrix;
}

int** InputMatrix(int a, int b) {
    int **matrix = (int **)malloc(a*sizeof(int *));
    for(int i = 0; i < a; i++) {
        matrix[i] = (int *)malloc(b*sizeof(int));
    }
    for (int i = 0; i < a; i++){
        for (int j = 0; j < b; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    return matrix;
}

int powNum(int x, int y) {
    for (; y != 1; y--) {
        x *= x;
    }
    return x;
}

int sumMatrix(int a, int b, int **matrix) {
    int c = 0;
    for (int i = 0; i < a; i++){
        for (int j = 0; j < b; j++) {
            c += powNum(matrix[i][j], 2);
        }
    }
    
    return c;
}

int main() {
    int a, b, x, y;
    
    printf("Set the size of the matrix: \n");
    printf("A = ");
    scanf("%d", &a);
    printf("B = ");
    scanf("%d", &b);
    
    int **matrix = autoInputMatrix(a, b);
//    int **matrix = InputMatrix(a, b);
    
    printf("\nThe input matrix: \n");
    printMatrix(a, b, matrix);

    printf("Sum of squares of a matrix: %d\n", sumMatrix(a, b, matrix));
    
    printf("\nThe resilt matrix: \n");
    printMatrix(a, b, matrix);
    
    printf("\n");
    return 0;
}
