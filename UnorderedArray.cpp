#include "UnorderedArray.h"
#include <cstring>
#include <iostream>
using namespace std;
//Constructor
UnorderedArray::UnorderedArray()
{
    Words=NULL; //Initialize struct pointer to NULL
    size=0; //Size of words is 0
    Rfactor=0; //Zero reallocations
}
//Functions
int UnorderedArray::serialSearch(string &a)
{
    int i,pos=-1; //Pos is the position of the word a in array
    for (i=0;i<size;i++) //Cross all elements of array
    {
        if (a==Words[i].word) //Check if found
        {
            pos=i; //Keep the position
            break; //Get out of the loop
        }
    }
    return pos; //returns -1 if not found, otherwise the position of word

}
void UnorderedArray::insert(string &a)
{
    int pos=serialSearch(a);
    value *tmp;
    if (pos==-1) //if the word doesn't already exists in array
    {
        if (Words==NULL) //First word
        {
            Words=new value[size+1000]; //Initialize size to 1000
            size++;
            Words[size-1].word=a;
            Words[size-1].freq=1;
            Rfactor=1; //First reallocation
        }
        else
        {
            if (size>=Rfactor*1000) //Realloc every 1000 words
            {
                //Realloc Array- increase by 1000
                tmp=new value [size+1000];
                for (int i=0;i<size;i++)
                {
                    tmp[i]=Words[i];
                }
                delete[] Words;
                Words=tmp;

                Words[size].word=a;
                Words[size].freq=1;
                size++;
                Rfactor++;
            }
            else
            {
                Words[size].word=a;
                Words[size].freq=1;
                size++;
            }

        }

    }
    else
    {
        Words[pos].freq++; //Increase the frequency by one since the word already exists in array
    }
}
void UnorderedArray::Delete(string &a)
{
    int i,pos=serialSearch(a); //Position of the word in array
    if (pos!=-1) //Check if word exists in array
    {
        //Realloc Words and count Arrays- decrease by one
        int k=0; //New counter k for correct indexing the temporary arrays
        value *tmp;
        tmp=new value[size-1];
        //Insert all words and counts before the desired deleted position
        for (i=0;i<pos;i++)
        {
            tmp[k]=Words[i];
            k++;
        }
        //Insert all words and counts after the desired deleted position
        for (i=pos+1;i<size;i++)
        {
            tmp[k]=Words[i];
            k++;
        }
        delete[] Words;
        Words=tmp;
        size--; //Decrease size by one
    }
    else
        cout<<"Delete failed!"<<endl; //Notify that the word doesn't not exist in array
}
ostream& operator<<(ostream& mystream,UnorderedArray& A) //Prints out all words in the array with their frequency
{
    int i;
    for (i=0;i<A.size;i++)
    {
        cout<<A.Words[i].word<<" - "<<A.Words[i].freq<<endl;
    }
    cout<<A.size<<endl;
}

int UnorderedArray::getSize() //Returns the size of the array
{
    return size;
}
int UnorderedArray::getFreq(int pos) //Returs the frequency of a word
{
    return Words[pos].freq;
}
