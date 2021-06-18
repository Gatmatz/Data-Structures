#include "AvlTree.h"
#include <iostream>
#include <string>

using namespace std;

AvlTree::AvlTree()  //empty constructor
{
    root=NULL; //sets root to NULL
}

node* AvlTree::insert(string & s, node* n)
{
    if (s.compare(n->word.word)>=0) //checks if the string s is bigger than the node
    {
        if (n->right==NULL) //if right child is empty
        {
            n->right=new node; //creates new node
            n->right->word.word=s; //inserts word s
            n->right->word.freq=1; //sets frequency to 1
            n->right->left=NULL; //sets left child to NULL
            n->right->right=NULL; //sets right child to NULL
            n->right->parent=n; //makes n its parent
            //getHeight(n->right); //sets height to 1;
        }
        else
            n->right=insert(s, n->right); //if it's not, check the right child
    }
    else //if it's smaller than the node
    {
        if (n->left==NULL) //if left child is empty
        {
            n->left=new node; //creates new node
            n->left->word.word=s; //inserts word s
            n->left->word.freq=1; //sets frequency to 1
            n->left->right=NULL; //sets left child to NULL
            n->left->left=NULL; //sets right child to NULL
            n->left->parent=n; //makes n its parent
            getHeight(n->left);
        }
        else
            n->left=insert(s, n->left); //if it's not, check the left child
    }

    int balance=getBalance(n); //updates balance
    //cases if node is unbalanced
    if(balance>1 && s < n->left->word.word) //left rotate
        return rightRotate(n);
    if(balance<-1 && s > n->right->word.word) //right rotate
        return leftRotate(n);
    if(balance>1 && s > n->left->word.word) //left right rotate
    {
        n->left=leftRotate(n->left);
        return rightRotate(n);
    }
    if (balance<-1 && s < n->right->word.word) //right left rotate
    {
        n->right=rightRotate(n->right);
        return leftRotate(n);
    }

    return n; //if balanced return unchanged node
}

void AvlTree::insert(string & s)
{
    if (search(s)==NULL) //If word hasn't been inserted
    {
        if (root==NULL) //If the tree is empty
        {
            root=new node; //Create a new root
            root->word.word=s; //sets word of the node to s
            root->word.freq=1; //sets frequency to 1
            root->left=NULL; //sets left child to NULL
            root->right=NULL; //sets right child to NULL
            root->parent=NULL; //sets parent to NULL
            getHeight(root); //sets height of the tree
        }
        else
            insert(s, root); //Call the private insert starting from root
    }
    else //If word has been inserted
        search(s)->word.freq++; //Increase the frequency by one
}

node* AvlTree::search(string & s, node* n)
{
    if (n==NULL) //if it is a NULL node return NULL
        return NULL;
    if (s.compare(n->word.word)==0) //if string and node are the same return node
        return n;
    if (s.compare(n->word.word)<0) //if string is smaller alphabetically go to left child
        return search (s, n->left);
    return search (s, n->right); //if string is bigger alphabetically go to right child

}
node* AvlTree::search(string & s)
{
    return search(s, root); //returns the node that contains this word
}

void AvlTree::deleteNode (node* n)
{
    n->word.freq=0; //Consider a deleted node, a node with zero frequency
}

void AvlTree::deleteNode (string & s)
{
    if (root!=NULL && search(s)) //if the node is found
    {
        deleteNode(search(s)); //call deleteNode function
    }
}

void AvlTree::deleteTree (node* n)
{
    if (n!=NULL) //if the node exists
    {
        deleteTree(n->left); //delete left subtree
        deleteTree(n->right); //delete right subtree
        delete n; //delete node n
    }
}
void AvlTree::deleteTree ()
{
    deleteTree(root); //call deleteTree function for root
}

void AvlTree::preorder (node* n, ostream &o)
{
    if(n!=NULL) //if node exists
    {
        if (n->word.freq!=0) //If a node is "deleted" then don't show it
            o<<n->word.word<<" - "<<n->word.freq<<endl; //print current node's word and frequency
        preorder(n->left, o); //go to left subtree
        preorder(n->right, o); //then go to right subtree
    }
}
void AvlTree::preorder (ostream &o)
{
    preorder(root, o); //start peorder from root
}

void AvlTree::inorder (node* n, ostream &o)
{
    if(n!=NULL) //if node exists
    {
        inorder(n->left, o); //first go to left subtree
        if (n->word.freq!=0) //If a node is "deleted" then don't show it
            o<<n->word.word<<" - "<<n->word.freq<<endl; //print current node's word and frequency
        inorder(n->right, o); //then go to right subtree
    }
}
void AvlTree::inorder (ostream &o)
{
    inorder(root, o); //start inorder from root
}

void AvlTree::postorder (node* n,  ostream &o)
{
    if(n!=NULL) //if node exists
    {
        postorder(n->left, o); //first go to left subtree
        postorder(n->right, o); //then go to right subtree
        if (n->word.freq!=0) //If a node is "deleted" then don't show it
            o<<n->word.word<<" - "<<n->word.freq<<endl; //print current node's word and frequency
    }
}
void AvlTree::postorder (ostream &o)
{
    postorder(root, o); //start postorder from root
}

node* AvlTree::findMin(node* n)
{
    while (n->left!=NULL) //go to furthest left node
        n=n->left;
    return n; //return smallest node

}
node* AvlTree::findMin()
{
    return findMin(root); //start from root
}

node* AvlTree::findMax(node* n)
{
    while (n->right!=NULL) //go to furthest right node
        n=n->right;
    return n; //return biggest node
}
node* AvlTree::findMax()
{
    return findMax(root);//start from root
}

int AvlTree::getFreq(string & s)
{
    return search(s)->word.freq; //return frequency of node with the string
}
int AvlTree::getNodeFreq(node* n)
{
    return n->word.freq; //return frequency of the node
}

node* AvlTree::leftRotate(node* n) //Simple Left Rotation
{
    if (n==root) //check if root rotates
    {
        root=n->right; //set right child to root
    }
    node *t=n->right; //helping nodes
    node *t2=t->left; 

    t->left=n; //perform left rotation
    n->right=t2;

    return t; //return new root of rotation
}

node* AvlTree::rightRotate(node* n) //Simple Right Rotation
{
    if (n==root) //check if root rotates
    {
        root=n->left; //set left child to root
    }
    node *t=n->left; //helping nodes
    node *t2=t->right;

    t->right=n; //perform right rotation
    n->left=t2;

    return t; //return new root of rotation
}

int AvlTree::getHeight(node* n)
{
    if (n==NULL)
        return 0;
    int left=0, right=0; //Initialize 2 variables for two children
    left=1+getHeight(n->left); //Plus 1 for current node
    right=1+getHeight(n->right); //Plus 1 for current node
    return left>right?left:right; //Find and return the maximum of two children
}
int AvlTree::getHeight()
{
    return getHeight(root); //start from root
}

int AvlTree::getBalance(node* n)
{
    if(n!=NULL)//if node exists
        return (getHeight(n->left)-getHeight(n->right)); //return the difference between two children
    return 0;
}
int AvlTree::getBalance()
{
    return getBalance(root); //get balance from root
}
