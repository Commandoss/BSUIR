//
//  main.cpp
//  Lab5
//
//  Created by Belousov Ilya on 10/9/20.
//

#include "Library.h"

void menuObj(int &answer, int &menuInput);

template <class Type>
void createObj(TreeClass<Type> &newNode, const int counter);

int main() {
    
    int answer = 0, menuInput = 0;
    menuObj(answer, menuInput);
    
    TreeClass<HumanClass> TreeH;
    HumanClass H;
    TreeClass<TourisClass> TreeT;
    TourisClass T;
    TreeClass<EntrepreneurClass> TreeE;
    EntrepreneurClass E;
    TreeClass<BusinessClass> TreeB;
    BusinessClass B;
    
    switch (menuInput) {
        case Human:
            createObj(TreeH, answer);
            TreeH.menuTree();
            break;
            
        case Tourist:
            createObj(TreeT, answer);
            TreeT.menuTree();
            break;
            
        case Entrepreneur:
            createObj(TreeE, answer);
            TreeE.menuTree();
            break;
            
        case Business:
            createObj(TreeB, answer);
            TreeB.menuTree();
            break;
            
        default:
            break;
    }
}

void menuObj(int &answer, int &menuInput) {
    cout << "\nHow do you want to do?\n";
    cout << "1. Create object Human.\n" << "2. Create object Tourist.\n";
    cout << "3. Create object Entrepreneur.\n" << "4. Create object Business.\n";
    cout << "5. Exit.\n" << "Answer: ";
    menuInput = MyExcep_Input::check_int(5, 1);
    if (menuInput > 5) return;
    
    cout << "\nHow many objects do you want to create?" << "\nAnswer: ";
    answer = MyExcep_Input::check_int(10, 1);
}

template <class Type>
void createObj(TreeClass<Type> &newNode, const int counter) {
    Type newObj;
    for (int i = 0; i < counter; i++) {
        cout << "\nEnter " <<  i + 1 << " object class:\n";
        cin >> newObj;
        newNode.addNode(newObj);
    }
}
