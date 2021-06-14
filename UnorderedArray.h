#ifndef UnorderedArray_h
#define UnorderedArray_h
#include <iostream>
#include <cstring>
#include <fstream>
#include "Struct Value.h"
using namespace std;

class UnorderedArray
{
private:
    value *Words; //Array with words and its frequencies
    int size; //Size of Array
    int Rfactor; //Variable that stores the number of Reallocs that have been made
public:
    //Constructor
    UnorderedArray();
    //Destructor
    ~UnorderedArray();
    //Functions
    int serialSearch(string); //Returns -1 if not found, otherwise the position of the word in array
    void insert(string); //Insert a word that hasn't been in array
    void Delete(string); //Delete a word from the array
    void show(ostream&); //Print out all words of array with their frequency
    int getSize(); //Returns the size of the Array
    int getFreq(int); //Returs the frequency of a word

    //Friendly operators
    friend ostream& operator<<(ostream&,UnorderedArray&);
};
//Operators
ostream& operator<<(ostream&,UnorderedArray&); //Prints out all words with their frequency
#endif
