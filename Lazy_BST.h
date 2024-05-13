//student id: 20538991

#include <iostream>
#include <stack>
#include <sstream>
#ifndef Lazy_BST_h
#define Lazy_BST_h

using namespace std;

template <typename T>
class Lazy_BST {
    protected:
        struct Node {
            T _data;
            Node *_left, *_right;
            bool _is_deleted;

            Node(const T &d =T()): _data (d), _left(nullptr), _right(nullptr), _is_deleted(false) {}
        };

        Node *_root;
        size_t _size, _real_size;

        bool _recursive_delete(Node *&p) { 
            if (p == nullptr) { delete p; return false; }
            if (p->_left == nullptr && p->_right == nullptr) {
                p = nullptr;
                delete p;
                _size--;
                _real_size--;
                return true;
            }
            if (p->_left != nullptr) _recursive_delete(p->_left);
            if (p->_right != nullptr) _recursive_delete(p->_right);
            p = nullptr;
            delete p;
            _real_size--;
            _size--;
            return true; 
        }
        bool _insert(Node *&p, const T &elem) { 
            if (_root == nullptr) {
                _root = new Node;
                _root->_data = elem;
                _size++;
                _real_size++;
                return true;
            }
            //if (p->_is_deleted){p->_is_deleted = false; _size++; }
            if (p->_data == elem) { if (p->_is_deleted) { p->_is_deleted = false; _size++; return true;} return false;} 
            if (p->_data > elem && p->_left == nullptr) {
                Node n(elem);
                p->_left = new Node;
                p->_left->_data = elem;
                _size++;
                _real_size++;
                return true;
            }
            if (p->_data > elem) return _insert(p->_left, elem);
            if (p->_data < elem && p->_right == nullptr) {
                p->_right = new Node;
                p->_right->_data = elem;
                _size++;
                _real_size++;
                return true;
            }
            if (p->_data < elem) return _insert(p->_right, elem);
            return false; 
        }
        bool _remove(Node *&p, const T &elem) {
            if (p == nullptr) return false;
            if (p->_data == elem) {
                if (p->_is_deleted) { return false; }
                p->_is_deleted = true; 
                _size--; 
                return true; 
            }
            else if (p->_data < elem) return _remove(p->_right, elem);
            return _remove(p->_left, elem); 
        }
        bool _collect_garbage(Node *&p) { 
            if (p == nullptr) return false;
            bool b1 = _collect_garbage(p->_left);
            bool b2 = _collect_garbage(p->_right);
            if (p->_is_deleted) return _really_remove(_root, p->_data);
            return b1 || b2;
        }

        const Node *_find_min(const Node *p) const {
            if (p == nullptr) return nullptr;
            if (!p->_is_deleted && !check_existing(p->_left)) return p;

            if (!p->_is_deleted) {
                bool left = check_existing(p->_left); // check if existing elements on left
                if (left)
                    return _find_min(p->_left);
                else return p;
            }
            // if p is deleted and there exists elements on the left
            // if (check_existing(p->_left)) return _find_min(p->_left);
            // return _find_min(p->_right);
            const Node *left = _find_min(p->_left);
            const Node *right = _find_min(p->_right);

            if (left != nullptr && right != nullptr) {
                return left->_data < right->_data ? left : right;
            }
            else if (left != nullptr) return left;
            return right;
        }
        // checks if there are any existing nodes left in the subtree. 
        bool check_existing(const Node *p) const {
            if (p == nullptr) return false;
            if (!p->_is_deleted) return true;
            return check_existing(p->_left) || check_existing(p->_right);
        }

       
        const Node *_find(const Node *p, const T &elem) const { 
            if (p == nullptr) return nullptr;
           // if (p->_is_deleted) { p->_is_deleted = false; _size++; }
            if (p->_data == elem) { 
                if (!p->_is_deleted) return p; 
                return nullptr;
            }
            
            if (p->_data < elem) {
                if (p->_right == nullptr) return nullptr;
                return _find(p->_right, elem);
            }

            if (p->_left == nullptr) return nullptr;
            return _find(p->_left, elem);
        }

        const Node *_find_real_min(const Node *p) const { 
            if (p == nullptr) return nullptr;
            if (p->_left == nullptr) return p;
            return _find_real_min(p->_left);
        }
        // find but doesn't care about deletions
        Node *_finder(Node *p, const T &elem) const {
            if (p == nullptr) return nullptr;
            if (p->_data == elem) return p;
            
            if (p->_data < elem) {
                if (p->_right == nullptr) return nullptr;
                return _finder(p->_right, elem);
            }

            if (p->_left == nullptr) return nullptr;
            return _finder(p->_left, elem);
        }
        bool _really_remove(Node *&p, const T &elem) { 
            Node *dell = _finder(p, elem);
            if (dell == nullptr) return false;
            //dell->_data = elem;
            //const Node *min = _find_min(dell->_right);
            //Node *temp = const_cast<Node*>(min);
            Node *parent = _get_parent(p, elem);
            if (dell->_left == nullptr && dell->_right == nullptr) {
                if (parent == nullptr) p = nullptr;
                else if (parent->_left == dell) parent->_left = nullptr;
                else {parent->_right = nullptr;}
                if (!dell->_is_deleted) _size--;
                delete dell;
                //_size--;
                _real_size--;
                return true;
            }
            else if (dell->_left == nullptr) {
                if (parent == nullptr) {
                    p = dell->_right;
                }
                else if (parent->_left == dell) {
                    parent->_left = dell->_right;
                }
                else 
                    parent->_right = dell->_right;
                //delete dell;
                if (!dell->_is_deleted) _size--;
                _real_size--;
                return true;
                //return true;
            }
            else if (dell->_right == nullptr) {
                if (parent == nullptr)
                    p = dell->_left;
                else if (parent->_left == dell) parent->_left = dell->_left;
                else parent->_right = dell->_left;
                if (!dell->_is_deleted) _size--;
                _real_size--;
                return true;
                //delete dell;
                //return true;
            }
            else {
                const Node *temp = _find_real_min(dell->_right);
                dell->_data = temp->_data;
                if (!dell->_is_deleted) _size--;
                dell->_is_deleted = temp->_is_deleted;
                //_real_size--;
                _really_remove(dell->_right, temp->_data);
                //_size--;
                //_real_size--;
            }
            // if (min == nullptr) dell = dell->_left;
            // else dell = temp;
            
            return true;
        }
        // precondition: elem exists in the tree
        Node *_get_parent(Node *&p, const T &elem) {
            //if (_root->_data == p->_data) return _root;
            if (p == nullptr) return nullptr;
            if (p->_data == elem) return nullptr;
            if (p->_left != nullptr && p->_left->_data == elem) return p;
            if (p->_right != nullptr && p->_right->_data == elem) return p;
            if (p->_data > elem && p->_left != nullptr) return _get_parent(p->_left, elem);
            if (p->_right != nullptr) return _get_parent(p->_right, elem);
            return nullptr;
        }
        
        string _to_string(const Node *p) const { 
            if (p == nullptr) return "[null]";
            if (p->_left == nullptr && p->_right == nullptr) return "";
            stringstream ret;
            ret << "" << p->_data;
            if (p->_is_deleted) ret << "*"; 
            ret << " : ";
            ret << _to_string(p->_left);
            if (p->_left != nullptr && p->_left->_is_deleted) ret << "*";
            ret << _to_string(p->_right);
            if (p->_right != nullptr && p->_right->_is_deleted) ret << "*";
            ret << "\n";
            return ret.str();
        }

    public:
        Lazy_BST(): _root(nullptr), _size(0), _real_size(0) {}
        ~Lazy_BST() { _recursive_delete(_root); }

        size_t get_size() const { return _size; }
        size_t get_real_size() const { return _real_size; }
        bool insert(const T &elem) { return _insert(_root, elem); }
        bool remove (const T &elem) { return _remove(_root, elem); }
        bool collect_garbage() { return _collect_garbage(_root); }
        bool contains(const T &elem) const {
            return _find(_root, elem) != nullptr; 
        }
        const T &find(const T &elem) const { 
            const Node *n = _find(_root, elem);
            if (n == nullptr) throw Not_found_exception();
            return n->_data;
        }
        string to_string() const { 
            stringstream ret;
            if (_root == nullptr) return "[NULL]";
            ret << "# Tree rooted at " << _root->_data << "\n";
            ret << "# size = " << _size << "\n";
            ret << _to_string(_root);
            ret << "#End of tree";
            return ret.str();
        }
        bool clear() { return _recursive_delete(_root);  }

        class Not_found_exception : public exception {
            public:
                string what() { return "Element not found exception"; }
        };
        friend class Tests;
};

//Gangaram - the grateful gator
#endif /* Lazy_BST_h */