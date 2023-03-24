#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value> 
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
		void clear_helper(Node<Key, Value> *curr);
		int balanced_helper(Node<Key, Value> *curr, int val) const;
		bool balanced_helper2(Node<Key, Value> *curr) const;


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
		current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
		current_ = NULL;
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
		if(&(this->current_->getItem()) == &(rhs.current_->getItem())) {
			return true;
		}
		return false;
}
 
/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
		if(&(this->current_->getItem()) != &(rhs.current_->getItem())) {
			return true;
		}
		return false;
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // // TODO

    if(this->current_->getRight() != NULL) {
		this->current_ = this->current_->getRight();
		bool isDone = false;
		while(!isDone) {
			if(this->current_->getLeft() != NULL) {
				this->current_ = this->current_->getLeft(); 
			}
			else {
				isDone = true;
				return *this;
			}
		}
	}
	else {
		Node<Key, Value>* parent = this->current_->getParent();
		// while(parent != NULL) {
		// 	// if the parent node is the first instance of being a right child
		// 	// Node<Key, Value>* parent_parent = parent->getParent();
		// 	if(parent->getParent()->getLeft() == parent) {
		// 		this->current_ = parent->getParent();
        //         return *this;
		// 	}
		// 	else {
		// 		parent = parent->getParent();
		// 	}
		// }
        while(parent != NULL && this->current_ == parent->getRight()) {
            this->current_ = parent;
            parent = parent->getParent();
        }
        this->current_ = parent;
        return *this;
	}
	// there is no predecessor
	return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
		root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
		clear();

}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
		Node<Key, Value>* duplicates = internalFind(keyValuePair.first);
		// if there is a duplicate, replace the value
		if(duplicates != NULL) {
			duplicates->setValue(keyValuePair.second);
		}
		// if root is NULL, then insert a new node with keyValuePair's variables to root
		else if(root_ == NULL) {
			Node<Key, Value>* temp = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
			root_ = temp; 
		}
		// otherwise, create a new Node with keyValuePair's variables and insert into the BST
		else {
			Node<Key, Value>* temp = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
			Node<Key, Value>* parent = root_;
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
		}
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
		Node<Key, Value>* current = internalFind(key);
		
		// if there are no nodes, do nothing
		if(current == NULL) {
			return;
		}
		// if there are two children
		if(current->getRight() != NULL && current->getLeft() != NULL) {
			Node<Key, Value>* pred = predecessor(current);
			nodeSwap(current, pred);
		}
		// if there are no children
		if(current->getLeft() == NULL && current->getRight() == NULL) {
			if(current == root_) {
				root_ = NULL;
			}
			else if(current->getParent()->getLeft() == current) {
				current->getParent()->setLeft(NULL);
			}
			else {
				current->getParent()->setRight(NULL);
			}
			delete current;
			current = nullptr;
			return;
		}
		// one child, promote the child to current spot
		else if(current->getLeft() != NULL && current->getRight() == NULL) {
			current->getLeft()->setParent(current->getParent());
			if(current == root_) {
				root_ = current->getLeft();
			}
			else if(current->getParent()->getRight() == current) {
				current->getParent()->setRight(current->getLeft());
			}
			else {
				current->getParent()->setLeft(current->getLeft());
			}
			delete current;
			current = nullptr;
			return;
		}
		else if(current->getRight() != NULL && current->getLeft() == NULL) {
			current->getRight()->setParent(current->getParent());
			if(current == root_) {
				root_ = current->getRight();
			}
			else if(current->getParent()->getRight() == current) {
				current->getParent()->setRight(current->getRight());
			}
			else {
				current->getParent()->setLeft(current->getRight());
			}
			delete current;
			current = nullptr;
			return;
		}
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
		if(current->getLeft() != NULL) {
			current = current->getLeft();
			bool isDone = false;
			while(!isDone) {
				if(current->getRight() != NULL) {
					current = current->getRight(); 
				}
				else {
					isDone = true;
					return current;
				}
			}
		}
		else {
			Node<Key, Value>* parent = current->getParent();
			while(parent != NULL) {
				// checks if the parent is a right child
				if(parent->getParent()->getRight() == parent) {
					return parent->getParent();
				}
				else {
					parent = parent->getParent();
				}
			}
			// while(parent != NULL) {
			// 	// if the parent node is the first instance of being a right child
			// 	Node<Key, Value>* parent_parent = parent->getParent();
			// 	if(parent_parent->getRight() == parent) {
			// 		return parent_parent;
			// 	}
			// 	else {
			// 		parent = parent_parent;
			// 	}
			// }
		}
		// there is no predecessor
		return NULL;
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
		clear_helper(root_);
		root_ = NULL;
}


// helper function for clear that uses recursion
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear_helper(Node<Key, Value> *curr) {
	if(curr != NULL) {
		clear_helper(curr->getLeft());
		clear_helper(curr->getRight());
		delete curr;
	}
}



/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
		Node<Key, Value>* current = root_;
		while(current->getLeft()) {
			current = current->getLeft();
		}
		return current;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
		Node<Key, Value>* current = root_;

		while(current != NULL) {
			if(current->getKey() == key) {
				return current;
			}
			else if(current->getKey() > key) {
				current = current->getLeft();
			}
			else if(current->getKey() < key) {
				current = current->getRight();
			}
			
		}
		return NULL;
}





/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
	if(root_ == NULL) {
		return true;
	}
	if((root_->getLeft() == NULL && root_->getRight() == NULL) || (root_->getLeft() == NULL && balanced_helper(root_->getRight(), 0) == 0) || (root_->getLeft() == NULL && balanced_helper(root_->getLeft(), 0) == 0)) {
    return true;
  }
	if(balanced_helper2(root_) && balanced_helper2(root_->getLeft()) && balanced_helper2(root_->getRight())) {
		return true;
	}
	return false;
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::balanced_helper2(Node<Key, Value> *curr) const {
		int left = balanced_helper(curr->getLeft(), 0);
		int right = balanced_helper(curr->getRight(), 0);
		if(left - right == 1 || left - right == 0 || right - left == 1 || right - left == 0) {
			return true;
		}
		return false;
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::balanced_helper(Node<Key, Value> *curr, int val) const {
		if(curr == NULL) {
        return val-1;
    }
    // recursive call to balanced_helper
    int left = balanced_helper(curr->getLeft(), val+1);
    int right = balanced_helper(curr->getRight(), val+1);
    if(left >= right) {
        return left;
    }
    return right;
}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer
   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif