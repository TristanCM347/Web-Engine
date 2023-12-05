/*
 Implementation of graph ADT
 Written by Tristan Clinton-Muehr, 
 z5420825
 Date 14/10/2023
*/

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "DLListStr.h"


typedef struct GraphRep {
    int    numURLs;

    Item *urls;     // the id of a URL is simply the index
                     // that contains the URL in this array
    
    bool **linksMatrix;
                    //x axis is urls
                    //y axis is hyperlinks on that url page
} GraphRep;


// Creates a new graph including initialising the matrix to all zero
// Takes number size and also DLListStr so list can be converted to array
Graph GetGraph(int size, DLListStr listOfURLs) {
    Graph g = malloc(sizeof(*g));
    if (g == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    g->numURLs = size;
    

    //add url list
    g->urls = calloc(size, sizeof(Item));
    if (g->urls == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }   
    
    SetCurrToFirstDLListStr(listOfURLs);
    
    for (int i = 0; i < g->numURLs; i++) {
        g->urls[i] = GetValueDLListStr(listOfURLs);
    }
    

    //create matrix
    g->linksMatrix = malloc(g->numURLs * sizeof(bool *));
    if (g->linksMatrix == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < g->numURLs; i++) {
        g->linksMatrix[i] = calloc(g->numURLs, sizeof(bool));
        if (g->linksMatrix[i] == NULL) {
            fprintf(stderr, "error: out of memory\n");
            exit(EXIT_FAILURE);
        }
    }

    //initialise matrix
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            g->linksMatrix[i][j] = false;
        }
    }

    return g;
}


//frees the components of the graph
void FreeGraph(Graph g) {
    for (int i = 0; i < g->numURLs; i++) {
        free(g->linksMatrix[i]);
    }
    free(g->linksMatrix);

    free(g->urls);
    
    free(g);
}


///Fills in the graph matrix with true or false for outgoing links
//can be a duplicate link in which case the 1 will be changed to 1 
//so nothing happens
//matrix[urlpage][hyperlink from that page]
//matrix[row][col]
void AddValueToGraph(Graph g, Item urlpage, Item hyperlink) {
    int i = 0;
    while (i < g->numURLs) {
        //look thoruhg array to find number assigned to url
        if (strcmp(g->urls[i], urlpage) == 0) {
            break;
        }
        i++;
    }
    //i is on the correct position
    int j = 0;
    while (j < g->numURLs) {
        //look thoruhg array to find number assigned to url
        if (strcmp(g->urls[j], hyperlink) == 0) {
            break;
        }
        j++;
    }

    //changing value
    g->linksMatrix[i][j] = true;

}


// gets rid of self links that were added
void GetRidOfSelfLinks(Graph g) {
    int i = 0;
    int j = 0;
    while (i < g->numURLs) {
        g->linksMatrix[i][j] = false;
        i++;
        j++;
    }
}


//gets teh outdegree for the url with inputed index
//counts how many trues there are on row of inputed index
int GetOutDegree(Graph g, int row) {
    int outDegree = 0;
    for (int i = 0; i < g->numURLs; i++) {
        if (g->linksMatrix[row][i] == true) {
            outDegree++;
        }
    }
    return outDegree;
}


//gets value from the adjacency matrix
bool GetValueMatrix(Graph g, int row, int col) {
    return g->linksMatrix[row][col];
}


//gets a value from from the urls array and returns it
Item GetValueURLs(Graph g, int index) {
    return g->urls[index];
}