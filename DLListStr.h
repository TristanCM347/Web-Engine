/*
 Interface to doubly-linked list ADT for string values.
 Written by Tristan Clinton-Muehr,
 z5420825 
 based on code written by John Shepherd 2015, Ashesh Mahidadia Jan 2020.
 Date 14/10/2023
*/

#ifndef DLLISTSTR_H
#define DLLISTSTR_H

#include <stdio.h>
#include <stdbool.h>


#define MAX_STRING_LENGTH 1000
#define MAX_URLS_OUTPUT 30
#define MAX_URL_LENGTH 100


typedef struct DLListRep *DLListStr;
typedef struct DLListNode *DLListSingleNode;
typedef char *Item; 

// create a new empty DLListStr
DLListStr NewDLListStr();

// free up all space associated with list
void FreeDLListStr(DLListStr);

// checks for duplicate string and if found adds a match 
// returns 1 or True if match is found
bool CheckDLListStrDuplicates(DLListStr, Item);

// display items from a DLListStr, space separated into file
void ShowDLListStrSpace(DLListStr, FILE *);

// prints items from a DLListStr, one per line
void ShowDLListStrLine(DLListStr);

// appends DLListNode to end of DLListStr
void DLListStrAppend(DLListStr, Item);

//adds value to list in the correct postion
//assume that list is already sorted
void DLListStrAddValue(DLListStr, Item);

// deletes DLListNode from DLListStr
void DLListStrDelete(DLListStr, DLListSingleNode);

//returns sorted inputed DLListStr by matches and pagerank 
DLListStr SortDLListStr(DLListStr);

//returns nitems
int GetDLListStrLength (DLListStr);

//sets curr pointer to first node
void SetCurrToFirstDLListStr(DLListStr);

//gets item from DLLListStr 
//assumes that curr is not pointing to NULL
//changes l->curr to point to next node
Item GetValueDLListStr(DLListStr);

#endif
