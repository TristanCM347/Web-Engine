/*
 Implementation of BST ADT for DLListStr in DLListStr.c .
 Written by Tristan Clinton-Muehr, 
 z5420825
 based on code written by, Ashesh Mahidadia Jan 2020.
 Date 14/10/2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "BST.h"
#include "DLListStr.h"

#define data(tree)  ((tree)->data)
#define left(tree)  ((tree)->left)
#define right(tree) ((tree)->right)


typedef struct Node {
   Tree left, right;
   char  data[MAX_STRING_LENGTH + 1];
   DLListStr  list;	
} Node;


static Tree newNode(Item it);


// make a new node containing data
static Tree newNode(Item it) {
   Tree new = malloc(sizeof(Node));
   if (new == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
   }   

   new->list = NewDLListStr();
   strcpy(new->data, it);  
   left(new) = NULL;
   right(new) = NULL;
   return new;
}


// create a new empty Tree
Tree NewTree() {
   return NULL;
}


// free memory associated with Tree
void FreeTree(Tree t) {
   if (t != NULL) {
      FreeTree(left(t));
      FreeTree(right(t));
      FreeDLListStr(t->list);
      free(t);
   }
}


// check whether a key is in a Tree
bool TreeSearch(Tree t, Item it) {
   if (t == NULL)
      return false;

   else if (strcmp(it, data(t)) < 0)   
      return TreeSearch(left(t), it);
   
   else if (strcmp(it, data(t)) > 0)  
      return TreeSearch(right(t), it);

   else                               
      return true;
}


//Returns pointer to DLListStr
//assumes corresponding word is in the list
DLListStr TreeGetPointerToList(Tree t, Item it) {
   if (strcmp(it, data(t)) < 0) {
      return TreeGetPointerToList(left(t), it);
   } else if (strcmp(it, data(t)) > 0) {
      return TreeGetPointerToList(right(t), it);
   } else                               
      return t->list;
}


// insert a new item into a Tree
Tree TreeInsert(Tree t, Item it) {
   if (t == NULL)
      t = newNode(it);

   else if (strcmp(it, data(t)) < 0)   
      left(t) = TreeInsert(left(t), it);

   else if (strcmp(it, data(t)) > 0)  
      right(t) = TreeInsert(right(t), it);

   return t;
}


// prints words in LNR with each words attatched list 
void DoPrintTreeListInOrderWithDLListStr(Tree t, FILE *invertedIndex) {
   if (t != NULL) {
      DoPrintTreeListInOrderWithDLListStr(left(t), invertedIndex);
      
      //print word
      fprintf(invertedIndex, "%s", data(t));
      
      //print DLListStr
      ShowDLListStrSpace(t->list, invertedIndex);
      fprintf(invertedIndex, "\n");

      DoPrintTreeListInOrderWithDLListStr(right(t), invertedIndex);
   }
}