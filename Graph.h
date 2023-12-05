/*
 Interface to graph ADT
 Written by Tristan Clinton-Muehr, 
 z5420825
 Date 14/10/2023
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <stdio.h>
#include "DLListStr.h"

typedef struct GraphRep *Graph;
typedef char *Item; 

// Creates a new graph including initialising the matrix to all zero
// Takes number size and also DLListStr so list can be converted to array
Graph GetGraph(int, DLListStr);

//frees the components of the graph
void FreeGraph(Graph);

//Fills in the graph matrix with true or false for outgoing links
//can be a duplicate link in which case the 1 will be changed to 1 
//so nothing happens
void AddValueToGraph(Graph, Item, Item);

// gets rid of self links that were added
void GetRidOfSelfLinks(Graph);

//gets teh outdegree for the url with inputed index
int GetOutDegree(Graph, int);

//gets value from the adjacency matrix
bool GetValueMatrix(Graph, int, int);

//gets a value from from the urls array and returns it
Item GetValueURLs(Graph, int);

#endif