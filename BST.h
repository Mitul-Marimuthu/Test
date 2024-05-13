// student id: 20538991

#include <iostream>
#include <sstream>
//#include <vector>

#ifndef BST_h 
#define BST_h

using namespace std;

template <typename T>
class BST {
    private: // change
        struct Node {
            T _data;
            Node *_left, *_right;
            Node(const T &d = T(), Node *l = nullptr, Node *r = nullptr): _data(d), _left(l), _right(r) {}
        };
        Node *_root;
        size_t _size;

        //helpers
        static Node *_deep_copy(const Node *p) {
            if (p == nullptr) return nullptr;
            Node *n = new Node;
            n->_data = p->_data;
            n->_left = _deep_copy(p->_left);
            n->_right = _deep_copy(p->_right);
            return n;
            //return copy;
        }
        bool _insert(Node *&p, const T &elem) {
            if (_root == nullptr) {
                //Node n(elem);
                _root = new Node;
                _root->_data = elem;
                _size++;
                return true;
            }
            if (p->_data > elem && p->_left == nullptr) {
                //Node n(elem);
                p->_left = new Node;
                p->_left->_data = elem;
                _size++;
                return true;
            }
            if (p->_data > elem) return _insert(p->_left, elem);
            if (p->_data < elem && p->_right == nullptr) {
                p->_right = new Node;
                p->_right->_data = elem;
                _size++;
                return true;
            }
            if (p->_data < elem) return _insert(p->_right, elem);
            return false;
        }
        Node *&_get_root() { return _root; }
        bool _insert_pointer(Node *&p) {
            if (_root == nullptr) {
                _root = p;
                _size++;
                return true;
            }
            if (p == nullptr) return false;
            Node *curr = _root;
            while (true) {
                if (p->_data < curr->_data) {
                    if (curr->_left == nullptr) {
                        //Node *&t = curr;
                        curr->_left = p;
                        _size++;
                        break;
                    }
                    curr = curr->_left;
                }
                else if (p->_data > curr->_data) {
                    if (curr->_right == nullptr) {
                        //Node *&t = curr;
                        curr->_right = p;
                        break;
                    }
                    curr = curr->_right;
                }
                else {
                    return false;
                }
            }
            return true;
        }
        bool _remove(Node *&p, const T &elem) {
            Node *dell = _find(p, elem);
            if (dell == nullptr) return false;
            //dell->_data = elem;
            //const Node *min = _find_min(dell->_right);
            //Node *temp = const_cast<Node*>(min);
            Node *parent = _get_parent(p, elem);
            if (dell->_left == nullptr && dell->_right == nullptr) {
                if (parent == nullptr) p = nullptr;
                else if (parent->_left == dell) parent->_left = nullptr;
                else {parent->_right = nullptr;}
                delete dell;
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
            }
            else if (dell->_right == nullptr) {
                if (parent == nullptr)
                    p = dell->_left;
                else if (parent->_left == dell) parent->_left = dell->_left;
                else parent->_right = dell->_left;
                //delete dell;
            }
            else {
                const Node *temp = _find_min(dell->_right);
                dell->_data = temp->_data;
                _size++;
                _remove(dell->_right, temp->_data);
            }
            // if (min == nullptr) dell = dell->_left;
            // else dell = temp;
            _size--;
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
        bool _recursive_delete(Node *&p) { 
            if (p == nullptr) { delete p; return false; }
            if (p->_left == nullptr && p->_right == nullptr) {
                p = nullptr;
                delete p;
                _size--;
                return true;
            }
            if (p->_left != nullptr) _recursive_delete(p->_left);
            if (p->_right != nullptr) _recursive_delete(p->_right);
            p = nullptr;
            delete p;
            _size--;
            return true;
        }

        const Node *_find_min(Node *p) const {
            if (p == nullptr) return nullptr;
            Node *temp = p;
            while (temp->_left != nullptr)
                temp = temp->_left;
            return temp;
        }
       Node *_find(Node *p, const T &elem) const {
            if (p == nullptr) return nullptr;
            if (p->_data == elem) return p;
            
            if (p->_data < elem) {
                if (p->_right == nullptr) return nullptr;
                return _find(p->_right, elem);
            }

            if (p->_left == nullptr) return nullptr;
            return _find(p->_left, elem);
        }

        string _to_string(const Node *p) const { 
            if (p == nullptr) return "";
            if (p->_left == nullptr && p->_right == nullptr) return "";
            stringstream ret;
            ret << "" << p->_data << " : ";
            if (p->_left != nullptr)
                ret << p->_left->_data; 
            else   
                ret << "[null]";
            ret << " "; 
            if (p->_right != nullptr) 
                ret << p->_right->_data ;
            else 
                ret << "[null]";
            ret << "\n";
            ret << _to_string(p->_left) << _to_string(p->_right);
            return ret.str();
        }
    
    public:
        BST() : _root(nullptr), _size(0) {}
        virtual ~BST() { _recursive_delete(_root); }

        virtual size_t get_size() const { return _size; }

        virtual bool insert(const T &elem) { return _insert(_root, elem); }
        virtual bool remove(const T &elem) { return _remove(_root, elem); }
        virtual bool clear() { return _recursive_delete(_root); }

        virtual bool contains(const T &elem) const {
            return _find(_root, elem) != nullptr; 
        }
        virtual T &find(const T &elem) const { 
            Node *n = _find(_root, elem);
            if (n == nullptr) throw Not_found_exception();
            return n->_data;
        }
        virtual string to_string() const { 
            stringstream ret;
            if (_root == nullptr) return "[NULL]";
            ret << "# Tree rooted at " << _root->_data << "\n";
            ret << "# size = " << _size << "\n";
            ret << _to_string(_root);
            ret << "#End of tree";
            return ret.str();
        }
        
        class Not_found_exception : public exception {
            public:
                string to_string() { return "Not found exception"; }
        };

        friend class Tests;
        friend class Tx;
};


#endif /* BST_h */