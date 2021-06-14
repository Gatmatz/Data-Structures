#ifndef avltree_h
#define avltree_h
#include <iostream>
#include <string>
#include "struct_value.h"

using namespace std;

struct node
{
    value word; //word and its frequency
    node* left; //left child
    node* right; //right child
    node* parent; //parent
    //int height;// height of the tree
};

class Avltree
{
private:
    node* root; // root pointer

    node* insert(string &, node*); //inserts new node
    node* search(string &, node*); //searches for node with string
    void deleteNode (node*); //deletes node
    void deleteTree (node*); //deletes entire tree

    int getheight(node*);

    void preorder (node*, ostream&); //prints tree in preorder
    void inorder (node*, ostream&); //prints tree in inorder
    void postorder (node*, ostream&); //prints tree in postorder

    node* findMin(node*); //finds node with minimum word alphabeticallly
    node* findMax(node*); //finds node with maximum word alphabeticallly
    int getBalance(node*); //returns balance of node
    
public:
    Avltree(); //empty constructor

    int getheight(); //returns the hight of the tree
    
    void insert(string &); //creates new node including string
    node* search(string &); //searches for node with string
    void deleteNode (string &); //deletes node
    void deleteTree (); //deletes entire tree

    void preorder (ostream&); //prints tree in preorder
    void inorder (ostream&); //prints tree in inorder
    void postorder (ostream&); //prints tree in postorder

    node* findMin(); //finds node with minimum word alphabeticallly
    node* findMax(); //finds node with maximum word alphabeticallly

    int getFreq(string &); //returns frequency of string
    int getNodeFreq(node*); //returns frequency of node

    node* leftRotate(node*); //left rotates subtree
    node* rightRotate(node*); //right rotates subtree
    node* leftrightRotate(node*); //left right
    node* rightleftRotate(node*); //right left

    int getBalance(); //returns balance of node
};

#endif