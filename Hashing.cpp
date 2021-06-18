#include "Hashing.h"
#include <iostream>
#include <string>
#define PRIME 5381
using namespace std;
//Constructor
Hash::Hash()
{
    size=0; //Initialize to 0 words
    capacity=1000; //Initialize HashTable to 1000 words
    data=new value[capacity]; //Initialization of HashTable
    int i;
    for (i=0;i<1000;i++)
    {
        data[i].word=".";
        data[i].freq=-1;
    }
    load_factor=(float)(size/capacity); //load_factor=0
}
//Destructor
Hash::~Hash()
{
    delete[] data;
}
//Find index of string
unsigned long Hash::hashkey(string& a,int capacity)
{
    unsigned long index = PRIME; //Prime is 5381 (Seems to have fewer collisions)
    for (int i=0;i<a.size();i++)
    {
        index+=index*33 +a[i]; //Evaluate the sum of hash*33 plus every character in string
    }
    return index%capacity; //Evaluate the hash key for the string and return it
}
//Other Functions
int Hash::HashSearch(string key)
{
    int pos=hashkey(key,capacity); //Find the start position
    while (data[pos].word!=".") //Until it finds an empty spot
    {
        if (data[pos].word==key) //Search the positions
            return pos;
        pos=(pos+1)%capacity;
    }
    return -1; //If not found return -1
}
void Hash::insert(string a)
{
    int pos=HashSearch(a); //Get the position of word
    int index;
    if (pos==-1) //if the word doesn't already exists in array
    {
        index=hashkey(a,capacity); //Get the right position of the inserted word
        while (data[index].word!=".") //Find free space
        {
            index=(index+1)%capacity;
        }
        if (data[index].word==".") //If it finds then inserts the word
        {
            size++;
            data[index].word=a;
            data[index].freq=1;
        }
        load_factor=((float)(size)/capacity); //Update the load factor
        checkRehash(); //Checks if HashTable needs rehashing
    }
    else //If the word already exists in HashTable
    {
        data[pos].freq++; //Increase the frequency by one
    }
}
void Hash::checkRehash()
{
    int i;
    if (load_factor>=0.5)
    {
        int newcap=2*capacity; //Variable that keeps the doubled capacity
        //Make a new HashTable with double the size
        int index;
        value *temp;
        temp=new value[newcap];
        //Initialize all positions to "."
        for (i=0;i<newcap;i++)
        {
            temp[i].word=".";
            temp[i].freq=-1;
        }
        size=0;
        //Rehash with the new capacity
        for (i=0;i<capacity;i++)
        {
            if (data[i].word!=".")
            {
                size++;
                index=hashkey(data[i].word,newcap);
                while (temp[index].word!=".")
                {
                    index=(index+1)%(2*capacity);
                }
                temp[index].word=data[i].word;
                temp[index].freq=data[i].freq;
            }

        }
        delete[] data;
        capacity*=2;
        data=temp;
        load_factor=(float)(size/capacity); //Update the load_factor
    }
}
int Hash::getSize()
{
    return size; //Returns the number of words
}
int Hash::getFreq(int pos) //Returns the frequency of a word
{
    return data[pos].freq;
}
string Hash::operator[](int pos) //Returns word in that position
{
    return data[pos].word;
}
ostream& operator<<(ostream& mystream,Hash& A)
{
    //Prints all words in HashTable
    for(int i=0;i<A.capacity;i++)
    {
        if (A.data[i].word!=".")
            mystream<<A.data[i].word<<"-"<<A.data[i].freq<<endl;
    }
    return mystream;
}
