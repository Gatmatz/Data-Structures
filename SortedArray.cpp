#include "SortedArray.h"
#include <cstring>
#include <iostream>

using namespace std;

SortedArray::SortedArray() //empty constructor
{
    arr=NULL; //Sets pointer to NULL
    size=0; //Sets size of words to 0
    R=0;
}

SortedArray::~SortedArray() //desturctor
{
    delete[] arr;
}   

int SortedArray::search(string s) //binary search in array for word s
{
    int low=0, high=size-1; 
    int midd=0;
    while (low<=high) //while low is on the left to high
    {
        midd=low+(high-low)/2; //sets middle
        if (arr[midd].word==s) //checks if the word is found at middle
            return midd; //returns position of the word
        if (arr[midd].word<s)
            low=midd+1; //if the word is after the middle one alphabetically, it ignores the left half
        else
            high=midd-1; //if the word is before the middle one alphabetically, it ignores the right half
    }
    return -1; //if the word is not found, it returns -1
}


void SortedArray::insert(string s) //adds word s in array
{
    int pos=search(s);//position of word in array if it already exists
    value* temp;
    if (pos!=-1)//checks if word exists in array
        arr[pos].freq++; //increases frequency by one
    else
    {
        if (arr==NULL) //if array is empty
        {
            arr=new value[size+1000]; //set size to 1000
            size++;
            arr[size-1].word=s;
            arr[size-1].freq=1;
            R=1; //first reallocation
        }
        else
        {
            if(size>=R*1000) //if array is full and needs reallocation
            {
                //increase size by 1000
                temp=new value [size+1000];
                for (int i=0; i<size; i++)
                    temp[i]=arr[i]; //copy array to construct new
                delete[] arr;
                arr=temp; 
                R++;
            }
            //perform insertion by shifting elements to keep the array sorted
            int i;
            for(i=size-1; (i>=0 && arr[i].word>s); i--)
                arr[i+1]=arr[i];
            arr[i+1].word=s;
            arr[i+1].freq=1;
            size++;
        }
    }
}


void SortedArray::deleteArr(string s) //deletes word s from array
{
    int pos=search(s);//position of word in array
    if (pos!=-1)//checks if word exists in array
    {
        int i;
        value *temp; //temporary array
        int j=0; //counter for temp array
        temp=new value [size-1]; //decrease size by one
        for (i=0; i<pos; i++) //insert elements before s in new array
        {
            temp[j]=arr[i];
            j++;
        }
        for (i=pos+1; i<size; i++) //insert elements after s in new array
        {
            temp[j]=arr[i];
            j++;
        }
        delete[] arr;
        arr=temp;
        size--;
    }
    else
        cout<<"Word not in array!"<<endl; //Notifies that word doesn't exist in array
}

ostream& operator<<(ostream& o,SortedArray& s) //Prints out all words in the array with their frequency
{
    int i;
    for (i=0;i<s.size;i++)
    {
        o<<s.arr[i].word<<" - "<<s.arr[i].freq<<endl;
    }
    o<<s.size<<endl;
    return o;
}

int SortedArray::getSize() //Returns the size of the array
{
    return size;
}
int SortedArray::getFreq(int pos) //Returns the frequency of a word
{
    return arr[pos].freq;
}
