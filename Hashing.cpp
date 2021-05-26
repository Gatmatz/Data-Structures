#include "Hashing.h"
#include <iostream>
#include <string>
#include <cmath>
#define PRIME 31
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
    load_factor=(float)(size/capacity); //load-factor=0
}
//Find index of string
int Hash::hashkey(string a,int capacity)
{
    int i;
    long int sum=0;
    for (i=0;i<a.size();i++)
    {
        sum+=a[i]*PRIME;
    }
    sum%=capacity;
    return sum;
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
void Hash::insert(string &a)
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
        //Make a new HashTable with double the size
        int index;
        value *temp;
        temp=new value[2*capacity];
        //Initialize all positions to "."
        for (i=0;i<2*capacity;i++)
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
                index=hashkey(data[i].word,2*capacity);
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
        data=new value[capacity];
        for (i=0;i<capacity;i++)
        {
            data[i]=temp[i];
        }
        delete[] temp;
        load_factor=(float)(size/capacity); //Update the load_factor
    }
}
int Hash::getSize()
{
    return size; //Returns the number of words
}

ostream& operator<<(ostream& mystream,Hash& A)
{
    //Prints all words in HashTable
    for(int i=0;i<A.capacity;i++)
    {
        if (A.data[i].word!=".")
            cout<<A.data[i].word<<"-"<<A.data[i].freq<<endl;
    }
}