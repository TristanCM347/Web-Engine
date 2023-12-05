/*
 Interface of the Inverted Index Data Type
 Written by Tristan Clinton-Muehr,
 z5420825 
 Date 14/10/2023
*/

#ifndef INVERTEDIDX_H
#define INVERTEDIDX_H

#include <stdio.h>

#include "BST.h"

typedef Tree InvertedIndex;
typedef char *Item; 

//makes new inverted index
InvertedIndex NewInvertedIndex(void);

//prints Inverted Index to file invertedIndex.txt
void OutputInvertedIndexToTextfile(InvertedIndex);

//adds word and assoicated url to inverted index
InvertedIndex AddWordAndLinkToInvertedIndex(InvertedIndex, Item, Item);

//frees inverted index
void FreeInvertedIndex(InvertedIndex);

#endif