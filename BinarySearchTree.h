#ifndef BinarySearchTree_h
#define BinarySearchTree_h
#include <iostream>
#include <string>
#include "Struct Value.h"
using namespace std;
struct node
{
    value word; //A word with his frequency
    node* left; //Left child
    node* right; //Right child
    node* parent; //Parent
};

class BinarySearchTree
{
private:
    node *root; //Root Pointer
    void insert(string&,node*); //Inserts a new node to its right place
    node* search(string&,node*);//Searches for a node with that string
    void PrintPreorder(node*,ostream&); //Prints in preorder traversal
    void PrintInorder(node *,ostream&); //Prints in inorder traversal
    void PrintPostorder(node *,ostream&); //Prints in postorder traversal
    void DeleteNode(node *); //Delete Node from tree
    void DeleteTree(node *); //Delete entire tree
    node *findMin(node*); //Find node with minimum word(ASCII Value)
    node *findMax(node*); //Find node with maximum word(ASCII Value)

public:
    //Constructors
    BinarySearchTree(); //Initialize the root ptr to NULL
    //Destructors
    ~BinarySearchTree();
    //Other functions/ User-friendly versions
    void insert(string&); //Create a new node with this string
    void DeleteNode(string&); //Delete Node from tree
    void DeleteTree(); //Delete entire tree
    node* search(string&);//Returns the node with this string
    void PrintPreorder(ostream&); //Prints in preorder traversal/accepts an output stream
    void PrintInorder(ostream&); //Prints in inorder traversal/accepts an output stream
    void PrintPostorder(ostream&); //Prints in postorder traversal/accepts an output stream
    int getCount(string&); //Returns the frequency of a string
    node *findMin(); //Find node with minimum word(ASCII Value)
    node *findMax(); //Find node with maximum word(ASCII Value)
    int getFreq(node*); //Returns the frequency of a node
};
#endif
