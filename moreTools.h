#ifndef STRUCT_VALUE_H
#define STRUCT_VALUE_H
#include <cstring>
#include <iostream>
using namespace std;

typedef struct value
{
    string word; //word
    int freq; //Frequency of the word
} value;

typedef struct node
{
    value word; //word and its frequency
    node* left; //left child
    node* right; //right child
    node* parent; //parent
} node;

#endif
