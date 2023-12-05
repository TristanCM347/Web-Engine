/*
 Interface to BST ADT
 Written by Tristan Clinton-Muehr, 
 z5420825
 based on code written, Ashesh Mahidadia Jan 2020.
 Date 14/10/2023
*/

#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include <stdio.h>

#include "DLListStr.h"

#define MAX_STRING_LENGTH 1000

typedef char *Item;     
typedef struct Node *Tree;

// create an empty Tree
Tree NewTree();        

// free memory associated with Tree
void FreeTree(Tree);   

// check whether an item is in a Tree
bool TreeSearch(Tree, Item);   

//Returns pointer to DLListStr
//assumes corresponding word is in the list
DLListStr TreeGetPointerToList(Tree, Item);

// insert a new item into a Tree
Tree TreeInsert(Tree, Item);   

// prints words in LNR with each words attatched list 
void DoPrintTreeListInOrderWithDLListStr(Tree, FILE *);

#endif


