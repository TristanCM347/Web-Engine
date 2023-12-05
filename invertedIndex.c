/*
 Finds corresponding URLs to each word and prints them in alphabetically order 
 into file invertedIndex.txt
 Written by Tristan Clinton-Muehr
 z5420825
 Date 14/10/2023
*/


#include <stdlib.h>
#include <stdio.h>

#include "Graph.h"
#include "DLListStr.h"
#include "readData.h"
#include "helpers.h"
#include "BST.h"
#include "InvertedIdx.h"


int main(void) {
    DLListStr listOfURLs = getCollection();
    
    //create inverted index
    InvertedIndex idx = NewInvertedIndex();

    //add all values to it
    idx = findingCorrespondingURLsToWords(idx, listOfURLs);
    
    OutputInvertedIndexToTextfile(idx);
    
    FreeInvertedIndex(idx);
    FreeDLListStr(listOfURLs);
    
    return 0;
}
