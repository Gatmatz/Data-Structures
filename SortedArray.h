#ifndef sortedarray_h
#define sortedarray_h
#include <iostream>
#include <cstring>
#include <fstream>
#include "moreTools.h"

using namespace std;

//Sorted array structure. Accepts words and number of appearances for each word and stores them alphabetically.
//Supports: add/delete element and search for element

class SortedArray
{
protected:
    value *arr; //array with words and frequencies
    int size; //size of array
    int R; //number of reallocks that have been made

public:
    SortedArray(); //empty constructor
    ~SortedArray(); //destructor

    int search(string); //Returns the position of the word in the array, -1 else using binary search
    void insert(string); //Inserts word in array
    void deleteArr(string); //Deletes word from array
    void print(ostream&); //Prints all words in the array and their frequency alphabetically
    int getSize(); //returns size of array
    int getFreq(int); //returns frequency of word

    friend ostream& operator<< (ostream&, SortedArray&); //friendly operator <<
};

ostream& operator<<(ostream&, SortedArray&); //operator << overload; prints all words with their frequency


#endif
