#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)


#endif


#include "equal-paths.h"
using namespace std;




// You may add any prototypes of helper functions here


// helper function that finds the furthest path length that the node goes
int path_length(Node* curr, int val) {
    if(curr == nullptr) {
        return val-1;
    }
    // recursive call to path_length
    int left = path_length(curr->left, val+1);
    int right = path_length(curr->right, val+1);
    if(left >= right) {
        return left;
    }
    return right;


}


// returns true if the tree has equal paths and false otherwise
bool equalPaths(Node * root)
{
    // returns true if the tree is empty
    if(root == nullptr) {
        return true;
    }
    // returns true if the left node is null and the right node doesn't have a child or the right node is null and the left node doens't have a child
    if((root->left == nullptr && path_length(root->right, 0) == 0) || (root->right == nullptr && path_length(root->left, 0) == 0)) {
        return true;
    }
    // returns true if the left node's path_length is equal to the right node's path_length
    if(path_length(root->left, 0) == path_length(root->right, 0)) {
        return true;
    }
    return false;


}


