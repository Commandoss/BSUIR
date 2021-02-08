//
//  main.cpp
//  Diary
//
//  Created by Belousov Ilya on 11.12.20.
//

#include "LibraryMain.h"

void menuProgram(int &menuInput, int &createObj);

template <class Type>
void createE(cList<Type> &newNode);

template <class Type>
void deleteE(cList<Type> &newNode);

template <class Type>
void changeE(cList<Type> &newNode);

template <class Type>
void deleteL(cList<Type> &newNode);

template <class Type>
void printL(cList<Type> &newNode);

template <class Type>
void saveL(cList<Type> &newNode);

template <class Type1, class Type2, class Type3>
void printAllList(cList<Type1> &newNode1, cList<Type2> &newNode2, cList<Type3> &newNode3);

template <class Type>
void checkListEvent(cList<Type> &newNode);

void sortL(cList<cImportEveryday> &newNode);

void sortL(cList<cImportWork> &newNode);


int main(int argc, const char * argv[]) {
    cout << setw(15) <<"---Diary---" << endl;
    File f;
    cList<cImportWork> LIW;
    cList<cImportPersonal> LIP;
    cList<cImportEveryday> LIE;

    cList<cImportWork>::iterator itLIW, endLIW;
    cList<cImportPersonal>::iterator itLIP, endLIP;
    cList<cImportEveryday>::iterator itLIE, endLIE;
    
    f.decode("LiwData.txt");
    f.decode("LipData.txt");
    f.decode("LieData.txt");
    
    f.readListFile(LIW, "LiwData.txt");
    f.readListFile(LIP, "LipData.txt");
    f.readListFile(LIE, "LieData.txt");


    int menuInput = 0, createObj = 0;
    while (menuInput != 7) {

        checkListEvent(LIW);
        checkListEvent(LIE);

        menuProgram(menuInput, createObj);
        switch (menuInput) {
            case Create:
                if (createObj == Work) createE(LIW);
                if (createObj == Personal) createE(LIP);
                if (createObj == Everyday) createE(LIE);
                break;

            case Delete:
                if (createObj == Work) deleteE(LIW);
                if (createObj == Personal) deleteE(LIP);
                if (createObj == Everyday) deleteE(LIE);
                break;

            case Change:
                if (createObj == Work) changeE(LIW);
                if (createObj == Personal) changeE(LIP);
                if (createObj == Everyday) changeE(LIE);
                break;

            case DeleteList:
                if (createObj == Work) deleteL(LIW);
                if (createObj == Personal) deleteL(LIP);
                if (createObj == Everyday) deleteL(LIE);
                break;

            case Print:
                if (createObj == Work) printL(LIW);
                if (createObj == Personal) printL(LIP);
                if (createObj == Everyday) printL(LIE);
                break;

            case PrintAll:
                printAllList(LIW, LIP, LIE);
                break;

            default:
                break;
        }
    }
    
    itLIW = LIW.begin();
    endLIW = LIW.end();
    
    itLIP = LIP.begin();
    endLIP = LIP.end();
    
    itLIE = LIE.begin();
    endLIE = LIE.end();

    f.writeListFile(itLIW, endLIW, "LiwData.txt");
    f.writeListFile(itLIP, endLIP, "LipData.txt");
    f.writeListFile(itLIE, endLIE, "LieData.txt");
    
    f.code("LiwData.txt");
    f.code("LipData.txt");
    f.code("LieData.txt");
}

void menuProgram(int &menuInput, int &createObj) {
    cout << "\nHow do you want to do?\n";
    cout << "1. Create Event.\n" << "2. Delete event.\n";
    cout << "3. Change Event.\n" << "4. Delete list.\n";
    cout << "5. Print list.\n" << "6. Print all list event.\n";
    cout << "7. Exit.\n" << "Answer: ";
    menuInput = ExceptionInput::check_int(7, 1);
    if (menuInput == 7 || menuInput == 6) return;
 
    cout << "\nWhat type do you want to use?\n";
    cout << "1. Work.\n" << "2. Personal.\n";
    cout << "3. Everyday.\n";
    cout << "4. Exit.\n" << "Answer: ";
    createObj = ExceptionInput::check_int(4, 1);
    if (createObj == 4) return;
}

template <class Type>
void createE(cList<Type> &newNode) {
    newNode.menuList(Create);
}

template <class Type>
void deleteE(cList<Type> &newNode) {
    newNode.menuList(Delete);
}

template <class Type>
void changeE(cList<Type> &newNode) {
    newNode.menuList(Change);
}

template <class Type>
void deleteL(cList<Type> &newNode) {
    newNode.menuList(DeleteList);
}

template <class Type>
void printL(cList<Type> &newNode) {
    newNode.menuList(PrintList);
}

template <class Type>
void saveL(cList<Type> &newNode) {
    newNode.menuList(Save);
}

template <class Type>
void checkListEvent(cList<Type> &newNode) {
    cAlerts cA;
    OwnIterator<Type> ite, end;
    ListNode<Type> *Item;
    ite = newNode.begin();
    end = newNode.end();
    for(int counter = 1; ite != end; ++ite, ++counter) {
        if (cA.checkEvents(*ite)) {
            int answer = 0;
            cout << "\nWhat do you want to do with this event." << endl;
            cout << "1. Change event.\n" << "2. Delete event.\n";
            cout << "Answer: ";
            answer = ExceptionInput::check_int(2, 1);
            switch (answer) {
                case 1:
                    Item = newNode.FindItem(newNode.getFirst(), counter);
                    Item->value.menuObj();
                    break;
                    
                case 2:
                    Item = newNode.FindItem(newNode.getFirst(), counter);
                    newNode.removeItem(Item);
                    break;
                    
                default:
                    break;
            }
        }
    }
    
}

template <class Type1, class Type2, class Type3>
void printAllList(cList<Type1> &newNode1, cList<Type2> &newNode2, cList<Type3> &newNode3) {
    int allcount = 1;
    if (newNode1.getFirst() == NULL &&
        newNode2.getFirst() == NULL &&
        newNode3.getFirst() == NULL) {
        cout << "\nAll lists are empty." << endl;
    }
    else {
        if (newNode1.getFirst() != NULL)
            newNode1.Print(allcount);
        if (newNode2.getFirst() != NULL)
            newNode2.Print(allcount);
        if (newNode3.getFirst() != NULL)
            newNode3.Print(allcount);
    }
}

//void sortL(cList<cImportWork> &newNode) {
//    newNode.sortListAscend();
//}
//
//void sortL(cList<cImportEveryday> &newNode) {
//    newNode.sortListAscend();
//}
