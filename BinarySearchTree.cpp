#include "BinarySearchTree.h"
#include <iostream>
#include <string>
using namespace std;
BinarySearchTree::BinarySearchTree()
{
    root=NULL; //Initialize root to null
}
void BinarySearchTree::insert(string& a,node* n) //Inserts a new node to its right place
{
    if (a.compare(n->word.word)>=0) //If string is bigger than the node
    {
        if (n->right == NULL) //If right child is empty then insert the new string
        {
            n->right= new node;
            n->right->word.word=a; //Insert word
            n->right->word.freq=1; //Initialize its frequency to 1
            n->right->left=NULL; //Initialize node's child to null
            n->right->right=NULL; //Initialize node's child to null
            n->right->parent=n; //Make n his parent
        }
        else
            insert(a,n->right); //Otherwise go check the right child
    }
    else //If string is smaller than the node
    {
        if (n->left==NULL) //If left child is empty then insert the new string
        {
            n->left= new node;
            n->left->word.word=a; //Insert word
            n->left->word.freq=1; //Initialize its frequency to 1
            n->left->left=NULL; //Initialize node's child to null
            n->left->right=NULL; //Initialize node's child to null
            n->left->parent=n; //Make n his parent
        }
        else //Otherwise go to the left child
            insert(a,n->left);
    }
}
void BinarySearchTree::insert(string& a)
{
    if (search(a)==NULL) //If word doesn't exist in tree
    {
        if (root==NULL) //If tree is empty then insert in root
        {
            root= new node;
            root->word.word=a;
            root->word.freq=1;
            root->left=NULL;
            root->right=NULL;
            root->parent=NULL;
        }
        else
            insert(a,root); //Otherwise go to children
    }
    else
    {
        search(a)->word.freq++; //If word already exists then increase frequency by one
    }

}


node* BinarySearchTree::search(string &a,node* n)
{
    if (n==NULL)
        return NULL; //If node is null then return
    if (a.compare(n->word.word)==0) //if string is same as the node's then return node
        return n;
    else if (a.compare(n->word.word)<0) //if string is smaller
        return search(a,n->left); //Go to left child
    else //if string is bigger
        return search(a,n->right); //Go to right child
}
node* BinarySearchTree::search(string& a)
{
    return search(a,root); //Returns the node with this word
}
void BinarySearchTree::DeleteNode(node *n)
{
    node *parent=n->parent; //Create a new node which stores deleted node's parent
    if (n->left==NULL && n->right==NULL) //Node has no child
    {
        if (parent==NULL) //If node is root
        {
            delete(n); //Delete node
            root=NULL; //And make root to null
        }
        else if (parent->left==n) //If node is at the left side
        {
            delete (parent->left); //Delete node
            parent->left=NULL; //And change the pointer to null
        }
        else //If node is at the right side
        {
            delete(parent->right); //Delete node
            parent->right=NULL; //And change the pointer to null
        }
    }
    else if (n->left==NULL || n->right==NULL) //If node has one child
    {
        if (parent==NULL) //if node is root
        {
            if (n->left==NULL) //If left child is empty
                root=n->right; //Move right child to root's place
            else //If right child is empty
                root=n->left; //Move left child to root's place
            delete(n); //delete root
        }
        else if (parent->left==n) //If node is at the left side
        {
            if (n->left==NULL) //If node's left child is empty
                parent->left=n->right; //Move right child to node's place
            else //If node's right child is empty
                parent->left=n->left; //Move left child to node's place
            delete(n); //delete node
        }
        else //If node is at the right side
        {
            if (n->left==NULL) //If node's left child is empty
                parent->right=n->right; //Move right child to node's place
            else //If node's right child is empty
                parent->right=n->left; //Move left child to node's place
            delete(n); //delete node
        }
    }
    else //If node has two children
    {
        node *min=findMin(n->right); //Find node of right side with minimum value
        n->word=min->word; //Replace values
        DeleteNode(min); //Delete minimum
    }
}
void BinarySearchTree::DeleteNode(string& a)
{
    node *n=search(a); //Search the node with the desirable string
    if (n!=NULL) //If a node with that string was found
        DeleteNode(n); //Call the Delete function
    //else do nothing
}
void BinarySearchTree::DeleteTree(node *n)
{
    if (n!=NULL) //If node exists
    {
        DeleteTree(n->left); //Delete the left subtree
        DeleteTree(n->right); //Delete the right subtree
        delete n; //Delete the current node
    }
}
void BinarySearchTree::DeleteTree()
{
    DeleteTree(root); //Start the Delete from root
}


void BinarySearchTree::PrintPreorder(node* n)
{
    if (n!=NULL) //If node exists
    {
        cout<<n->word.word<<" - "<<n->word.freq<<endl; //Print the current node
        PrintPreorder(n->left); //First go to left subtree
        PrintPreorder(n->right); //And then to the right subtree
    }
}
void BinarySearchTree::PrintPreorder()
{
    PrintPreorder(root); //Start from root
}
void BinarySearchTree::PrintInorder(node* n)
{
    if (n!=NULL) //If root exists
    {
        PrintInorder(n->left); //Start from left subtree
        cout<<n->word.word<<" - "<<n->word.freq<<endl; //Print the current node
        PrintInorder(n->right); //And then go to the right subtree
    }
}
void BinarySearchTree::PrintInorder()
{
    PrintInorder(root); //Start from root
}
void BinarySearchTree::PrintPostorder(node* n)
{
    if (n!=NULL) //If root exists
    {
        PrintPostorder(n->left); //Start with left subtree
        PrintPostorder(n->right); //Then go to right subtree
        cout<<n->word.word<<" - "<<n->word.freq<<endl; //And then print current node
    }
}
void BinarySearchTree::PrintPostorder()
{
    PrintPostorder(root); //Start from root
}

int BinarySearchTree::getCount(string& a)
{
    return search(a)->word.freq; //Return the node's-that has been returned by the search-frequency
}
node *BinarySearchTree::findMin()
{
    return findMin(root);//Start from the root
}
node *BinarySearchTree::findMin(node* n)
{
    while (n->left!=NULL) //Go as far as left goes
    {
        n=n->left;
    }
    return n; //Return the leftmost node
}
node *BinarySearchTree::findMax()
{
    return findMax(root); //Start from root
}
node *BinarySearchTree::findMax(node* n)
{
    while (n->right!=NULL) //Go as far as right goes
    {
        n=n->right;
    }
    return n; //Return the rightmost node
}
