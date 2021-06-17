#ifndef DoubleHashing_h
#define DoubleHashing_h
#include <string>
#include "moreTools.h"
using namespace std;
class Hash
{
private:
    value *data;
    int capacity; //Size of HashTable
    int size; //Size of words
    float load_factor; //Load factor size/capacity
public:
    unsigned long hashkey(const char*,int); //Linear Hashing with djb2 algorithm
    //Constructor
    Hash(); //Initial size of HashTable:1000
    //Other Functions
    void insert(string); //insert word in hashtable
    int HashSearch(string); //returns the position of a word
    void checkRehash(); //Checks if load_factor>0.5
    int getSize(); //returns the number of words in HashTable
    int getFreq(int); //Returns the frequency of a word
    string operator[](int); //Returns word in that position
    //Friendly operators
    friend ostream& operator<<(ostream&,Hash&);
};
//Operators
ostream& operator<<(ostream&,Hash&);
#endif
