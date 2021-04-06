//
//  main.c
//  lab 5.lists
//
//  Created by Belousov Ilya on 4/18/20.
//  Copyright © 2020 Belousov Ilya. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <curses.h>

//struct list {
//    char book;
//    struct list *next;
//};

//typedef struct list ListNode;
//typedef ListNode *ListNodePtr; ??
//void insert (ListNodePtr*, char);
//char del (ListNodePtr*, char);
//int IsEmpty(ListNodePtr);
//void printList (ListNodePtr);
//void instructions (void);

//int main () {
//    ListNodePtr start = NULL;
//    int choice;
//    char elem;
//    instructions();
//    printf("Answer: ");
//    scanf("%d", &choice);
//    while (choice != 3) {
//        switch (choice) {
//            case 1:
//                printf("Enter an character: ");
//                scanf("\n%c", &elem);
//                insert(&start, elem);
//                printList(start);
//                break;
//
//            case 2:
//                if (!IsEmpty(start)) {
//                    printf("Enter character to be delete: ");
//                    scanf("%c", &elem);
//                    if (del(&start, elem)) {
//                        printf("%c deleted.\n", elem);
//                        printList(start);
//                    }
//
//                    else {
//                        printf("%c not found.\n", elem);
//                    }
//                }
//
//                else {
//                    printf("List if empty.\n");
//                    break;
//                }
//
//            default:
//                printf("Invalid choice.\n");
//                instructions();
//                break;
//        }
//        printf("?");
//        scanf("%d", &choice);
//    }
//    printf("End of run.\n");
//    return 0;
//}

//void instructions (void) {
//    printf("Enter choice:\n"
//    "1) Insert an element into the list.\n"
//    "2) Delete an element from the list.\n"
//    "3) End program.\n");
//}

//void insert (ListNodePtr *s, char value) {
//    ListNodePtr newP, previous, current;
//    newP = (ListNodePtr) malloc (sizeof(ListNode));
//    if (newP != NULL) {
//        newP -> book = value;
//        newP -> next = NULL;
//        previous = NULL;
//        current = *s;
//        while (current != NULL && value > current -> book) {
//            previous = current;
//            current = current -> next;
//        }
//
//        if (previous == NULL) {
//            newP -> next = *s;
//            *s = newP;
//        }
//
//        else {
//            previous -> next = newP;
//            newP -> next = current;
//        }
//    }
//
//    else {
//        printf("%c not inserted. No memory avaliable.\n", value);
//    }
//}
// delete alam in list
//char del (ListNodePtr *s, char value) {
//    ListNodePtr previous, current, temp;
//    if (value == (*s) -> book) {
//        temp = *s;
//        *s = (*s)-> next;
//        free(temp);
//        return value;
//    }
//
//    else {
//        previous = *s;
//        current = (*s) -> next;
//        while (current != NULL && current -> book != value) {
//            previous = current;
//            current = current -> next;
//        }
//        if (current != NULL) {
//            temp = current;
//            previous -> next = current -> next;
//            free(temp);
//            return value;
//        }
//    }
//    return '\0';
//}
// возвратить 1, если список пуст, 0 в противном случае
//int IsEmpty (ListNodePtr s) {
//    return s = NULL;
//}

//void printList (ListNodePtr current) {
//    if (current == NULL) printf("the list is empty.\n");
//    else {
//        printf("The list if: \n");
//        while (current != NULL) {
//            printf("%c -->", current -> book);
//            current = current -> next;
//        }
//        printf("NULL\n");
//    }
//}

// Лабораторная работа 5. Вариант 3
//1. Реализовать односвязный список целочисленных значений, поддерживающий порядок по мере добавления элементов. Добавить возможность вывода элементов списка.

//struct list {
//    int number;
//    struct list *next;
//};
//
//
//typedef struct list *ListPointer;
//void list_entry (ListPointer *s, int );
//void Print_list (ListPointer);
//
//int main () {
//    ListPointer start = NULL;
//    int num = 0;
//    while (num != 99) {
//        printf("Enter an character (getchar exit): ");
//        scanf("%d", &num);
//        list_entry(&start, num);
//        Print_list(start);
//    }
//    free(start);
//    return 0;
//}
//
//void list_entry (ListPointer *s, int value) {
//    ListPointer newP, previous, current, save; // Это все указатели на структуру
//    newP = (ListPointer) malloc (sizeof(ListPointer));
//
//    if (newP != NULL) {
//        newP -> number = value;
//        newP -> next = NULL;
//        previous = NULL;
//        current = *s;
//
//        while (current != NULL) { //value > current -> number
//
//            if (previous == NULL && value < current -> number) {
//                save = current;
//                *s = newP;
//                newP -> next = save;
//                break;
//            }
//
//            if (value >= current -> number) {
//                previous = current;
//                current = current -> next;
//
//            }
//
//            else if (value < current -> number) {
//                save = previous -> next;
//                previous -> next = newP;
//                newP -> next = save;
//                break;
//            }
//        }
//
//        if (previous == NULL) {
//            *s = newP;
//        }
//
//        else {
//            previous -> next = newP;
//
//        }
//    }
//
//    else {
//        printf("%d not inserted. No memory avaliable.\n", value);
//        exit(1);
//    }
//
//}
//
//void Print_list (ListPointer current) {
//    if (current == NULL) printf("The list is empty.\n"); // список пуст
//    else {
//        printf("The list if: ");
//        while (current != NULL) {
//            printf("%d -> ", current -> number);
//            current = current -> next;
//        }
//        if (current == NULL) printf("NULL\n");
//    }
//}

//2. Реализовать стек целочисленных значений на основе односвязного списка, функции push и pop. Поменять местами N-й и M-й элементы стека, используя только эти функции. N и M задать с клавиатуры.


#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY   -102


struct stack {
    int number;
    struct stack *next;
};

typedef struct stack *StkPointer;
void push (StkPointer *, int);
void location (StkPointer *, StkPointer *, int );
void gluing (StkPointer *, StkPointer *);
void printStack (StkPointer);
size_t getSize (StkPointer);
int pop (StkPointer *);

int main () {
    StkPointer head = NULL, newHead = NULL;
    int i, save_i;
    for (i = 0; i < 10; i++) {
        push(&head, i);
    }
    printStack(head);
    size_t SizeStack = getSize(head);
    printf("Size stack = %zu\n", SizeStack);
    while (head) {
        int N, M;
        printf("What two elements do you want to swap? (N,M).\nAnswer: ");
        scanf("%d %d", &N, &M);
        if (N > M) {
            i = M;
            M = N;
            N = i;
        }

        if (N == M || N > SizeStack || M > SizeStack) {
            printf("---------------------------Warning!--------------------------------\n");
            printf("The entered values are larger than the stack itself.\n");
            printf("-------------------------------------------------------------------\n");
            continue;
        }
            location(&head, &newHead, N);
            save_i = pop(&newHead);
            M--;
            gluing(&head, &newHead);
            location(&head, &newHead, M);
            i = pop(&newHead);
            push(&newHead, save_i);
            gluing(&head, &newHead);
            location(&head, &newHead, N);
            push(&newHead, i);
            gluing(&head, &newHead);
            printStack(head);
        break;
        }

    free(head);
    return 0;
}

void push (StkPointer *head, int value) {
    StkPointer newP;
    newP = (StkPointer) malloc (sizeof(StkPointer));
    if (newP == NULL) {
        exit(STACK_OVERFLOW);
    }
        newP -> next = *head;
        newP -> number = value;
        *head = newP;
}

int pop (StkPointer *head) {
    StkPointer out;
    if ((*head) == NULL) {
        exit(STACK_UNDERFLOW);
    }
    out = *head;
    *head = (*head) -> next;
    return out -> number;
}

void location (StkPointer *head, StkPointer *newHead, int pos) {
    StkPointer current, previous = NULL;
    current = *head;
    int counter = 0;
    while (head) {
        counter++;
        if (pos == 1) {
            *head = NULL;
            *newHead = current;
            break;
        }
        else if (counter == pos) {
            *newHead = current;
            previous -> next = NULL;
            break;
        }
        previous = current;
        current = current -> next;
    }

}

void gluing (StkPointer *head, StkPointer *newHead) {
    StkPointer current, previous = NULL;
    current = *head;
    while (head) {
        if ((*head) == NULL) {
            *head = *newHead;
            break;
        }

        if (current == NULL) {
            previous -> next = *newHead;
            break;
        }
        previous = current;
        current = current -> next;
    }
}

void printStack (StkPointer current) {
    if (current == NULL) printf("The stack if empty.\n");
    else {
        printf("The stack if:  ");
        while (current != NULL) {
            printf("%d -> ", current -> number);
            current = current -> next;
        }
    }
    if (current == NULL) printf("NULL\n");
}

size_t getSize (StkPointer head) {
    size_t size = 0;
    while (head != NULL) {
        size++;
        head = head -> next;
    }
    return size;
}

