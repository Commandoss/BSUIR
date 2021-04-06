//
//  main.c
//  lab 6.turn
//
//  Created by Belousov Ilya on 2/10/20.
//  Copyright © 2020 Belousov Ilya. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <curses.h>
#include <time.h>

// Лабораторная работа 6. Вариант 2
//1. Реализовать очередь целочисленных значений, функции push_back, pop_front. Изначально добавить в очередь 4 числа. Далее при каждом добавлении извлекать число из головы очереди. Вывести сообщение в случае, если извлекаемое число равно сумме всех элементов очереди после извлечения элемента из головы и добавления нового.

#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY   -102

//struct turn {
//    int number;
//    struct turn *next;
//};
//
//typedef struct turn *TurnPointer;
//void push_back (TurnPointer *, int );
//int pop_front (TurnPointer *);
//void printTurn (TurnPointer);
//void sumTurn (TurnPointer, int );
//
//int main () {
//    TurnPointer start = NULL;
//    srand(time(NULL));
//    int i, Y = 1, counter = 0;
//    while (counter < 4) {
//        counter++;
//        i = rand() % 10;
//        push_back(&start, i);
//    }
//    printTurn(start);
//
//    while (true) {
//        printf("-------------------------------------------------------------------\n");
//        printf("Want to add an item to the turn?\n");
//        printf("1) Yes   2) No\nAnswer: ");
//        scanf("%d", &Y);
//        printf("-------------------------------------------------------------------\n");
//        if (Y != 1) break;
//        printf("Enter an item in the turn: ");
//        scanf("%d", &i);
//        push_back(&start, i);
//        counter = pop_front(&start);
//        sumTurn(start, counter);
//        printTurn(start);
//    }
////    sumTurn(start, start -> number);
//    printTurn(start);
//
//
//    free(start);
//    return 0;
//}
//
//void push_back (TurnPointer *head, int value) {
//    TurnPointer newP, current, previous;
//    newP = (TurnPointer) malloc (sizeof(TurnPointer));
//
//    if (newP != NULL) {
//        newP -> number = value;
//        newP -> next = NULL;
//        previous = NULL;
//        current = *head;
//
//        while (current != NULL) {
//            previous = current;
//            current = current -> next;
//        }
//
//        if (previous == NULL) {
//            *head = newP;
//        }
//
//        else {
//            previous -> next = newP;
//        }
//    }
//
//    else {
//        printf("%d not inserted. No memory avaliable.\n", value);
//    }
//}
//
//int pop_front (TurnPointer *head) {
//    int out;
//    if ((*head) == NULL) {
//        exit(STACK_OVERFLOW);
//    }
//    out = (*head) -> number;
//    *head = (*head) -> next;
//
//    return out;
//}
//
//void sumTurn (TurnPointer head, int out_value) {
//    TurnPointer Pointer = head;
//    if ((head) == NULL) {
//        exit(STACK_OVERFLOW);
//    }
//    int sum = 0;
//    while (Pointer != NULL) {
//        sum = sum + Pointer -> number;
//        Pointer = Pointer -> next;
//    }
//    if (sum == out_value) {
//        printf("-------------------------------------------------------------------\n");
//        printf("The output element is equal to the sum of all elements of the turn.\n");
//        printf("Output element = %d\nSum = %d\n", out_value, sum);
//        printf("-------------------------------------------------------------------\n");
//    }
//}
//
//
//void printTurn(TurnPointer current) {
//    if (current == NULL) printf("The turn if empty.\n");
//    else {
//        printf("The turn if: ");
//        while (current != NULL) {
//            printf("%d -> ", current -> number);
//            current = current -> next;
//        }
//        if (current == NULL) printf("NULL\n");
//    }
//}

//2. Реализовать кольцо целочисленных значений, функции добавления, удаления и вывода элементов. С клавиатуры ввести элементы кольца и задать число M. На каждом проходе по кольцу удалить те элементы, которые делятся на M без остатка. M уменьшается на единицу после каждого прохода пока не достигнет единицы. Выводить элементы кольца после каждого прохода.

struct ring {
    int number;
    struct ring *next;
};

typedef struct ring *RingPointer;
void push (RingPointer *, int );
void pop_del (RingPointer *, int);
void printRing (RingPointer);
int checkR (RingPointer, int);

int main () {
    RingPointer start = NULL;
    int Answer = 1, num, quantity = 0, divindend = 0;
    while (true) {
        printf("What do you want to do next?\n");
        printf("1) Add multiple items\n"
               "2) Set a dividend\n"
               "3) Close program\n"
               "Answer: ");
        scanf("%d", &Answer);

        if (Answer == 1) {
            printf("-------------------------------------------------------------------\n");
            printf("How many elements do you want to add?\nAnswer: ");
            scanf("%d", &quantity);
            for (int i = 0; i < quantity; i++) {
                printf("Add an item to the ring: ");
                scanf("%d", &num);
                push(&start, num);
                printRing(start);
            }
            continue;
        }

        if (Answer == 2) {
            printf("Enter dividend: ");
            scanf("%d", &divindend);
//            if (checkR(start, divindend) == 0) {
//                printf("---------------------------Warning!--------------------------------\n");
//                printf("Invalid number entered\n");
//                printf("-------------------------------------------------------------------\n");
//                continue;
//            }
            pop_del(&start, divindend);
            printRing(start);
            continue;
        }

        else {
            printf("Close program.\n");
            break;
        }
    }
    free(start);
    return 0;
}

void push (RingPointer *ring, int value) {
    RingPointer newP, current, previous;
    newP = (RingPointer) malloc (sizeof(RingPointer));

    if (newP != NULL) {
        newP -> number = value;
        newP -> next = *ring;
        previous = NULL;
        current = *ring;

        while (current != NULL) {
            previous = current;
            current = current -> next;
            if (current == *ring) break;
        }

        if (previous == NULL) {
            *ring = newP;
            newP -> next = *ring;
        }

        else {
            previous -> next = newP;
        }
    }

    else {
        printf("%d not inserted. No memory avaliable.\n", value);
    }
}
// можно сделать проверку на ввод
void pop_del (RingPointer *ring, int divind) {
    RingPointer current = *ring, previous = NULL, check = *ring;
    int i;
    if (current == NULL) printf("The Ring if empty.\n");
    while (divind != 1) {
        int currNum = current -> number;
        if ((currNum % divind) == 0) {

            if (current == *ring) {
                while (true) {
                    previous = check;
                    check = check -> next;
                    if (check == current) {
                        previous -> next = (*ring) -> next;
                        check = (*ring) -> next;
                        break;
                    }
                }
                free(current);
                *ring = (*ring) -> next;
                current = *ring;
            }

            else {
                previous -> next = current -> next;
                free(current);
                current = previous -> next;

            }
//            if (current == *ring) {
//            divind--;
////                current = *ring;
////                continue;
//            }
        }

        else {
            previous = current;
            current = current -> next;
        }
        if (current == *ring) {
            divind--;
            printRing(*ring);
//            i = checkR(*ring, divind);
//            if (i == 0) break;
        }

    }
}

int checkR (RingPointer ring, int value) {
    RingPointer point = ring;
    while (true) {
        if ((ring -> number % value) == 0) {
            return 1;
        }
        ring = ring -> next;
        if (ring == point) break;
    }
    return 0;
}

void printRing (RingPointer current) {
    RingPointer firstelem = current;
    if (current == NULL) printf("The Ring if empty.\n");
    else {
        printf("The Ring if: ");
        while (true) {
            printf("%d -> ", current -> number);
            current = current -> next;
            if (current == firstelem) {
                printf("...\n");
                break;
            }
        }
    }
}
