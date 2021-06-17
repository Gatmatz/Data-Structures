#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "UnorderedArray.h"
#include "SortedArray.h"
#include "BinarySearchTree.h"
#include "Avltree.h"
#include "Hashing.h"
using namespace std;
string fixWord(string &word) //Take out capital letters and punctuation
{
    int i;
    string checked;
    for (i=0;i<word.size();i++)
    {
        if (word[i]>=65 && word[i]<=90) //If letter is uppercase
            checked.push_back(word[i]+32); //Then replace it with its lowercase
        if (word[i]>=97 && word[i]<=122) //If letter is lowercase
        {
            checked.push_back(word[i]); //Add it to the final word
        }
    }
    return checked; //Return final word
}
class Query //class representing a string set
{
private:
    string *W;
    long long count; //The number of words
    long long size; //The capacity of the string Array
public:
    //Constructor
    Query(long long size) //Initialize the array to 1000 capacity
    {
        W=new string[size];
        this->size=size;
        count=0;
    }
    //Other functions
    void insert(string a)
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
            W[count]=a;
            count++;
        }
        else
        {
            W[count]=a;
            count++;
        }
    }
    int getCount() //Returns the number of words in text
    {
        return count;
    }
    string& operator[](int pos) //Operator overload that returns the value to a specific position
    {
        return W[pos];
    }
};
int main(int argc, const char * argv[])
{
    UnorderedArray A; //An Unordered Array A
    SortedArray B; //A sorted array B
    BinarySearchTree C; //A Binary Search Tree C
    Avltree D; //An AVL Tree D
    Hash E; //A Hash Table E
    long long nofWords=0; //Variable that counts the words from text file
    ofstream results; //A stream to write the results to a text file
    results.open("results.txt",ios::out); //The textfile will be named as: results.txt
    string word; //A string variable for reading from text file
    string filename="small-file.txt"; //Filename variable to read a text file
    ifstream mystream;
    mystream.open(filename,ios::in); //Open the file
    chrono::high_resolution_clock read; //Initialize a chrono class variable
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
            {
                A.insert(word); //Insert words to Unordered Array
                B.insert(word); //Insert words to Sorted Array
                C.insert(word); //Insert words to Binary Search Tree Table
                D.insert(word); //Insert words to AVL
                E.insert(word); //Insert words to Hash Array
                nofWords++; //Increase by 1 the counter that counts the number of words
            }
        }
    }
    auto end=read.now(); //Keep the read finish time
    auto time_span=chrono::duration_cast<chrono::seconds>(end - start); //Evaluate the time needed
    results<<"Read time of Text file took:"<<time_span.count()<<" seconds."<<endl; //Write the result to output text file
    mystream.close(); //Close text file
    //Define the size of set Q
    long long Qsize; //Initialize Query size
    srand(time(NULL)); //Mix up the rand() function
    Qsize=1000; //Fixed Qsize size
    results<<"The random set of Q consists of:"<<Qsize<<" words."<<endl; //Inform for the Qsize
    results<<"Number of Words is:"<<nofWords<<endl; //Inform for the number of Words in the text file
    //Fill in Q set
    Query Q(Qsize); //Create Query with size Qsize
    long long count=0; //Variable that counts the number of Words that have been read
    long long randomstep; //Random step variable for picking words from text file
    do
    {
        randomstep=rand(); //Generate random step
        while (Qsize*randomstep<(nofWords*75)/100) //If random step is too small for picking from whole text file
        {
            randomstep*=2; //Double the random step
        }
        while (Qsize*randomstep>nofWords) //If random step is too big for text file
        {
            randomstep/=2; //Then divide by 2 the random step
        }
    }
    while (Qsize*randomstep>=nofWords || Qsize*randomstep<=(nofWords*75)/100); //Finally pick a random step that will at least pick words from the 75% of the text file
    results<<"The random step is set to:"<<randomstep<<"."<<endl; //Inform about the random step
    mystream.open(filename,ios::in); //Open the file
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
            {
                if (count == randomstep * Q.getCount()) //Choose word based on the random step
                {
                    if (Q.getCount() > Qsize) //Stop picking when you reach the Qsize
                        break;
                    Q.insert(word); //Insert the word to Query
                }
                count++; //Increase by 1 the counter that counts the number of words that have been read
            }
        }
    }
    using namespace std::chrono;
    //Search
    high_resolution_clock Unordered; //Create a chrono class variable for each structure
    high_resolution_clock Sorted;
    high_resolution_clock BST;
    high_resolution_clock AVL;
    high_resolution_clock HashT;

    //Unordered Array
    auto sUnordered=Unordered.now(); //Keep the Unordered Array search start time
    for (int i=0;i<Qsize;i++)
    {
        results<<"Word:<"<<Q[i]<<"> has been in text for: "<<A.getFreq(A.serialSearch(Q[i]))<<" times."<<endl; //Execute and print the search
    }
    auto eUnordered=Unordered.now(); //Keep the Unordered Array search finish time
    auto span_Unordered=duration_cast<milliseconds>(eUnordered - sUnordered); //Evaluate the time needed

    //Sorted Array
    auto sSorted=Sorted.now(); //Keep the Sorted Array search start time
    for (int i=0;i<Qsize;i++)
    {
        results<<"Word:<"<<Q[i]<<"> has been in text for: "<<B.getFreq(B.search(Q[i]))<<" times."<<endl; //Execute and print the search
    }
    auto eSorted=Sorted.now(); //Keep the Sorted Array search finish time
    auto span_Sorted=duration_cast<milliseconds>(eSorted - sSorted); //Evaluate the time needed


    //Binary Search Tree
    auto sBST=BST.now(); //Keep the BST search start time
    for (int i=0;i<Qsize;i++)
    {
        results<<"Word:<"<<Q[i]<<"> has been in text for: "<<C.getFreq(C.search(Q[i]))<<" times."<<endl; //Execute and print the search
    }
    auto eBST=BST.now(); //Keep the BST search finish time
    auto span_BST=duration_cast<milliseconds>(eBST - sBST); //Evaluate the time needed
    */

    //AVL Tree
    auto sAVL=AVL.now(); //Keep the AVL Tree search start time
    for (int i=0;i<Qsize;i++)
    {
        results<<"Word:<"<<Q[i]<<"> has been in text for: "<<D.getNodeFreq(D.search(Q[i]))<<" times."<<endl; //Execute and print the search
    }
    auto eAVL=AVL.now(); //Keep the AVL Tree search finish time
    auto span_AVL=duration_cast<milliseconds>(eAVL - sAVL); //Evaluate the time needed
    D.inorder(results);

    //Hash Table
    auto sHashT=HashT.now(); //Keep the Hash Table search start time
    for (int i=0;i<Qsize;i++)
    {
        results<<"Word:<"<<Q[i]<<"> has been in text for: "<<E.getFreq(E.HashSearch(Q[i]))<<" times."<<endl; //Execute and print the search
    }
    auto eHashT=HashT.now(); //Keep the Hash Table search finish time
    auto span_HashT=duration_cast<milliseconds>(eHashT - sHashT); //Evaluate the time needed


    //Write the search results to output text file
    results<<"Search time of "<<Qsize<<" words in Unordered Array took:"<<span_Unordered.count()<<" milliseconds."<<endl;
    results<<"Search time of "<<Qsize<<" words in Sorted Array took:"<<span_Sorted.count()<<" milliseconds."<<endl;
    results<<"Search time of "<<Qsize<<" words in Binary Search Tree took:"<<span_BST.count()<<" milliseconds."<<endl;
    results<<"Search time of "<<Qsize<<" words in AVL Tree took:"<<span_AVL.count()<<" milliseconds."<<endl;
    results<<"Search time of "<<Qsize<<" words in Hash Table took:"<<span_HashT.count()<<" milliseconds."<<endl;

    results.close(); //Close output text file
}
