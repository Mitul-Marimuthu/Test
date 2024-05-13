// student id: 20538991
// Bangaru - the Kingaroo of kangaroos
#include <iostream>
#include "BST.h"

#ifndef Tree_Algorithms_h
#define Tree_Algorithms_h

using namespace std;

class Tx {
    private : // change
        template <typename T> static void _rotate_with_left_child(typename BST<T>::Node *&p) {
            if (p == nullptr || p->_left == nullptr) return;
            typename BST<T>::Node *left = p->_left;
            //if (left == nullptr) return;
            typename BST<T>::Node *right = left->_right;
            p->_left = right;
            left->_right = p;
            p = left;
        }
        template <typename T> static void _rotate_with_right_child(typename BST<T>::Node *&p) {
            if (p == nullptr || p->_right == nullptr) return;
            //cout << "in" << endl;
            typename BST<T>::Node *right = p->_right;
            //cout << std::to_string(right->_data) << endl;<
            //if (right == nullptr) return;
            typename BST<T>::Node *left = right->_left;
            //cout << "done" << endl;
            right->_left = p;
            p->_right = left;
            //cout << "yup" << endl;
            //cout << "end" << endl;
            p = right;
            //cout << "end" << endl;
        }
        template <typename T> static void _splay(typename BST<T>::Node *&p, const T &x) { 
            if (p == nullptr) return;
            if (p->_data == x) return;
            if (x < p->_data && p->_left == nullptr) return;
            if (x > p->_data && p->_right == nullptr) return;
            if (p->_left != nullptr && x == p->_left->_data){
                _rotate_with_left_child<T>(p);
                return;
            }
            if (p->_right != nullptr && p->_right->_data == x) {
                _rotate_with_right_child<T>(p);
                return;
            }
            if (x <p->_data && p->_left != nullptr && x < p->_left->_data) {
                _rotate_with_left_child<T>(p);
                _splay<T>(p->_left,x);
                _rotate_with_left_child<T>(p);
            }
            else if (x < p->_data && p->_left != nullptr && ((x < p->_left->_data && p->_left->_left == nullptr) ||
                (x > p->_left->_data && p->_left->_right == nullptr))) {
                _rotate_with_left_child<T>(p);
                return;
            }
            else if (x > p->_data && p->_right != nullptr && x > p->_right->_data) {
                _rotate_with_right_child<T>(p);
                _splay<T>(p->_right,x);
                _rotate_with_right_child<T>(p);
            }
            else if (x > p->_data && p->_right != nullptr && ((x < p->_right->_data && p->_right->_left == nullptr) ||
                (x > p->_right->_data && p->_right->_right == nullptr))) {
                _rotate_with_right_child<T>(p);
                return;
            }
            else if (x < p->_data) {
                _splay<T>(p->_left, x);
                _rotate_with_left_child<T>(p);
            }
            else if (x > p->_data) {
                _splay<T>(p->_right, x);
                _rotate_with_right_child<T>(p);
            }
        }
            // if (p == nullptr) return;
            // typename BST<T>::Node *left;
            // typename BST<T>::Node *right;
            // typename BST<T>::Node *right_min;
            // typename BST<T>::Node *left_max;
            // typename BST<T>::Node *curr = p;
        //     while (true) {
        //         cout << to_string(curr->_data) << endl;
        //         if (x < curr->_data) {
        //             //cout << to_string(curr->_left == nullptr) << endl;
        //             cout << "2" << endl;
        //             if (curr->_left == nullptr) 
        //                 break;
        //             if (x < curr->_left->_data) {
        //                 cout << "3" << endl;
        //                 Tx::_rotate_with_left_child<int>(p);
        //                 cout << to_string(curr->_data) << endl;
        //                 right = curr;
        //                 right_min = curr;
        //             }
        //             if (right_min != nullptr)
        //                 right_min->_left = curr;
        //             else {
        //                 right_min = curr;
        //             }
        //             cout << "3" << endl;
        //             _update_min<T>(right_min);
        //             cout << "4" << endl;
        //             p = p->_left;
        //             curr = p;
        //         }
        //         else if (x > curr->_data) {
        //             if (curr->_right == nullptr) break;
        //             if (x > curr->_right->_data) {
        //                 Tx::_rotate_with_right_child<int>(p);
        //                 left = curr;
        //                 left_max = curr;
        //             }
        //             if (left_max != nullptr)
        //                 left_max->_right = curr;
        //             _update_max<T>(left_max);
        //             p = p->_right;
        //             curr = p;
        //         }
        //         if (x == curr->_data) break; 
        //     }
        //     if (curr->_left != nullptr) {
        //         left_max->_left = curr->_left;
        //     }
        //     if (curr->_right != nullptr) right_min->_right = curr->_right;
        //     p->_left = left;
        //     p->_right = right;
        // }
        // template <typename T> static void _update_min(typename BST<T>::Node *&p) {
        //     if (p->_left == nullptr) return;
        //     p = p->_left;
        //     _update_min<T>(p);
        // }
        // template <typename T> static void _update_max(typename BST<T>::Node *&p) {
        //     if (p->_right == nullptr) return;
        //     p = p->_right;
        //     _update_max<T>(p);
        // }
        // template <typename T> static void _splay(typename BST<T>::Node *&p, const T &x) {
        //     if (p == nullptr) return;
        //     BST<T> less;
        //     BST<T> right;
        //     typename BST<T>::Node *mid = p;
        //     typename BST<T>::Node *first = x < p->_data ? p->_left : p->_right;
        //     if (first == nullptr) return;
        //     if (first->_data == x) {
        //         if (mid->_left == first) Tx::_rotate_with_left_child<T>(p);
        //         else Tx::_rotate_with_right_child<T>(p);
        //         return;
        //     }
        //     //p = p->_left == first ? p->_left : p->_right;
        //     typename BST<T>::Node *second = x < first->_data ? first->_left : first->_right;
        //     while (second != nullptr && second->_data != x) {
        //         //typename BST<T>::Node *old = mid;
        //         if (mid->_left == first && first->_left == second) {
        //             first->_left = nullptr;
        //             Tx::_rotate_with_left_child<T>(mid);
        //             right._insert_pointer(mid);
        //             mid = second;
        //             first = second;
        //         }
        //         else if (mid->_right == first && first->_right == second) {
        //             first->_right = nullptr;
        //             Tx::_rotate_with_right_child<T>(mid);
        //             less._insert_pointer(mid);
        //             mid = second;
        //             first = second;
        //         }
        //         else if (mid->_right == first && first->_left == second) {
        //             mid->_right = nullptr;
        //             less._insert_pointer(mid);
        //         }
        //         else if (mid->_left == first && first->_right == second) {
        //             mid->_left = nullptr;
        //             right._insert_pointer(mid);
        //         }
        //         mid = first;
        //         first = second;
        //         second = x < second->_data ? second->_left : second->_right;
        //     }
        //     p = second == nullptr ? first : second;
        //     //cout << std::to_string(second->_data);
        //     if (mid == first && second == first) {
        //         //cout <<"5";
        //         less._insert_pointer(first->_left);
        //         right._insert_pointer(first->_right);
        //         first->_left = less._root;
        //         first->_right = right._root;
        //         //mid = first;
        //         // typename BST<T>::Node *&t = first;
        //         // p = t;
        //         // return;
        //     }
        //     else if (first == second) {
        //         if (mid->_left == first) {
        //             mid->_left = nullptr;
        //             right._insert_pointer(mid);
        //             less._insert_pointer(first->_left);
        //             right._insert_pointer(first->_right);
        //             first->_left = less._root;
        //             first->_right = right._root;
        //             //mid = first;
        //         }
        //         else {
        //             mid->_right = nullptr;
        //             less._insert_pointer(mid);
        //             less._insert_pointer(first->_left);
        //             right._insert_pointer(first->_right);
        //             first->_left = less._root;
        //             first->_right = right._root;
        //             //mid = first;
        //         }
        //         typename BST<T>::Node *&t = first;
        //         p = t;
        //         return;
        //     }
        //     second = second != nullptr ? second : first;
        //     if (mid->_left == first && first->_left == second) {
        //         //cout << "1";
        //         first->_left = nullptr;
        //         Tx::_rotate_with_left_child<T>(mid);
        //         right._insert_pointer(mid);
        //     }
        //     else if (mid->_right == first && first->_right == second) {
        //         //cout << "2";
        //         first->_right = nullptr;
        //         Tx::_rotate_with_right_child<T>(mid);
        //         less._insert_pointer(mid);
        //     }
        //     else if (mid->_left == first && first->_right == second) {
        //         //cout << "3";
        //         //cout << to_string(second->_data);
        //         mid->_left = nullptr;
        //         right._insert_pointer(mid);
        //         first->_right = nullptr;
        //         less._insert_pointer(first);
        //         // less._insert_pointer(second->_left);
        //         // right._insert_pointer(second->_right);
        //     }
        //     else if (mid->_right == first && first->_left == second) {
        //         //cout << "4";
        //         mid->_right = nullptr;
        //         less._insert_pointer(mid);
        //         first->_left = nullptr;
        //         right._insert_pointer(first);
        //     }
        //     less._insert_pointer(second->_left);
        //     right._insert_pointer(second->_right);
        
        //     second->_left = less._get_root();
        //     second->_right = right._get_root();

        //     //p = new typename BST<T>::Node;
        //     p->_data = second->_data;
        //     p->_left = second->_left;
        //     p->_right = second->_right;
        //     // typename BST<T>::Node *&t = second;
        //     // p = t;
        //     cout << "Inside _splay: " << endl;
        //     BST<T> temp; temp._root = p; cout << temp.to_string() << endl << endl << endl;
        //     // BST<T> temp; temp._root = p;
        //     // cout <<"nah";
        //     // bool b = p->_left == nullptr;
        //     // cout << b;
        //     // cout << temp.to_string();
        // }

        // template <typename T> static void _splay(typename BST<T>::Node *&p, const T &x) {
        //     if (p == nullptr) return;
            
        //     BST<T> *less = new BST<T>();
        //     BST<T> *more = new BST<T>();
        //     BST<T> *mid = new BST<T>();
        //     mid->_root = p;
        //     typename BST<T>::Node *c;
        //     c = BST<T>::_deep_copy(p);
        //     typename BST<T>::Node *first;
        //     typename BST<T>::Node *second;
        //     typename BST<T>::Node *more_end;
        //     typename BST<T>::Node *less_end;
        //     if (x < c->_data) first = c->_left;
        //     else first = c->_right;
        //     if (first == nullptr) return;
        //     else if (first->_data == x) {
        //         if (p->_left == first) Tx::_rotate_with_left_child<T>(p);
        //         else Tx::_rotate_with_right_child<T>(p);
        //         return;
        //     }
        //     if (x < first->_data) second = first->_left;
        //     else second = first->_right;
        //     cout << "abt to enter" << endl;
        //     while (second != nullptr && second->_data != x) {
        //         cout << "entered" << endl;
        //         if (p->_left == first && first->_left == second) {
        //             first->_left = nullptr;
        //             if (more->_root == nullptr) {
        //                 more->_root = p;
        //                 Tx::_rotate_with_left_child<T>(more->_root);
        //                 more_end = more->_root->_left;   
        //             }
        //             else {
        //                 //typename BST<T>::Node *&temp *p;
        //                 Tx::_rotate_with_left_child<T>(p);
        //                 more_end->_left = p;
        //                 more_end = p;  
        //             }
        //             mid->_root = second;
        //             first = second;
        //             if (x < second->_data) second = second->_left;
        //             else second = second->_right;
        //         }
        //         else if (p->_right == first && first->_right == second) {
        //             first->_right = nullptr;
        //             if (less->_root == nullptr) {
        //                 less->_root = p;
        //                 Tx::_rotate_with_right_child<T>(less->_root);
        //                 less_end = less->_root->_right;
        //             }
        //             else {
        //                 //typename BST<T>::Node *&temp = BST<T>::_deep_copy(p);
        //                 Tx::_rotate_with_right_child<T>(p);
        //                 less_end->_right = p;
        //                 less_end = p;
        //             }
        //             mid->_root = second;
        //         }
        //         else if (c->_left == first && first->_right == second) {
        //             cout << "3" << endl;
        //             //cout << std::to_string(c->_left->_data) << endl;
        //             c->_left = nullptr;
        //             //cout << std::to_string(first->_data) << endl;
        //             if (more->_root == nullptr) {
        //                 cout << "in" << endl;
        //                 more->_root = c;
        //                 cout << to_string(more->_root->_data) << endl;
        //                 //more->_root->_left = nullptr;
        //                 more_end = c;
        //             }
        //             else {
        //                 //typename BST<T>::Node *&temp = BST<T>::_deep_copy<T>(p);
        //                 more_end->_left = p;
        //                 more_end = p;
        //             }
        //             mid->_root = first;
        //         }
        //         else if (p->_right == first && first->_left == second) {
        //             p->_right = nullptr;
        //             if (less->_root == nullptr) {
        //                 less->_root = p;
        //                 less_end = p;
        //             }
        //             else {
        //                 //typename BST<T>::Node *&temp = BST<T>::_deep_copy(p);
        //                 less_end->_right = p;
        //                 less_end = p;
        //             }
        //             mid->_root = first;
        //         }
        //         c = first;
        //         //cout << to_string(more->_root->_data) << endl;
        //         //is_root = false;
        //         first = second;
        //         if (second->_data < x) second = second->_right;
        //         else second = second->_left;
        //         cout << to_string(second->_data) << endl;
        //     }
        //     cout << "out" << endl;
        //     if (second == nullptr) {
        //         if (more->_root == nullptr && less->_root == nullptr) {
        //         if (p->_left == first) {
        //             //_rotate_with_left_child(first);
        //             Tx::_rotate_with_left_child<T>(p);
        //         }
        //         else {
        //            // _rotate_with_right_child(first);
        //             Tx::_rotate_with_right_child<T>(p);
        //         }
        //         }
        //         typename BST<T>::Node *&left = first->_left;
        //         typename BST<T>::Node *&right = first->_right;
        //         if (less->_root == nullptr) {
        //             less->_root = left;
        //         }
        //         else less_end->_right = left;
        //         if (more->_root == nullptr) more->_root = right;
        //         else more_end->_left = right;
        //         first->_left = less->_root;
        //         first->_right = more->_root;
        //     }
        //     // case where the loop doesnt get invoked (second is the data off rip)
        //     //cout <<"out" << endl;
        //     typename BST<T>::Node *&t1 = first;
        //     typename BST<T>::Node *&t2 = second;
        //     if (more->_root == nullptr && less->_root == nullptr) {
        //         //cout << "in" << endl;
        //         if (t1->_left == t2) {
        //             T old = t1->_data;
        //             Tx::_rotate_with_left_child<T>(t1);
        //             if (p->_left->_data == old) p->_left = t2;
        //             else p->_right = t2;
        //         }
        //         else {
                    
        //             T old = t1->_data;
        //             Tx::_rotate_with_right_child<T>(t1);
        //             if (p->_left->_data == old) p->_left = t2;
        //             else p->_right = t2;
        //         }
        //         if (p->_left == t2) {
        //             Tx:: _rotate_with_left_child<T>(p);
        //         } 
        //         else {
        //             Tx::_rotate_with_right_child<T>(p);
        //         }
        //         return;
        //     }
        //     typename BST<T>::Node *&left = second->_left;
        //     typename BST<T>::Node *&right = second->_right;
        //     if (less->_root == nullptr) {
        //         less->_root = left;
        //     }
        //     else less_end->_right = left;
        //     cout << std::to_string(less->_root->_data) << endl;
        //     if (more->_root == nullptr) more->_root = right;
        //     else more_end->_left = right;
        //     t2->_left = less->_root;
        //     t2->_right = more->_root;
            
        //     p = t2;
        //     delete less;
        //     delete more;
        //     delete mid;
        // }

    public:
        template <typename T> static const T &splay_find(BST<T> &tree, const T &x) {
            if (tree._root == nullptr) throw typename BST<T>::Not_found_exception();
            _splay<T>(tree._root, x);
            if (tree._root->_data == x) return tree._root->_data;
            throw typename BST<T>::Not_found_exception();
        }
        template <typename T> static bool splay_contains(BST<T> &tree, const T &x) {
            try {
                splay_find(tree,x);
            }
            catch(...) {
                return false;
            }
            return true;
        }
        template <typename T> static bool splay_insert(BST<T> &tree, const T &x) { 
            if (tree._root == nullptr){
                return tree.insert(x);
            }
            _splay<T>(tree._root,x);
            if (tree._root->_data == x) return false;
            typename BST<T>::Node *n = new typename BST<T>::Node(x);
            if (x > tree._root->_data) {
                n->_right = tree._root->_right;
                tree._root->_right = nullptr;
                n->_left = tree._root;
            }
            else {
                n->_left = tree._root->_left;
                tree._root->_left = nullptr;
                n->_right = tree._root;
            }
            tree._root = n;
            tree._size++;
            return true;
        }
        template <typename T> static bool splay_remove(BST<T> &tree, const T &x) { 
            if (tree._root == nullptr) return false;
            _splay<T>(tree._root,x);
            if (tree._root->_data != x) return false;
            if (tree._root->_left == nullptr) {
                tree._root = tree._root->_right;
                tree._size--;
                return true;
            }
            _splay<T>(tree._root->_left,x);

            tree._root->_left->_right = tree._root->_right;
            tree._root = tree._root->_left;
            tree._size--;
            return true; 
        }

        friend class Tests;
};

// template <typename T> void Tx::_rotate_with_left_child(typename BST<T>::Node *&p) {
//     typename BST<T>::Node *&left = p->_left;
//     typename BST<T>::Node *&right = left->_right;
//     p->_left = right;
//     left->_right = p;
// }

#endif /* Tree_Algorithms_h */