#include "Avltree.h"
#include <iostream>
#include <string>

using namespace std;

Avltree::Avltree()  //empty constructor
{
    root=NULL; //sets root to NULL
}

node* Avltree::insert(string & s, node* n)
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
            getheight(n->right); //sets height to 1;
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
            getheight(n->left);
        }
        else
            n->left=insert(s, n->left); //if it's not, check the left child
    }
    
    int balance=getBalance(n); //updates balance
    //cout<<n->word.word<<" - "<<balance<<endl;
    //cases if node is unbalanced
    if(balance>1 && s < n->left->word.word)//s.compare(n->word.word)<0) //left rotate
        return rightRotate(n);
    if(balance<-1 && s > n->right->word.word)//s.compare(n->word.word)>=0) //right rotate
        return leftRotate(n);
    if(balance>1 && s > n->left->word.word)//s.compare(n->word.word)>=0) //left right rotate
    {
        n->left=leftRotate(n->left);
        return rightRotate(n);
    }
    if (balance<-1 && s < n->right->word.word)//s.compare(n->word.word)<0)//right left rotate
    {
        n->right=rightRotate(n->right);
        return leftRotate(n);
    } 
    
    return n; //if balanced return unchanged node
}

void Avltree::insert(string & s)
{
    if (search(s)==NULL)
    {
        if (root==NULL)
        {
          //  node* n=new node; //creates new node;
            root=new node;
            root->word.word=s; //sets word of the node to s
            root->word.freq=1; //sets frequency to 1
            root->left=NULL; //sets left child to NULL
            root->right=NULL; //sets right child to NULL
            root->parent=NULL;
            getheight(root); //sets height of the tree
        }
        else
            insert(s, root);
    }
    else
        search(s)->word.freq++;
}

node* Avltree::search(string & s, node* n)
{
    if (n==NULL) //if it is a NULL node return NULL
        return NULL;
    if (s.compare(n->word.word)==0) //if string and node are the same return node
        return n;
    if (s.compare(n->word.word)<0) //if string is smaller alphabetically go to left child
        return search (s, n->left);
    return search (s, n->right); //if string is bigger alphabetically go to left child

}
node* Avltree::search(string & s)
{
    return search(s, root); //returns the node that contains this word
}

void Avltree::deleteNode (node* n)
{
    node* par=n->parent; //new node that stores deleted node's parent
    if (n->left==NULL && n->right==NULL)//if the node has no children
    {
        if (par==NULL) //if node is root
        {
            delete(n); //delete node
            root=NULL; //make node NULL
        }
        else if (par->left==n) //if the node is on the left side
        {
            delete (par->left); //delete node
            par->left=NULL; //set pointer to NULL
        }
        else //if the node is on the right side
        {
            delete (par->right); //delete node
            par->right=NULL; //set pointer to NULL
        }
    }
    else if (n->left==NULL || n->right==NULL) //if the node has only one child
    {
        if (par==NULL) //if node is root
        {
            if (n->left==NULL) //if left child is empty
                root=n->left; //move right child to root
            else //if right child is empty
                root=n->right; //move left child to root
            delete(n); //delete node
        }
        else if (par->left==n) //if node is on the left side
        {
            if (n->left==NULL) //if left child is empty
                par->left=n->right;// move right child to node
            else //if right child is empty
                par->left=n->left; //move left child to node
            delete(n); //delete node
        }
        else //if node is on the right side
        {
            if (n->left==NULL) //if left child is empty
                par->right=n->right; //move right child to node
            else //if right child is empty
                par->right=n->left; //move left child to node
            delete(n); //delete node
        }
    }
    else //if node has two children
    {
        node *min=findMin(n->right); //find node with minimum value on right side
        n->word=min->word; //replace node's value with minimum
        deleteNode(min); //delete minimum
    }

    int balance=getBalance(root); //updates balance
    cout<<balance<<endl;
    //cases if node is unbalanced
    if(balance>1)
    {
        if (getBalance(root->left)>=0)
            rightRotate(root);
        else
        {
            root->left=leftRotate(root->left);
            rightRotate(root);
        }
    }
    if (balance<-1)
    {
        if (getBalance(root->right)<=0)
            leftRotate(root);
        else
        {
            root->right=rightRotate(root->right);
            leftRotate(root);
        }
    }
}

void Avltree::deleteNode (string & s)
{
    node *n=search(s); //find the node with the s string
    if (n!=NULL) //if the node is found
        deleteNode(n); //call deleteNode function
}

void Avltree::deleteTree (node* n)
{
    if (n!=NULL) //if the node exists
    {
        deleteTree(n->left); //delete left subtree
        deleteTree(n->right); //delete right subtree
        delete n; //delete node n
    }
}
void Avltree::deleteTree ()
{
    deleteTree(root); //call deleteTree function for root
}

void Avltree::preorder (node* n, ostream &o)
{
    if(n!=NULL) //if node exists
    {
        o<<n->word.word<<" - "<<n->word.freq<<endl; //print current node's word and frequency
        preorder(n->left, o); //go to left subtree
        preorder(n->right, o); //then go to right subtree
    }
}
void Avltree::preorder (ostream &o)
{
    preorder(root, o); //start peorder from root
}

void Avltree::inorder (node* n, ostream &o)
{
    if(n!=NULL) //if node exists
    {
        preorder(n->left, o); //first go to left subtree
        o<<n->word.word<<" - "<<n->word.freq<<endl; //print current node's word and frequency
        preorder(n->right, o); //then go to right subtree
    }
}
void Avltree::inorder (ostream &o)
{
    inorder(root, o); //start inorder from root
}

void Avltree::postorder (node* n,  ostream &o)
{
    if(n!=NULL) //if node exists
    {    
        preorder(n->left, o); //first go to left subtree
        preorder(n->right, o); //then go to right subtree
        o<<n->word.word<<" - "<<n->word.freq<<endl; //print current node's word and frequency
    }
}
void Avltree::postorder (ostream &o)
{
    postorder(root, o); //start postorder from root
}

node* Avltree::findMin(node* n)
{
    while (n->left!=NULL) //go to furthest left node
        n=n->left;
    return n; //return smallest node
}
node* Avltree::findMin()
{
    return findMin(root); //start from root
}

node* Avltree::findMax(node* n)
{
    while (n->right!=NULL) //go to furthest right node
        n=n->right;
    return n; //return biggest node
}
node* Avltree::findMax()
{
    return findMax(root);//start from root
}

int Avltree::getFreq(string & s)
{
    return search(s)->word.freq; //return frequency of node with the string
}
int Avltree::getNodeFreq(node* n)
{
    return n->word.freq; //return frequency of the node
}

int max(int a, int b)
{
    return (a>b)?a:b;
}

node* Avltree::leftRotate(node* n)
{
    if (n==root)
       { 
           //cout<<"Root changed from "<<root->word.word<<" to "<<n->right->word.word<<endl;
           root=n->right;
        }
    node *t=n->right;
    node *t2=t->left;

    t->left=n;
    n->right=t2;

    return t;
}

node* Avltree::rightRotate(node* n)
{
    if (n==root)
        {
            //cout<<"Root changed from "<<root->word.word<<" to "<<n->left->word.word<<endl;
            root=n->left;
        }
    node *t=n->left;
    node *t2=t->right;

    t->right=n;
    n->left=t2;

    return t;
}

int Avltree::getheight(node* n)
{
    if (n==NULL)
        return 0;
    int left=0, right=0;
    left=1+getheight(n->left);
    right=1+getheight(n->right);
    return left>right?left:right;
}
int Avltree::getheight()
{
    return getheight(root);
}

int Avltree::getBalance(node* n)
{
    if(n!=NULL)//if node exists
        return (getheight(n->left)-getheight(n->right));
    return 0;
}
int Avltree::getBalance()
{
    return getBalance(root); //get balance from root
}
