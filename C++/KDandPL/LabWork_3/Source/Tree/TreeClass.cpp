//
//  TreeClass.cpp
//  LabWork_7_Tree
//
//  Created by Belousov Ilya on 27.11.20.
//

//#include "TreeClass.hpp"

#ifndef TreeClass1_hpp
#define TreeClass1_hpp

//template <class Type> // constructor
//TreeClass<Type>::TreeClass() {
//    root = NULL;
//}
//
//template <class Type> // destructor
//TreeClass<Type>::~TreeClass() {
//    DestroyTree(root);
//}
//
//template <class Type> // удаление элемента дерева (возможна утечка)
//TreeNode<Type>* TreeClass<Type>::freeNode(TreeNode<Type> *root, const int key) {
//    if (root == NULL) {
//        cout << "Empty tree.\n" << endl;
//        return root;
//    }
//
//    if (key < root->key) {
//        root->left = freeNode(root->left, key);
//    }
//    else if (key > root->key) {
//        root->right = freeNode(root->right, key);
//    }
//    else if (root->left != NULL && root->right != NULL) {
//        root->key = minKey(root->right)->key;
//        root->right = freeNode(root->right, root->key);
//    }
//    else {
//        if (root->left != NULL) {
//            root = root->left;
//        }
//        else if (root->right != NULL) {
//            root = root->right;
//        }
//        else {
//            DestroyElemTree(root);
//        }
//    }
//    return root;
//}
//
//template <class Type> // добавление элемента в дерево
//void TreeClass<Type>::addNode(Type val) {
//    TreeNode<Type> *current = root, *previous = NULL, *newNode;
//    newNode = new TreeNode<Type>;
//    if (newNode != NULL) {
//        int newKey;
//        do {
//            cout << "Set Key: ";
//            newKey = MyExcep_Input::check_int(100, 0);
//        } while (check_key(root, newKey));
//
//        newNode->left = NULL;
//        newNode->right = NULL;
//        newNode->key = newKey;
//        newNode->value = val;
//
//        if (root == NULL) {
//            root = newNode;
//            return;
//        }
//
//        while (current != NULL) {
//            previous = current;
//            if (newKey < current->key)
//                current = current->left;
//            else current = current->right;
//        }
//
//        if (newKey < previous->key) previous->left = newNode;
//        else previous->right = newNode;
//    }
//    else {
//        cout << "No memory was kept." << endl;
//        exit(1);
//    }
//}
//
//template <class Type> // поиск элемента в дереве
//TreeNode<Type>* TreeClass<Type>::searchTree(TreeNode<Type> *root, int value) {
//    if ((root == NULL) || (value == root->key)) return root;
//    if (value < root -> key)
//        return searchTree(root->left, value);
//    else return searchTree(root->right, value);
//}
//
//template <class Type> // вывод всех элементов дерева
//void TreeClass<Type>::printTree(TreeNode<Type> *root) {
//    if (root) {
//        cout << root->value;
//        printTree(root->left);
//        printTree(root->right);
//    }
//}
//
//template <class Type> // нахождение объекта с минимальным ключом
//TreeNode<Type>* TreeClass<Type>::minKey(TreeNode<Type> *root) {
//    if (root->left == NULL) {
//        return root;
//    }
//    return minKey(root->left);
//}
//
//template <class Type> // нахождение объекта с максимальным ключом
//TreeNode<Type>* TreeClass<Type>::maxKey(TreeNode<Type> *root) {
//    if (root->right == NULL) {
//        return root;
//    }
//    return minKey(root->right);
//}
//
//template <class Type> // удаление всех элементов дерева
//void TreeClass<Type>::DestroyTree(TreeNode<Type> *root) {
//    if (root) {
//        DestroyTree(root->left);
//        DestroyTree(root->right);
//        delete this->root;
//        this->root = NULL;
//    }
//}
//
//template <class Type> // удаление всех элементов дерева
//void TreeClass<Type>::DestroyElemTree(TreeNode<Type> *root) {
//    if (root->left == NULL && root->right == NULL) {
//        delete root;
//        root = NULL;
//    }
//}
//
//template <class Type> // проверка ключей
//bool TreeClass<Type>::check_key(TreeNode<Type> *root, int newKey) {
//    if (root) {
//        if (root->key == newKey) {
//            cout << "This key is already available." << endl;
//            return 1;
//        }
//        check_key(root->left, newKey);
//        check_key(root->right, newKey);
//    }
//    return 0;
//}
//
//template <class Type> // вывод всех ключей
//bool TreeClass<Type>::print_key(TreeNode<Type> *root) {
//    if (root) {
//        cout << setw(4) << root->key;
//        print_key(root->left);
//        print_key(root->rigth);
//    }
//}
//
//template <class Type>
//void TreeClass<Type>::menuTree() {
//    int menuInput = 0;
//    while (menuInput < 8) {
//
//        cout << "\nWhat do you want to do in this binary search tree?\n";
//        cout << "1. Add item.\n" << "2. Remove item.\n";
//        cout << "3. Find item.\n" << "4. Find the minimum key.\n";
//        cout << "5. Find the maximum key.\n" << "6. Remove tree.\n";
//        cout << "7. Print Tree.\n" << "8. Change elem tree.\n";
//        cout << "9. Exit.\n" << "Answer: ";
//        menuInput = MyExcep_Input::check_int(9, 1);
//        Type newObj;
//
//        switch (menuInput) {
//            case AddItem:
//                cin >> newObj;
//                addNode(newObj);
//                break;
//
//            case RemoveItem:
//                int removeKey;
//                cout << "Set the key of the item to remove: ";
//                removeKey = MyExcep_Input::check_int(100, 0);
//                freeNode(root, removeKey);
//                break;
//
//            case FindItem:
//                int findKey;
//                cout << "Set the key of the item to find: ";
//                findKey = MyExcep_Input::check_int(100, 0);
//                searchTree(root, findKey);
//                break;
//
//            case FindMin:
//                cout << "Minimum tree key: " << minKey(root)->key << endl;
//                break;
//
//            case FindMax:
//                cout << "Maximum tree key: " << maxKey(root)->key << endl;
//                break;
//
//            case RemoveTree:
//                DestroyTree(root);
//                return;
//                break;
//
//            case PrintTree:
//                if (root) {
//                    root->value.Table();
//                    printTree(root);
//                } else {
//                    cout << "Empty tree.\n" << endl;
//                }
//
//                break;
//
//            case changeElement:
//                int changeKey;
//                cout << "Enter the key of the element you want to change: ";
//                changeKey = MyExcep_Input::check_int(100, 0);
//                searchTree(root, changeKey)->value.menuObj();
//                break;
//
//            default:
//                break;
//        }
//    }
//}
#endif /* TreeClass_hpp */
