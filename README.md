# Data Structures
This project consists of my own implementation of basic data structures.
The implementation refers to the structures:
- Unordered Array
- Ordered Array
- Binary Search Tree
- AVL Tree
- Hash Array

## Functions
Each structure supports the following operations:
 - Insert record
 - Delete record
 - Search record

Especially for the Binary Search Tree and the AVL Tree more operations are supported:
 - Find Max Record
 - Find Min Record
 - Preorder, Inorder, Postorder traversal

## Architecture
### Main Class
The main class reads a .txt file which consists of a text and inserts each word to every data structure. </br>
It then generates a Query of a random size and executes the query to each data structure. </br>
Finally, it measures the performance (time) of each data structure to the specific query.
### More Tools Header
The moreTools header creates the structure of a node for the tree structures and a pair of a word and its frequency for the rest of the structures.
### Rest of the Classes
Each data structure consists of a class with its header and the .cpp file.
