/*
 Interface of the Inverted Index Data Type
 Written by Tristan Clinton-Muehr,
 z5420825 
 Date 14/10/2023
*/

#include <stdio.h>
#include <stdbool.h>

#include "BST.h"
#include "InvertedIdx.h"
#include "DLListStr.h"


//makes new inverted index
InvertedIndex NewInvertedIndex(void) {
    return NewTree();
}


//prints Inverted Index to file invertedIndex.txt
void OutputInvertedIndexToTextfile(InvertedIndex idx) {
    //open file
    FILE *invertedIndex;
    invertedIndex = fopen("invertedIndex.txt", "w");
    DoPrintTreeListInOrderWithDLListStr(idx, invertedIndex);
    fclose(invertedIndex);
}


//adds word and assoicated link to inverted index
InvertedIndex AddWordAndLinkToInvertedIndex(InvertedIndex idx, 
Item word, Item url) {
    // check whether a word is in Tree
    // add if not in tree
    if (TreeSearch(idx, word) == false) {
        idx = TreeInsert(idx, word);
    }

    //add url to words node
    // first return DLListStrPointer from BST
    DLListStr listOfURLs = TreeGetPointerToList(idx, word);
    //check for duplicates in list
    if (CheckDLListStrDuplicates(listOfURLs, url) 
    == false) {
        DLListStrAddValue(listOfURLs, url);
    }

    return idx;
}


//frees inverted index
void FreeInvertedIndex(InvertedIndex idx) {
    FreeTree(idx);
}