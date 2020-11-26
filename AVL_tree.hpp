//
//  AVL_tree.hpp
//  AVL-tree
//
//  Created by Артём Lazemir on 19.11.2020.
//

#ifndef AVL_tree_hpp
#define AVL_tree_hpp

using std::max;
using std::pair;

#include "map.hpp"

template<typename keyT, typename valT>
class map_AVL : public map<keyT, valT> {
    typedef typename map<keyT, valT>::iterator iterator;
    typedef typename map<keyT, valT>::node node;
private:
    node* root;
    
    size_t _size;
    
    
    int height(node* branch) {
        return (branch ? branch->height : 0);
    }
    
    int getBalance(node* branch) {
        if(!branch)
            return 0;
        else
            return height(branch->left) - height(branch->right);
    }

    void singleLeftRotate(node*& branch) {
        node* u = branch->right;
        node* parent_temp = branch->parent;
        branch->right = u->left;
        u->left = branch;
        branch->height = max(height(branch->left), height(branch->right)) + 1;
        u->height = max(height(branch->right), branch->height) + 1 ;
        branch = u;
        branch->parent = parent_temp;
        branch->left->parent = branch;
    }
    
    void singleRightRotate(node*& branch) {
        node* u = branch->left;
        node* parent_temp = branch->parent;
        branch->left = u->right;
        u->right = branch;
        branch->height = max(height(branch->left), height(branch->right)) + 1;
        u->height = max(height(u->left), branch->height) + 1;
        branch = u;
        branch->parent = parent_temp;
        branch->right->parent = branch;
    }

    void doubleLeftRotate(node*& branch) {
        singleRightRotate(branch->right);
        singleLeftRotate(branch);
    }

    void doubleRightRotate(node*& branch) {
        singleLeftRotate(branch->left);
        singleRightRotate(branch);
    }

    void del(node* branch) {
        if(branch) {
            del(branch->left);
            del(branch->right);
            delete branch;
        }
    }

    pair<iterator, bool> insert(std::pair<const keyT, valT> element, node*& branch, node* parent = nullptr) {
        pair<iterator, bool> res;
        if(!branch) {
            branch = new node(element);
            branch->height = 1;
            branch->left = branch->right = nullptr;
            branch->parent = parent;
            
            res = std::make_pair(iterator(branch), true);
        }
        
        else if(element.first < branch->data.first) {
            res = insert(element, branch->left, branch);
            
            if(height(branch->left) - height(branch->right) == 2) {
                if(element < branch->left->data) {
                    singleRightRotate(branch);
                } else {
                    doubleRightRotate(branch);
                }
            }
        } else if(element.first > branch->data.first) {
            res = insert(element, branch->right, branch);
            
            if(height(branch->right) - height(branch->left) == 2)
            {
                if(element.first > branch->right->data.first) {
                    singleLeftRotate(branch);
                } else {
                    doubleLeftRotate(branch);
                }
            }
        } else {
            res = std::make_pair(iterator(branch), false);
        }

        branch->height = max(height(branch->left), height(branch->right)) + 1;
        return res;
    }

    node* findMin(node* branch) {
        if(!branch)
            return nullptr;
        else if(!branch->left)
            return branch;
        else
            return findMin(branch->left);
    }

    node* findMax(node* branch) {
        if(!branch)
            return nullptr;
        else if(!branch->right)
            return branch;
        else
            return findMax(branch->right);
    }

    size_t erase(keyT key, node*& branch) {
        size_t dec_size = 0;
        node* temp;

        // Element not found
        if(!branch)
            return 0;

        // Searching for element
        else if(key < branch->data.first)
            dec_size += erase(key, branch->left);
        else if(key > branch->data.first)
            dec_size += erase(key, branch->right);

        // Element found
        // With 2 children
        else if(branch->left && branch->right) {
            temp = branch;
            branch = new node(findMin(temp->right)->data, temp->parent, temp->left, temp->right);
            if (branch->left) {
                branch->left->parent = branch;
            }
            delete temp;
            erase(branch->data.first, branch->right);
        }
        // With one or zero child
        else {
            temp = branch;
            if(!branch->left) {
                branch = branch->right;
            } else {
                branch = branch->left;
            }
            if (branch) {
                branch->parent = temp->parent;
                delete temp;
            }
        }
        
        if(!branch)
            return 1;

        branch->height = max(height(branch->left), height(branch->right)) + 1;

        // If node is unbalanced
        // If left node is deleted, right case
        if(height(branch->left) - height(branch->right) == 2) {
            // right right case
            if(height(branch->left->left) - height(branch->left->right) == 1)
                singleLeftRotate(branch);
            // right left case
            else
                doubleLeftRotate(branch);
        }
        // If right node is deleted, left case
        else if(height(branch->right) - height(branch->left) == 2)
        {
            // left left case
            if(height(branch->right->right) - height(branch->right->left) == 1)
                singleRightRotate(branch);
            // left right case
            else
                doubleRightRotate(branch);
        }
        
        return dec_size;
    }
    
    iterator find(keyT key, node* branch) {
        if (key < branch->data.first) {
            return find(key, branch->left);
        } else if(key > branch->data.first) {
            return find(key, branch->right);
        } else {
            return iterator(branch);
        }
    }

public:
    map_AVL() {
        root = nullptr;
        _size = 0;
    }
    
    ~map_AVL() {del(root);}

    pair<iterator, bool> insert(pair<keyT, valT> element) {
        auto p = insert(element, root);
        if (p.second) {
            ++_size;
        }
        return insert(element, root);
    }
    
    valT& operator[](keyT key) {return insert(std::make_pair(key, valT())).first->second;}
    
    iterator find(keyT key) {return find(key, root);}

    size_t erase(keyT key) {
        size_t dec_size = erase(key, root);
        _size -= dec_size;
        return dec_size;
    }
    
    size_t size() {return _size;}

    iterator begin() {return iterator(findMin(root));}
    
    iterator end() {return nullptr;}
    
    void clear() {
        del(root);
        root = nullptr;
        _size = 0;
    }
    
    bool contains(keyT key) {return find(key, root) != end();}
};


#endif /* AVL_tree_hpp */
