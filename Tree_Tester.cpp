#include <iostream>
#include "Tree_Algorithms.h"
#include "BST.h"

using namespace std;

int main() {
    BST<int> tree;
    tree.insert(46);
    tree.insert(13);
    tree.insert(7);
    tree.insert(4);
    tree.insert(10);
    tree.insert(34);
    tree.insert(19);
    tree.insert(16);
    tree.insert(28);
    tree.insert(22);
    tree.insert(31);
    tree.insert(25);
    tree.insert(40);
    tree.insert(37);
    tree.insert(43);
    //tree.insert(49);
    //cout << "everything included" << endl;
    cout << tree.to_string() << endl;
    //cout << "stringed" << endl;
    BST<int>::Node *&n = tree._root;
    //cout << "in" << endl;
    Tx::_splay<int>(n,34);
    //cout << "out" << endl;
    //bool b = tree._root == nullptr;
    //cout <<b;
    cout << "Outside splay: " << endl;
    cout << tree.to_string() << endl;
    
    // cout << "made" << endl;
    // Tx::_rotate_with_left_child<int>(n);
    // cout << tree.to_string() << endl;
}