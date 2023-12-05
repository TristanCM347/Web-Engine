/*
 Calculates pagerank and outdegree of urls and prints them to file pagerankList
 in sorted order with highest pagerank at the top
 Written by Tristan Clinton-Muehr
 z5420825
 https://en.wikipedia.org/wiki/PageRank
 Date 14/10/2023
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#include "Graph.h"
#include "DLListStr.h"
#include "readData.h"
#include "helpers.h"


static void calculatingPageranks(Graph webGraph, double *urlPageranksOld,
int variableN, double dampingFactor, double diffPR, int maxIterations);
static double sumPageranksOverOutdegree(int index, double *urlPageranksOld, 
int variableN, Graph webGraph);
static double sumAbsNewMinusOldPageranks(double *urlPageranksOld, 
double *urlPageranksNew, int variableN);
static void OutputPageranksToTextfile(double *urlPageranks,
Graph webGraph, int variableN);
static bool hasPagerankBeenAdded(int index, int *indexBeenAdded, int size);


int main(int argc, char **argv) {
    //get arguements
    double dampingFactor = atof(argv[1]);
    double diffPR = atof(argv[2]);
    int maxIterations = atoi(argv[3]);
    
    //build graph
    DLListStr listOfURLs = getCollection();
    int variableN = GetDLListStrLength(listOfURLs);
    Graph webGraph = GetGraph(variableN, listOfURLs);
    findingOutGoingLinks(webGraph, listOfURLs, variableN);
    GetRidOfSelfLinks(webGraph);
    //now graph is done
    
    double urlPageranks[variableN + 1];
    calculatingPageranks(webGraph, urlPageranks, variableN, 
    dampingFactor, diffPR, maxIterations);
    
    OutputPageranksToTextfile(urlPageranks, webGraph, variableN);
    
    FreeDLListStr(listOfURLs);
    FreeGraph(webGraph);
    
    return 0;
}


static void calculatingPageranks(Graph webGraph, double *urlPageranksOld,
int variableN, double d, double diffPR, int maxIterations) {
    double urlPageranksNew[variableN + 1];
    
    //intialise pageranks
    for (int i = 0; i < variableN; i++) {
        urlPageranksOld[i] = 1 / (double) variableN;
    }

    urlPageranksOld[variableN] = '\0';
    urlPageranksNew[variableN] = '\0';
    
    int iteration = 0;
    double diff = diffPR;

    while (iteration < maxIterations && diff >= diffPR) {
        for (int i = 0; i < variableN; i++) {
            urlPageranksNew[i] = ( (double) 1 - d) / (double) variableN 
            + d * sumPageranksOverOutdegree(i, urlPageranksOld, variableN, 
            webGraph);
        }
        diff = sumAbsNewMinusOldPageranks(urlPageranksOld, urlPageranksNew, 
        variableN);
        iteration++;
        
        //copy new array to old
        for (int i = 0; i < variableN; i++) {
            urlPageranksOld[i] = urlPageranksNew[i];
        }
    }
    
    //now all the pageranks are in the urlPageranksOld
}


//gets the sum of pageranks over out degree for url of the inputed index
static double sumPageranksOverOutdegree(int index, double *urlPageranksOld, 
int variableN, Graph webGraph) {
    double sum = 0;
    
    //these are the set of pages with links to url of inputed index
    for (int i = 0; i < variableN; i++) {
        if (GetValueMatrix(webGraph, i, index) == true) {
            double pagerankOverOutdegree 
            = urlPageranksOld[i] / (double) GetOutDegree(webGraph, i);
            sum = sum + pagerankOverOutdegree;
        }
    }
    return sum;
}


static double sumAbsNewMinusOldPageranks(double *urlPageranksOld, 
double *urlPageranksNew, int variableN) {
    double sum = 0;
    for (int i = 0; i < variableN; i++) {
        double NewMinusOld = urlPageranksNew[i] - urlPageranksOld[i];
        sum = sum + fabs(NewMinusOld);
    }
    return sum;
}

//prints pageranks in sorted order to textfile  with outdegree and url name
static void OutputPageranksToTextfile(double *urlPageranks,
Graph webGraph, int variableN) {
    //open file
    FILE *pagerankList;
    pagerankList = fopen("pagerankList.txt", "w");
    
    //dont need a '\0'
    int indexBeenAdded[variableN];

    //loop to make sure all urls gets added
    
    for (int i = 0; i < variableN; i++) {

        //loop to find biggest pagerank that hasnt been added yet
        //have to initialise biggestPagerankIndex so below is code to do that
        int biggestPagerankIndex;
        bool initialised = false;
        for (int j = 0; j < variableN; j++) {
            if (initialised == false) {
                if (hasPagerankBeenAdded(j, indexBeenAdded, i) == false) {
                    //intialise biggestPagerankIndex with j
                    biggestPagerankIndex = j;
                    initialised = true;
                } else {
                    //j has already been added so go to next pagerank
                    //to find another value to intialise with
                }
            } else {
                //biggestPagerankIndex has been initalised so now compare
                if (hasPagerankBeenAdded(j, indexBeenAdded, i) == false) {
                    //compare j pagerank with biggestPagerankIndexs pagerank
                    if (urlPageranks[biggestPagerankIndex] < 
                    urlPageranks[j]) {
                        biggestPagerankIndex = j;
                    }
                } else {
                    //its been added thus go to next pagerank
                }
            }
        }

        //add each url to file 
        fprintf(pagerankList, "%s, %d, %.7lf\n", 
        GetValueURLs(webGraph, biggestPagerankIndex), 
        GetOutDegree(webGraph, biggestPagerankIndex), 
        urlPageranks[biggestPagerankIndex]);
        indexBeenAdded[i] = biggestPagerankIndex;
    }

    fclose(pagerankList);
}

//checks if index of pagerank/url has been added
//returns true or false
static bool hasPagerankBeenAdded(int index, int *indexBeenAdded, 
int sizeOfArray) {
    for (int i = 0; i < sizeOfArray; i++) {
        if (indexBeenAdded[i] == index) {
            return true;
        }
    }
    return false;
}