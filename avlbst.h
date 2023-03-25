#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void insertFix(AVLNode<Key,Value>* parent, AVLNode<Key,Value>* current);
    void rotateRight(AVLNode<Key, Value>* parent);
    void rotateLeft(AVLNode<Key, Value>* parent);
    void removeFix(AVLNode<Key,Value>* parent, int diff);

};



/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */

template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO

    AVLNode<Key, Value>* duplicates = static_cast<AVLNode<Key, Value>*>(this->internalFind(new_item.first));
	// if there is a duplicate, replace the value
	if(duplicates != NULL) {
        // std::cout << "HAS DUPE" << std::endl;
		duplicates->setValue(new_item.second);
	}
	// if root is NULL, then insert a new node with new_item's variables to root
	else if(this->root_ == NULL) {
		AVLNode<Key, Value>* temp = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
		this->root_ = temp; 
        return;
	}
	// otherwise, create a new Node with new_item's variables and insert into the BST
	else {
		AVLNode<Key, Value>* temp = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
		AVLNode<Key, Value>* parent = static_cast<AVLNode<Key, Value>*>(this->root_);
		bool isDone = false;
		while(!isDone) {
			// if the current key value is less than the root's key value
			if(temp->getKey() < parent->getKey()) {
				// if parent node's left child is NULL, then sets it to the new value
				if(parent->getLeft() == NULL) {
					temp->setParent(parent);
					parent->setLeft(temp);  
					isDone = true; 
				}
				// if the parent's left child is not NULL, then continues down the BST
				else {
					parent = parent->getLeft();
				}
			}
			// if the current key value is greater than  the root's key value
			else if(temp->getKey() > parent->getKey()) {
				// if parent node's right child is NULL, then sets it to the new value
				if(parent->getRight() == NULL) {
					temp->setParent(parent);
					parent->setRight(temp);  
					isDone = true; 
				}
				// if the parent's right child is not NULL, then continues down the BST
				else {
					parent = parent->getRight();
				}
			}
		}
        // sets the balance
        if(parent->getBalance() == 1 || parent->getBalance() == -1) {
            parent->setBalance(0);
            return;
        }
        else {
            if(parent->getLeft() != NULL && parent->getRight() == NULL) {
                parent->setBalance(-1);
            }
            else if(parent->getRight() != NULL && parent->getLeft() == NULL) {
                parent->setBalance(1);
            }
            insertFix(parent, temp);
        }
	}
}



template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key,Value>* parent, AVLNode<Key,Value>* current) {
    if(parent->getParent() == NULL || parent == NULL) {
        return;
    }
    AVLNode<Key, Value>* grandparent = parent->getParent();
    // if the child is a left child of the parent's parent
    if(parent == grandparent->getLeft()) {
        grandparent->updateBalance(-1);
        // case 1
        if(grandparent->getBalance() == 0) {
            // std::cout << "case 1" << std::endl;
            return;
        }
        // case 2
        else if(grandparent->getBalance() == -1) {
            // std::cout << "case 2" << std::endl;
            insertFix(grandparent, parent);
        }
        // std::cout << "case 3" << std::endl;
        else if(grandparent->getBalance() == -2) {
            // zig-zig left case
            if(current == parent->getLeft()) {
                parent->setBalance(0);
                grandparent->setBalance(0);
                rotateRight(grandparent);
            }
            // zig-zag case
            else {
                rotateLeft(parent);
                rotateRight(grandparent);
                if(current->getBalance() == 0) {
                    parent->setBalance(0);
                    grandparent->setBalance(0);

                } 
                else if(current->getBalance() == -1) {
                    parent->setBalance(0);
                    grandparent->setBalance(1);

                } 
                else if(current->getBalance() == 1) {
                    parent->setBalance(-1);
                    grandparent->setBalance(0);
                }
                current->setBalance(0);
            }
        }
    }
    else if(parent == grandparent->getRight()) {
        grandparent->updateBalance(1);
        // case 1
        if(grandparent->getBalance() == 0) {
            // std::cout << "case 1" << std::endl;
            return;
        }
        // case 2
        else if(grandparent->getBalance() == 1) {
            // std::cout << "case 2" << std::endl;
            insertFix(grandparent, parent);
        }
        // std::cout << "case 3" << std::endl;
        else if(grandparent->getBalance() == 2) {
            // zig-zig right case
            if(current == parent->getRight()) {
                parent->setBalance(0);
                grandparent->setBalance(0);
                rotateLeft(grandparent);
            }
            else {
                rotateRight(parent);
                rotateLeft(grandparent);
                if(current->getBalance() == 0) {
                    parent->setBalance(0);
                    grandparent->setBalance(0);

                } 
                else if(current->getBalance() == -1) {
                    parent->setBalance(1);
                    grandparent->setBalance(0);

                } 
                else if(current->getBalance() == 1){
                    parent->setBalance(0);
                    grandparent->setBalance(-1);
                }
                current->setBalance(0);
            }
        }   
    }
}



template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* parent) {
    AVLNode<Key, Value>* grandparent = parent->getParent();
    AVLNode<Key, Value>* childL = parent->getLeft();
    AVLNode<Key, Value>* childLR = childL->getRight();

    childL->setParent(grandparent);
    if (parent->getParent() == NULL) {        
        this->root_ = childL;
        childL->setRight(parent);
        parent->setParent(childL);
        parent->setLeft(childLR);
    }
    else if (parent == grandparent->getRight()){
        grandparent->setRight(childL);
        childL->setRight(parent);
        parent->setParent(childL);
        parent->setLeft(childLR);
    }
    else if(parent == grandparent->getLeft()){
        grandparent->setLeft(childL);
        childL->setRight(parent);
        parent->setParent(childL);
        parent->setLeft(childLR);
    }    
    if (childLR != NULL){
        childLR->setParent(parent);
    }

}




template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* parent) {
    AVLNode<Key, Value>* grandparent = parent->getParent();
    AVLNode<Key, Value>* childR = parent->getRight();
    AVLNode<Key, Value>* childRL = childR->getLeft();
    childR->setParent(grandparent);

    //set the root parent
    if (parent->getParent() == NULL) {        
        this->root_ = parent->getRight();
        childR->setLeft(parent);
        parent->setParent(childR);
        parent->setRight(childRL);
    }
    else if (parent == grandparent->getRight()){
        grandparent->setRight(childR);
        childR->setLeft(parent);
        parent->setParent(childR);
        parent->setRight(childRL);
    }
    else if(parent == grandparent->getLeft()){
        grandparent->setLeft(childR);
        childR->setLeft(parent);
        parent->setParent(childR);
        parent->setRight(childRL);
    }    
    if (childRL != NULL){
        childRL->setParent(parent);
    }
    
}

template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
	AVLNode<Key, Value>* current = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
		
	// if there are no nodes, do nothing
	if(current == NULL) {
		return;
	}
	// if there are two children
	if(current->getRight() != NULL && current->getLeft() != NULL) {
		AVLNode<Key, Value>* success = static_cast<AVLNode<Key, Value>*>(this->successor(current));
		nodeSwap(current, success);
	}
    AVLNode<Key, Value>* p = current->getParent();
    AVLNode<Key, Value>* c = current->getLeft();

    if(current->getRight() != NULL) {
        c = current->getRight();
    }
    if(current->getLeft() != NULL) {
        c = current->getLeft();
    }
    if(c != NULL) {
        c->setParent(p);
    }

    int diff;
    if(p != NULL) {
        if(p->getLeft() == current) {
            p->setLeft(c);
            diff = 1;
        }
        else if(p->getRight() == current) {
            p->setRight(c);
            diff = -1;
        }
    }
    else {
        this->root_ = c;
    }

    if(current == this->root_) {
        this->root_ = NULL;
        return;
    }


	
	delete current;
	current = nullptr;
    removeFix(p, diff);

}


template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key,Value>* current, int diff) {
    if(current == NULL) {
        return;
    }

    AVLNode<Key, Value>* parent = current->getParent();
    int ndiff = -1;
    if(parent != NULL) {
        ndiff = 1;
    }
    else {
        ndiff = -1;
    }

    // case 1
    if(current->getBalance() + diff == -2) {
        AVLNode<Key, Value>* child = current->getLeft();
        // case 1a
        if(child->getBalance() == -1) {
            rotateRight(current);
            current->setBalance(0);
            child->setBalance(0);
            removeFix(parent, ndiff);
        }
        // case 1b
        else if(child->getBalance() == 0) {
            rotateRight(current);
            current->setBalance(-1);
            child->setBalance(1);
            return;
        // case 1c
        }
        else if(child->getBalance() == 1) {
            AVLNode<Key, Value>* g = child->getRight();
            rotateLeft(child);
            rotateRight(current);
            if(g->getBalance() == 1) {
                current->setBalance(0);
                child->setBalance(-1);
                g->setBalance(0);
            }
            else if(g->getBalance() == 0) {
                current->setBalance(0);
                child->setBalance(0);
                g->setBalance(0);
            }
            else if(g->getBalance() == -1) {
                current->setBalance(1);
                child->setBalance(0);
                g->setBalance(0);
            }
        }
    }
    else if(current->getBalance() + diff == 2) {
        AVLNode<Key, Value>* child = current->getRight();
        // case 1a
        if(child->getBalance() == 1) {
            rotateLeft(current);
            current->setBalance(0);
            child->setBalance(0);
            removeFix(parent, ndiff);
        }
        // case 1b
        else if(child->getBalance() == 0) {
            rotateLeft(current);
            current->setBalance(1);
            child->setBalance(-1);
            return;
        // case 1c
        }
        else if(child->getBalance() == -1) {
            AVLNode<Key, Value>* g = child->getLeft();
            rotateRight(child);
            rotateLeft(current);
            if(g->getBalance() == -1) {
                current->setBalance(0);
                child->setBalance(1);
                g->setBalance(0);
            }
            else if(g->getBalance() == 0) {
                current->setBalance(0);
                child->setBalance(0);
                g->setBalance(0);
            }
            else if(g->getBalance() == 1) {
                current->setBalance(-1);
                child->setBalance(0);
                g->setBalance(0);
            }
        }
    }
    // case 2
    else if(current->getBalance() + diff == -1) {
        current->setBalance(-1);
    }
    else if(current->getBalance() + diff == 0) {
        removeFix(parent, ndiff);
    }

}


template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}



#endif