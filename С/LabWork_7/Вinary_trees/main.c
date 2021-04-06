//
//  main.c
//  lab 7. Binary trees
//
//  Created by Belousov Ilya on 5/11/20.
//  Copyright © 2020 Belousov Ilya. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <curses.h>
#include <string.h>
#include <time.h>

// Лабораторная работа 7. Вариант 2
//1. Реализовать бинарное дерево с целочисленными ключами, вывод элементов дерева, добавление нового элемента с клавиатуры, задавая ключ родительского элемента и сторону (левый или правый потомок). Вывести количество листьев в дереве.

//struct tree {
//    int key;
//    struct tree *left;
//    struct tree *right;
//    struct tree *parent;
//};
//
//typedef struct tree *PTree;
//void addtree(PTree *, int , int );
//void TreePrint(PTree);
//PTree create(PTree *, int );
//int quantityleaves(PTree);
//void search(PTree *, int , PTree *cop);
//
//int main() {
//    PTree root = NULL, Pointer = NULL;
//    int Answer = 0, number = 0, key_par = 0, select = 0;
//    while (Answer < 4) {
//        printf("What would you like to do?\n"
//               "1) Add an item.\n"
//               "2) Output tree elements.\n"
//               "3) Print the number of element in the tree.\n"
//               "4) Exit.\n"
//               "Answer: ");
//        scanf("%d", &Answer);
//        printf("\n\n");
//
//        if (Answer == 1) {
//            printf("Enter the item you want to add: ");
//            scanf("%d", &number);
//            if (root == NULL) root = create(&root, number);
//            else {
//                printf("Set Parent Key: ");
//                scanf("%d", &key_par);
//                search(&root, key_par, &Pointer);
////                printf(" key !!!= === %d\n", Pointer -> key);
//                printf("Choose a key:\n1) left  2) right\nAnswer: ");
//                scanf("%d", &select);
//                addtree(&Pointer, number, select);
//            }
//        }
//
//        if (Answer == 2) {
//            TreePrint(root);
//            printf("\n");
//        }
//
//        if (Answer == 3) {
//            int count = quantityleaves(root);
//            printf("Quantity leaves = %d\n", count);
//        }
//    }
//    free(root);
//    return 0;
//}
//
//PTree create(PTree *root, int key) {
//    PTree newP = (PTree) malloc(sizeof(PTree));
//    newP -> key = key;
//    newP -> left = NULL;
//    newP -> right = NULL;
//    *root = newP;
//    return *root;
//}
//
//void search(PTree *root, int key, PTree *cop) {
//    if (root == NULL)
//    return;
//
//    if (key == (*root) -> key) {
//        *cop = *root;
//        return;
//    }
//    if ((*root) -> left != NULL)
//    search(&(*root) -> left, key, cop);
//    if ((*root) -> right != NULL)
//    search(&(*root) -> right, key, cop);
//}
//
//void addtree(PTree *root, int key, int sel) {
//    PTree newP = (PTree) malloc(sizeof(PTree));
//    newP -> key = key;
//    newP -> left = NULL;
//    newP -> right = NULL;
//    if (sel == 1) (*root) -> left = newP;
//    else (*root) -> right = newP;
//}
//
//void TreePrint(PTree root) {
//    if (root == NULL)
//        return;
//    if (root -> key)
//        printf(" %d -", root -> key);
//    TreePrint(root -> left);
//    TreePrint(root -> right);
////    printf("\n");
//}
//
//int quantityleaves(PTree root) {
//    int result;
//    if (root == NULL) result = 0;
//    else if ((root -> left == NULL)&&(root -> right == NULL)) result =  1;
//    else result = quantityleaves(root -> left) + quantityleaves(root -> right);
//    return result;
//}

//2. Реализовать структуру “Абонент”, которая хранит фамилию и номер телефона. Хранение организовать в бинарном дереве поиска. Ввести в коде программы большое количество записей с фамилией в качестве ключа. Реализовать поиск телефона по фамилии абонента, вводимой с клавиатуры. Сравнить время поиска со случаем хранения записей в массиве или списке (для этого можно повторить поиск большое количество раз).

#define No_avalible_memory -100

struct subscriber {
    char surname[32];
    int number;
};

struct tree {
    struct subscriber sub;
    struct tree *left;
    struct tree *right;
};

struct list {
    struct subscriber SUB;
    struct list *next;
};

typedef struct tree PtreeNode;
typedef PtreeNode *Ptree;
typedef struct list PlistNode;
typedef PlistNode *Plist;

Ptree CreTreeSUB(Ptree *, int, char []);
Ptree AddTreeSUB (Ptree *, int, char []);
Ptree search (Ptree *, char []);
void PrinTree (Ptree);

void addlist (Plist *, int , char []);
Plist findlist (Plist *, char []);
void printlist (Plist);

int main () {
    Ptree root = NULL, Pointer = NULL;
    Plist start = NULL, Pin = NULL;

    int Answer = 0, phone = 0, counter = 0, copy = 0, tru = 0, N = 0;
    char lastname[32];
    float start_time_tree, end_time_tree, search_time_tree = 0;
    float start_time_list, end_time_list, search_time_list = 0, total;
    
    while (Answer < 8) {
        printf("What would you like to do?\n"
               "1) Add subscriber to tree.\n"
               "2) Add subscriber to list.\n"
               "3) Output elements tree.\n"
               "4) Output elements lists.\n"
               "5) Find element on tree.\n"
               "6) Find element on list.\n"
               "7) Program settings.\n"
               "8) Close program.\n"
               "Answer: ");
        scanf("%d", &Answer);
        srand(time(NULL));
        
        if (Answer < 3) {
            printf("-------------------------------------------------------------------\n");
            printf("How much would you like to add?\nAnswer: ");
            scanf("%d", &counter);
            printf("-------------------------------------------------------------------\n");
            while (counter != 0) {
                counter--;
                N = rand () % 4 + 15;
                lastname[0] = '\0';
                for (int i = 0; i < N; i++)
                    lastname[i] = rand() % 26 + 0x61;
                
                phone = rand() % 77777;
                if (Answer == 1) {
                    if (root == NULL) root = CreTreeSUB(&root, phone, lastname);
                    else AddTreeSUB(&root, phone, lastname);
                }
                if (Answer == 2 || copy == 1) addlist(&start, phone, lastname);
            }
        }
        
        if (Answer == 3){
            printf("-------------------------------------------------------------------\n");
            PrinTree(root);
            printf("-------------------------------------------------------------------\n");
        }

        if (Answer == 4) {
            printf("-------------------------------------------------------------------\n");
            printlist(start);
            printf("-------------------------------------------------------------------\n");
        }
        
        if (Answer == 5 || Answer == 6) {
            printf("-------------------------------------------------------------------\n");
            printf("Enter the last name of the contact: ");
            fflush(stdin);
            scanf("%s", lastname);
            printf("-------------------------------------------------------------------\n");
            
            if (Answer == 5) {
//                Pointer = root;
                start_time_tree =  clock();
                Pointer = search(&root, lastname);
                end_time_tree = clock();
                search_time_tree = (end_time_tree - start_time_tree) / CLOCKS_PER_SEC; // тут поделить
                
                if (Pointer == NULL) printf("Error 404. This contact was not found.\n");
                else {
                    printf("Subscriber: %sPhone: %d\n", Pointer -> sub.surname, Pointer -> sub.number);
                    printf("-------------------------------------------------------------------\n");
                    printf("Time spent searching in the tree : %f ss.\n", search_time_tree);
                    printf("-------------------------------------------------------------------\n");
                }
            }
            if (Answer == 6 || tru == 1) {
                if (start == NULL) printf("Error 404. This contact was not found.\n");
                else {
                    start_time_list =  clock();
                    Pin = findlist(&start, lastname);
                    end_time_list = clock();
                    search_time_list = (end_time_list - start_time_list) / CLOCKS_PER_SEC;
                    
                    printf("Subscriber: %sPhone: %d\n", Pin -> SUB.surname, Pin -> SUB.number);
                    printf("-------------------------------------------------------------------\n");
                    printf("Time spent searching in the list : %f s.\n", search_time_list);
                    printf("-------------------------------------------------------------------\n");
                }
            }
        //-----
            if (tru == 1 && search_time_list != 0 && search_time_tree != 0) {
                if (search_time_list > search_time_tree) {
                    total = (search_time_list - search_time_tree);
                    printf("Tree search faster on: : %f s.\n", total);
                }
                else {
                    total = search_time_tree - search_time_list;
                    printf("List search faster on: %f s.\n", total);
                }
                printf("-------------------------------------------------------------------\n");
            }
            //----
        }
        if (Answer == 7) {
            printf("-------------------------------------------------------------------\n");
            printf("Do you want to automatically copy information from the tree to the list?\n");
            printf("1) Yes 2) No\nAnswer: ");
            scanf("%d", &copy);
            printf("-------------------------------------------------------------------\n");
            printf("Search to produce immediately in both places?\n");
            printf("1) Yes 2) No\nAnswer: ");
            scanf("%d", &tru);
            printf("-------------------------------------------------------------------\n");
        }
    }
    
    free(root); free(start);
    return 0;
}

Ptree CreTreeSUB (Ptree *root, int key, char name[]) {
    Ptree newP = (Ptree) malloc(sizeof(Ptree));
    strcat(newP -> sub.surname, name);
    newP -> sub.number = key;
    newP -> left = NULL;
    newP -> right = NULL;
    *root = newP;
    return *root;
}

Ptree AddTreeSUB (Ptree *root, int key, char name[]) {
    Ptree newP = (Ptree) malloc(sizeof(PtreeNode));
    if (newP != NULL) {
        Ptree current = *root, previous = NULL;

        strcat(newP -> sub.surname, name);
        newP -> sub.number = key;
        newP -> left = NULL;
        newP -> right = NULL;

        while (current != NULL) {
            previous = current;
            if (name[0] < current -> sub.surname[0])
                current = current -> left;
            else current = current -> right;
        }

        if (name[0] < previous -> sub.surname[0]) previous -> left = newP;
        else previous -> right = newP;
    }
    else {
        printf("-------------------------------------------------------------------\n");
        printf("Not inserted. NO memory avaliable.\n");
        printf("-------------------------------------------------------------------\n");
        exit(No_avalible_memory);
    }

    return *root;
}

Ptree search (Ptree *root, char name[]) {
    if (((*root) == NULL) || (strcmp(name, ((*root) -> sub.surname)) == 0)) return *root;
    if (name[0] < (*root) -> sub.surname[0])
        return search(&(*root) -> left, name);
    else return search(&(*root) -> right, name);
}

void PrinTree (Ptree root) {
    if (root != NULL) {
        printf("Subscriber: %s\nPhone: %d\n", root -> sub.surname, root -> sub.number);
        PrinTree(root -> left);
        PrinTree(root -> right);
    }
    else return;
}

void addlist (Plist *s, int num, char name[]) {
    Plist current = *s, previous = NULL, newP;
    newP = (Plist ) malloc(sizeof(PlistNode));
    if (newP != NULL) {
        strcat(newP -> SUB.surname, name);
        newP -> SUB.number = num;
        newP -> next = NULL;

        while (current != NULL) {
            previous = current;
            if (previous == NULL) break;
            current = current -> next;
        }

        if (previous == NULL) *s = newP;
        else previous -> next = newP;
    }
    else {
        printf("-------------------------------------------------------------------\n");
        printf("No inserted. No memory avaliable.\n");
        printf("-------------------------------------------------------------------\n");
        exit(No_avalible_memory);
    }
}

Plist findlist (Plist *s, char name[]) {
    Plist current = *s, previous = NULL;
    if (current == NULL) {
        printf("-------------------------------------------------------------------\n");
        printf("This list if empty.\n");
        printf("-------------------------------------------------------------------\n");
        return current;
    }
    else {
        while (true) {
            if (strcmp(name, current -> SUB.surname) == 0) {
                return current;
            }
            else {
                previous = current;
                current = current -> next;
            }
        }
    }
}

void printlist (Plist current) {
    if (current == NULL) {
        printf("-------------------------------------------------------------------\n");
        printf("This list if empty.\n");
        printf("-------------------------------------------------------------------\n");
        return;
    }
    else {
        printf("-------------------------------------------------------------------\n");
        printf("This list if: \n");
        while (current != NULL) {
            printf("Subscriber: %s\nPhone: %d\n", current -> SUB.surname, current -> SUB.number);
            current = current -> next;
        }
        if (current == NULL) printf("End list.\n");
        printf("-------------------------------------------------------------------\n");
    }
}
