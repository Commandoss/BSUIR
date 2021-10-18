//
//  List.hpp
//  Diary
//
//  Created by Belousov Ilya on 11.12.20.
//

#ifndef List_hpp
#define List_hpp

#include <iostream>

#include "ExceptionInput.hpp"

using namespace std;

template <class Type> class cList;
template <class Type> struct ListNode;

template <class Type>
class OwnIterator {
protected:
    ListNode<Type> *Iter;
public:
    OwnIterator();
    OwnIterator(Type *p);
    OwnIterator(ListNode<Type> *node);
    OwnIterator(const OwnIterator &cO);

    OwnIterator& operator++();
    OwnIterator& operator--();
    bool operator==(const OwnIterator &other) const;
    bool operator!=(const OwnIterator &other) const;
    OwnIterator& operator=(ListNode<Type> &cOI);
    Type& operator*();
    Type& operator[](const int index);
    
    friend ostream& operator<<(ostream &os, OwnIterator &cOI) {
        os << cOI.Iter->value;
        return os;
    }
    
    friend istream& operator>>(istream &in, OwnIterator &cOI) {
        in >> cOI.Iter->value;
        return in;
    }
};

template <class Type>
OwnIterator<Type>::OwnIterator() {
    Iter = NULL;
}

template <class Type>
OwnIterator<Type>::OwnIterator(Type *p) {
    this->Iter = p;
}

template <class Type>
OwnIterator<Type>::OwnIterator(ListNode<Type> *root) {
    this->Iter = root;
}

template <class Type>
OwnIterator<Type>::OwnIterator(const OwnIterator &cO) {
    this->Iter = cO.Iter;
}

template <class Type>
bool OwnIterator<Type>::operator!=(const OwnIterator<Type> &other) const {
    return this->Iter != other.Iter;
}

template <class Type>
bool OwnIterator<Type>::operator==(const OwnIterator<Type> &other) const {
    return Iter == other.Iter;
}

template <class Type>
OwnIterator<Type>& OwnIterator<Type>::operator++() {

    Iter = Iter->next;
    return *this;
}

template <class Type>
OwnIterator<Type> &OwnIterator<Type>::operator--() {
    if (Iter->last != NULL)
        Iter = Iter->last;
    return *this;
}

template <class Type>
Type& OwnIterator<Type>::operator[](const int index) {
    int meter = 1;
    while (meter != index) {
        Iter = Iter->next;
        meter++;
    }
    return Iter;
}

template <class Type>
OwnIterator<Type>& OwnIterator<Type>::operator=(ListNode<Type> &cOI) {
    delete Iter;
    OwnIterator<Type> newOI(cOI);
    this = newOI;
    return *this;
}

template <class Type>
Type& OwnIterator<Type>::operator*() {
    return Iter->value;
}

//LIST ---------------------------------------------

enum menuList {
    AddItem = 1,
    RemoveItem,
    changeEvent,
    RemoveList,
    SwapItem,
    PrintList,
};

template <class Type>
struct ListNode {
    Type value;
    ListNode *next;
    ListNode *last;
};

template <class Type>
class cList {
protected:
    ListNode<Type> *head;
    int counter = 0;
public:
    cList();
    ~cList();
    
    typedef OwnIterator<Type> iterator;
    typedef OwnIterator<const Type> const_iterator;
    
    iterator begin();
    iterator end();
    
    const_iterator begin() const;
    const_iterator end() const;
    
    void addNode(Type val);
    void remove(ListNode<Type> *head);
    bool isEmpty(); //+
    int getCount(); //+
    void setValue(ListNode<Type> *pointer, Type val); //+
    
//    cList<Type>& sortListAscend();
    
//    void link(ListNode<Type>* a, ListNode<Type>* b );
    
    ListNode<Type>* removeItem(ListNode<Type> *node);
    ListNode<Type>* getValue(ListNode<Type> *pointer);//+
    ListNode<Type>* getFirst();
    ListNode<Type>* getLast();
    ListNode<Type>* FindItem(ListNode<Type> *node, int key);
    
    void Print();
    void Print(int &number);
    
    
//    void Swap(ListNode<Type>* a, ListNode<Type>* b );
    
    void menuList(int menuInput);
};

template <class Type>
cList<Type>::cList() {
    this->head = NULL;
}

template <class Type>
cList<Type>::~cList() {
    this->head = NULL;
}

template <class Type>
int cList<Type>::getCount() {
    return this->counter;
}

template <class Type>
bool cList<Type>::isEmpty() {
    return this->head == NULL;
}

template <class Type>
void cList<Type>::setValue(ListNode<Type> *pointer, Type val) {
    pointer->value = val;
}

template <class Type>
ListNode<Type>* cList<Type>::getValue(ListNode<Type> *pointer) {
    return pointer->value;
}

template <class Type>
void cList<Type>::addNode(Type val) {
    ListNode<Type> *current = head, *newNode;
    newNode = new ListNode<Type>;
    if (newNode != NULL) {
        newNode->next = NULL;
        newNode->value = val;
        
        if (head == NULL) {
            head = newNode;
            head->last = NULL;
            counter++;
            return;
        }
        
        current = getLast();
        current->next = newNode;
        newNode->last = current;
        counter++;
    }
    else {
        cout << "No memory was kept." << endl;
        exit(1);
    }
}

template <class Type>
void cList<Type>::remove(ListNode<Type> *head) {
    ListNode<Type> *current = getLast(), *previous;
    while (current) {
        previous = current->last;
        delete current;
        current = NULL;
        current = previous;
    }
    this->head = NULL;
}

template <class Type>
ListNode<Type>* cList<Type>::getFirst() {
    return head;
}

template <class Type>
ListNode<Type>* cList<Type>::getLast() {
    if (head != NULL) {
    ListNode<Type> *pointer = head;
    while (pointer->next != NULL)
        pointer = pointer->next;
        return pointer;
    }
    return head;
    
}

template <class Type>
void cList<Type>::Print() {
    if (isEmpty()) {
        cout << "\nThe list is empty.\n" << endl;
        return;
    }
    
    int number = 1;
    ListNode<Type> *current = head;
    while (current) {
        cout << "\n" << number << ".";
        current->value.printEvent();
        current = current->next;
        number++;
    }
}

template <class Type>
void cList<Type>::Print(int &number) {
    if (isEmpty()) {
        cout << "\nThe list is empty.\n" << endl;
        return;
    }
    
    ListNode<Type> *current = head;
    while (current) {
        cout << "\n" << number << ".";
        current->value.printEvent();
        current = current->next;
        number++;
    }
}

//template <class Type>
//void cList<Type>::link(ListNode<Type>* a, ListNode<Type>* b )
//{
//    if (a == NULL) {
//        return;
//    }
//    else {
//        a->next = b;
//        b->next = a;
//    }
//}

//template <class Type>
//void cList<Type>::Swap(ListNode<Type>* a, ListNode<Type>* b )
//{
//    if(a==b) return; // don't swap with yourself
//
//    // handle adjacent nodes separately
//    if( a->next == b )
//    {
//        ListNode<Type>* bef = a->last;
//        ListNode<Type>* aft = b->next;
//        link( bef, b);    // link bef, b, a, aft
//        link( b, a );
//        link( a, aft );
//    }
//    else if( b->next == a )
//    {
//        ListNode<Type>* bef = b->last;
//        ListNode<Type>* aft = a->next;
//        link( bef, a);   // link bef, a, b, aft
//        link( a, b );
//        link( b, aft );
//    }
//    else
//    {
//        ListNode<Type>* a_prv = a->last;
//        ListNode<Type>* a_nxt = a->next;
//        ListNode<Type>* b_prv = b->last;
//        ListNode<Type>* b_nxt = b->next;
//
//        link( a_prv, b ); link( b, a_nxt ); // links b in a's old position
//        link( b_prv, a ); link( a, b_nxt ); // links a in b's old position
//    }
//}

template <class Type>
ListNode<Type>* cList<Type>::FindItem(ListNode<Type> *node, int key) {
    int meter = 1;
    while (meter != key) {
        node = node->next;
        meter++;
    }
    return node;
}

template <class Type>
ListNode<Type>* cList<Type>::removeItem(ListNode<Type> *node) {
    ListNode<Type> *previous = NULL, *current = node;
    if (current->next != NULL && current->last != NULL) {
        previous = current->last;
        previous->next = current->next;
        delete current;
        current = NULL;
        current = previous->next;
        current->last = previous;
    }
    else if (current->next != NULL) {
        node = current->next;
        delete current;
        current = NULL;
    }
    else if (current->last != NULL) {
        previous = current->last;
        delete current;
        current = NULL;
        previous->next = NULL;
    }
    else {
        delete node;
        node = NULL;
        head = NULL;
        return NULL;
    }
    return node;
}

//template <class Type>
//cList<Type>& cList<Type>::sortListAscend() {
//    ListNode<Type> *previous = head, *current = head;
//    if (current->next != NULL) {
////        for (int i = 0; i < counter; i++) {
////            for (int j = i + 1; j < counter; j++) {
//                    current = current->next;
//                if (previous->value.getData(3) > current->value.getData(3)) {
//                    Swap(current, previous);
//                }
//                else if (previous->value.getData(3) == current->value.getData(3)) {
//                    if (previous->value.getData(2) > current->value.getData(2)) {
//                        Swap(current, previous);
//                    }
//                    else if (previous->value.getData(2) == current->value.getData(2)) {
//                        if (previous->value.getData(1) > current->value.getData(1)) {
//                            Swap(current, previous);
//                        }
//                    }
////                }
////            }
////            ()
//        }
//    }
//    return *this;
//}

template <class Type>
void cList<Type>::menuList(int menuInput) {
    Type newObj;
    switch (menuInput) {
        case AddItem:
            newObj.setEvent();
            newObj.changeType();
            addNode(newObj);
            break;
            
        case RemoveItem:
            int removeNumber;
            cout << "\nEnter the number of the element you want to delete: ";
            removeNumber = ExceptionInput::check_int(getCount(), 1);
            removeItem(FindItem(head, removeNumber));
            break;
            
        case changeEvent:
            int changeNumber;
            if (isEmpty()) {
                cout << "\nThe list is empty, the item cannot be changed."
                     << "Create event first.\n" << endl;
            }
            else {
                cout << "\nEnter the number of the element you want to change: ";
                changeNumber = ExceptionInput::check_int(getCount(), 1);
                FindItem(head, changeNumber)->value.menuObj();
            }
            break;
            
        case RemoveList:
            remove(head);
            if (head == NULL) cout << "\nThe tree has been cleaned." << endl;
            else cout << "\nThe tree was not cleaned." << endl;
            break;
            
        case PrintList:
            Print();
            break;
            
        default:
            break;
            
    }
}

template <class Type>
typename cList<Type>::iterator cList<Type>::begin() {
    return iterator(getFirst());
}

template <class Type>
typename cList<Type>::iterator cList<Type>::end() {
    if (getLast() != NULL)
        return iterator(getLast()->next);
    return iterator(getLast());
}

template <class Type>
typename cList<Type>::const_iterator cList<Type>::begin() const {
    return const_iterator(getFirst());
}

template <class Type>
typename cList<Type>::const_iterator cList<Type>::end() const {
    if (getLast() != NULL)
        return const_iterator(getLast()->next);
    return const_iterator(getLast());
}



#endif /* List_hpp */
