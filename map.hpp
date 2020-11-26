//
//  map.hpp
//  AVL-tree
//
//  Created by Артём Lazemir on 19.11.2020.
//

#ifndef map_hpp
#define map_hpp

template<typename keyT, typename valT>
class map {
protected:
    struct node {
        std::pair<const keyT, valT> data;
        node* left;
        node* right;
        node* parent;
        int height;
        
        node(std::pair<const keyT, valT> d, node* parent = nullptr, node* left = nullptr, node* right = nullptr) : data(d) {
            this->parent = parent;
            this->left = left;
            this->right = right;
        }
    };
    
    node* root;
    
    size_t _size;
    
public:
    class iterator {
    private:
        node* current;
        
    public:
        iterator(node* branch) {
            current = branch;
        }
        
        iterator() : current(nullptr) {};
        
        iterator operator++() {
            if (!current->right) {
                if (current->parent) {
                    if(current->parent->left == current) {
                        current = current->parent;
                    } else {
                        while (current->parent->right == current) {
                            current = current->parent;
                            if (!current->parent) {
                                current = nullptr;
                                return *this;
                            }
                        }
                        current = current->parent;
                    }
                } else {
                    current = nullptr;
                }
            } else {
                current = current->right;
                while(current) {
                    if (!current->left) {
                        break;
                    }
                    current = current->left;
                }
            }
            return *this;
        }
        
        bool operator!=(const iterator& rv) {
            return (current != rv.current);
        }
        
        std::pair<const keyT, valT>& operator*() {return current->data;};
        
        std::pair<const keyT, valT>* operator->() {return &current->data;}
    };
    
    virtual pair<iterator, bool> insert(pair<keyT, valT> element) = 0;
    
    virtual valT& operator[](keyT key) = 0;
    
    virtual iterator find(keyT key) = 0;

    virtual size_t erase(keyT key) = 0;
    
    virtual size_t size() = 0;
    
    virtual void clear() = 0;
    
    virtual bool contains(keyT key) = 0;

    iterator begin() {return iterator(root);}
    
    iterator end() {return nullptr;}
};


#endif /* map_hpp */
