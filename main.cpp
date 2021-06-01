#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "UnorderedArray.h"
#include "BinarySearchTree.h"
#include "Hashing.h"
using namespace std;
string fixWord(string &word) //Take out capital letters and punctuation
{
    int i;
    string checked;
    for (i=0;i<word.size();i++)
    {
        if (word[i]>=65 && word[i]<=90)
            checked.push_back(word[i]+32);
        if (word[i]>=97 && word[i]<=122)
        {
            checked.push_back(word[i]);
        }
    }
    return checked;
}
class Warray //class representing all words of text file
{
private:
    string *W;
    int count; //The number of words
    int size; //The capacity of the string Array
public:
    //Constructor
    Warray(int size) //Initialize the array to "size" capacity
    {
        W=new string[size];
        this->size=size;
        count=0;
    }
    //Other functions
    void insert(string& a)
    {
        if (count+1==size) //If size is not enough
        { //Then realloc to double the size
            string *temp;
            temp=new string[2*size];
            for (int i=0;i<count;i++)
            {
                temp[i]=W[i];
            }
            delete[] W;
            W=temp;
            size*=2;
            count++;
            W[count]=a;
        }
        else
        {
            count++;
            W[count]=a;
        }
    }
    int getCount() //Returns the number of words in text
    {
        return count;
    }
    string& operator[](int pos) //Overload [] to have easy access to words
    {
        return W[pos];
    }
};
int main(int argc, const char * argv[])
{
    Warray Text(1000); //Initialize to 1000 capacity
    UnorderedArray A; //An Unordered Array A
    BinarySearchTree B; //A Binary Search Tree B
    Hash C; //A Hash Table C
    ofstream results; //A stream to write the results to a text file
    results.open("../results.txt",ios::out); //The textfile will be named as: results.txt
    string word; //A string variable for reading from text file
    ifstream mystream;
    mystream.open("../gutenberg.txt",ios::in); //Open the file
    chrono::steady_clock read; //Initialize a chrono class variable
    auto start=read.now(); //Keep the read start time
    if (!(mystream.is_open()))
    {
        cout<<"File Error!"<<endl;
        exit(1);
    }
    else
    {
        while(mystream>>word)
        {
            word=fixWord(word); //Take out all unnecessary characters
            if (word.empty()==false)
                Text.insert(word);
        }
    }
    auto end=read.now(); //Keep the read finish time
    auto time_span=static_cast<chrono::duration<double>>(end - start); //Evaluate the time needed
    results<<"Read time of Text file took:"<<time_span.count()<<" seconds."<<endl; //Write the result to output text file
    mystream.close(); //Close text file

    //Reading
    chrono::steady_clock Unordered; //Create a chrono class variable for each structure
    chrono::steady_clock BST;
    chrono::steady_clock HashT;
    //Unordered Array
    auto sUnordered=Unordered.now(); //Keep the Unordered Array read start time
    for (int i=0;i<Text.getCount();i++)
    {
        A.insert(Text[i]);
    }
    auto eUnordered=Unordered.now(); //Keep the Unordered Array read finish time
    auto span_Unordered=static_cast<chrono::duration<double>>(eUnordered - sUnordered); //Evaluate the time needed
    results<<"Read time of Unordered Array took:"<<span_Unordered.count()<<" seconds."<<endl; //Write the result to output text file

    //Binary Search Tree
    auto sBST=BST.now(); //Keep the BST read start time
    for (int i=0;i<Text.getCount();i++)
    {
        B.insert(Text[i]);
    }
    auto eBST=BST.now(); //Keep the BST read finish time
    auto span_BST=static_cast<chrono::duration<double>>(eBST - sBST); //Evaluate the time needed
    results<<"Read time of Binary Search Tree took:"<<span_BST.count()<<" seconds."<<endl; //Write the result to output text file

    //Hash Table
    auto sHashT=HashT.now(); //Keep the Hash Table read start time
    for (int i=0;i<Text.getCount();i++)
    {
        C.insert(Text[i]);
    }
    auto eHashT=HashT.now(); //Keep the Hash Table read finish time
    auto span_HashT=static_cast<chrono::duration<double>>(eHashT - sHashT); //Evaluate the time needed
    results<<"Read time of Hash Table took:"<<span_HashT.count()<<" seconds."<<endl; //Write the result to output text file

    //Search

    //Define the size of set Q
    int Qsize;
    srand(time(NULL)); //Mix up the rand() function
    //Qsize=rand() % Text.getCount(); //If you want random Qsize
    Qsize=1000; //Fixed 1000 Qsize
    results<<"The random set of Q consists of:"<<Qsize<<" words."<<endl; //Inform the Qsize

    //Fill in Q set
    string *Q;
    Q=new string[Qsize];
    int rnum;
    for (int i=0;i<Qsize;i++)
    {
        rnum=rand()%Qsize;
        Q[i]=Text[rnum];
    }

    //Unordered Array
    sUnordered=Unordered.now(); //Keep the Unordered Array search start time
    for (int i=0;i<Qsize;i++)
    {
        results<<"Word:<"<<Q[i]<<"> has been in text for: "<<A.getFreq(A.serialSearch(Q[i]))<<" times."<<endl;
    }
    eUnordered=Unordered.now(); //Keep the Unordered Array search finish time
    span_Unordered=static_cast<chrono::duration<double>>(eUnordered - sUnordered); //Evaluate the time needed


    //Binary Search Tree
    sBST=BST.now(); //Keep the BST search start time
    for (int i=0;i<Qsize;i++)
    {
        results<<"Word:<"<<Q[i]<<"> has been in text for: "<<B.getFreq(B.search(Q[i]))<<" times."<<endl;
    }
    eBST=BST.now(); //Keep the BST search finish time
    span_BST=static_cast<chrono::duration<double>>(eBST - sBST); //Evaluate the time needed


    //Hash Table
    sHashT=HashT.now(); //Keep the Hash Table search start time
    for (int i=0;i<Qsize;i++)
    {
        results<<"Word:<"<<Q[i]<<"> has been in text for: "<<C.getFreq(C.HashSearch(Q[i]))<<" times."<<endl;
    }
    eHashT=HashT.now(); //Keep the Hash Table search finish time
    span_HashT=static_cast<chrono::duration<double>>(eHashT - sHashT); //Evaluate the time needed

    //Write the search results to output text file
    results<<"Search time of "<<Qsize<<" words in Unordered Array took:"<<span_Unordered.count()<<" seconds."<<endl;
    results<<"Search time of "<<Qsize<<" words in Binary Search Tree took:"<<span_BST.count()<<" seconds."<<endl;
    results<<"Search time of "<<Qsize<<" words in Hash Table took:"<<span_HashT.count()<<" seconds."<<endl;

    results.close(); //Close output text file
}
