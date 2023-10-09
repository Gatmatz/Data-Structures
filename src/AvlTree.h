#ifndef AvlTree_h
#define AvlTree_h
#include <iostream>
#include <string>
#include "moreTools.h"

using namespace std;

class AvlTree
{
private:
    node* root; // root pointer

    node* insert(string &, node*); //inserts new node
    node* search(string &, node*); //searches for node with string
    void deleteNode (node*); //Sets the frequency of the word to zero
    void deleteTree (node*); //deletes entire tree

    int getHeight(node*);

    void preorder (node*, ostream&); //prints tree in preorder
    void inorder (node*, ostream&); //prints tree in inorder
    void postorder (node*, ostream&); //prints tree in postorder

    node* findMin(node*); //finds node with minimum word alphabetically
    node* findMax(node*); //finds node with maximum word alphabetically
    int getBalance(node*); //returns balance of node

public:
    AvlTree(); //empty constructor

    int getHeight(); //returns the hight of the tree

    void insert(string &); //creates new node including string
    node* search(string &); //searches for node with string
    void deleteNode (string &); //deletes node
    void deleteTree (); //deletes entire tree

    void preorder (ostream&); //prints tree in preorder
    void inorder (ostream&); //prints tree in inorder
    void postorder (ostream&); //prints tree in postorder

    node* findMin(); //finds node with minimum word alphabetically
    node* findMax(); //finds node with maximum word alphabetically

    int getFreq(string &); //returns frequency of string
    int getNodeFreq(node*); //returns frequency of node

    node* leftRotate(node*); //left rotates subtree
    node* rightRotate(node*); //right rotates subtree

    int getBalance(); //returns balance of node
};

#endif
