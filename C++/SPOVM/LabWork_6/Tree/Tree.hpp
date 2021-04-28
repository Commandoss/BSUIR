//
//  Tree.hpp
//  LabWork_6
//
//  Created by Belousov Ilya on 21.04.21.
//

#ifndef Tree_hpp
#define Tree_hpp

//#include <alloca>

//template <class Type>
//struct nodeTree {
//    Type value;
//    size_t key;
//    nodeTree *left;
//    nodeTree *right;
//};
//
//template <class Type>
//class cBinaryTree {
//private:
//    nodeTree<Type> *root;
//
//public:
//    cBinaryTree();
//    ~cBinaryTree();
//
//
//
//    void addNode(Type value);
////    void destroyElem(nodeTree<Type *root);
//    void destroyTree();
//    void printTree();
//};
//
//template <class Type>
//cBinaryTree<Type>::cBinaryTree() {
//    root = NULL;
//}
//
//template <class Type>
//cBinaryTree<Type>::~cBinaryTree() {
//    destroyTree();
//}
//
//template <class Type>
//void cBinaryTree<Type>::addNode(Type value) {
//    cBinaryTree<Type> *current = root, *previous = NULL, *newNode;
//    newNode = new TreeNode<Type>;
//    if (newNode != NULL) {
//        int newKey;
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
#endif /* Tree_hpp */
