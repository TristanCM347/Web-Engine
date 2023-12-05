/*
 Interface to way to read data from all necessary data files
 Written by Tristan Clinton-Muehr, 
 z5420825
 based on code written, Ashesh Mahidadia Jan 2020.
 Date 14/10/2023
*/

#ifndef READDATA_H
#define READDATA_H

#include <stdio.h>

#include "InvertedIdx.h"
#include "DLListStr.h"
#include "Graph.h"

#define MAX_STRING_LENGTH 1000
#define MAX_URL_LENGTH 100

typedef char *Item; 

// returns matched urls from query words in a list
DLListStr findingMatchedURLS(int argc, char **argv);

//finds outgoing links and adds this data to webGraph
void findingOutGoingLinks(Graph, DLListStr, int) ;

// gets pagerank from file and returns
double getPagerank(Item);

// gets list of urls from collection.txt
DLListStr getCollection();

//finds corresponding urls to each word and add them to inverted index
InvertedIndex findingCorrespondingURLsToWords(InvertedIndex, DLListStr);

#endif