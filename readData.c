/*
 Implementation of way to read data from all necessary data files
 Written by Tristan Clinton-Muehr, 
 z5420825
 based on code written, Ashesh Mahidadia Jan 2020.
 Date 14/10/2023
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "BST.h"
#include "helpers.h"
#include "readData.h"
#include "DLListStr.h"
#include "InvertedIdx.h"

static void readFileForURLs (Item queryWord, DLListStr matchedURLList, 
FILE *invertedIndex);
static void readSection1(Item urlname, Graph g);
static InvertedIndex readSection2(Item urlname, InvertedIndex idx);


// returns matched urls from query words in a list
DLListStr findingMatchedURLS(int argc, char **argv) {
    FILE *invertedIndex;
    invertedIndex = fopen("invertedIndex.txt", "r");
    
    if (invertedIndex == NULL) {
        printf("null file\n");
        exit(EXIT_FAILURE);
    }
    
    DLListStr matchedURLList = NewDLListStr();

    //loop for query words
    for (int x = 1; x < argc; x++) {
        readFileForURLs(argv[x], matchedURLList, invertedIndex);
        rewind(invertedIndex);
    }

    fclose(invertedIndex);
    return matchedURLList;
}


//reads line by line to find query word so can add corresponding urls to 
//DLListStr
static void readFileForURLs (Item queryWord, DLListStr matchedURLList, 
FILE *invertedIndex) {
    //+1 is for '\0'
    char line[MAX_STRING_LENGTH + 1];

    //traverse through each line in file
    while(fgets(line, MAX_STRING_LENGTH + 1, invertedIndex) != NULL) {
        // get the first token which is the first word
        Item nextWord = strtok(line, " ");

        //check if query words is the same
        if (strcmp(queryWord, nextWord) == 0) {
            //makes pointer point to start of next word
            nextWord = strtok(NULL, " ");

            //since there can be at least one url, need to start checking 
            //for new line char as this is always after the last url

            while(nextWord != NULL) {
                removeNewlineChar(nextWord);
                if (CheckDLListStrDuplicates(matchedURLList, nextWord) 
                == false) {
                    //no matches
                    DLListStrAppend(matchedURLList, nextWord);
                }
                
                // else there was a match and a match was added
                nextWord = strtok(NULL, " ");
            }
            break;
        }
        
    }
    
}


//loops thoruhg each url in DLListStr and runs function to open urls 
// correspondnig file
void findingOutGoingLinks(Graph webGraph, DLListStr listOfURLs, int size) {
    SetCurrToFirstDLListStr(listOfURLs);
    for (int i = 0; i < size; i++) {
        readSection1(GetValueDLListStr(listOfURLs), webGraph);
    }
}


// gets pagerank from file and returns
double getPagerank(Item url) {
    FILE *pagerankList;
    pagerankList = fopen("pagerankList.txt", "r");
    
    if (pagerankList == NULL) {
        printf("null file\n");
        exit(EXIT_FAILURE);
    }

    char urlFromFile[MAX_URL_LENGTH + 1];
    double pagerank;

    while (fscanf(pagerankList, "%s %*d%*c %lf", 
    urlFromFile, &pagerank) == 2) {
		removeCommaChar(urlFromFile);
        
        //check if URLs are the same
        if (strcmp(urlFromFile, url) == 0) {
            break;
        }
        
	}
    
	fclose(pagerankList);
    return pagerank;
}


// gets list of urls from collection.txt
DLListStr getCollection(void) {
    FILE *collection;
    collection = fopen("collection.txt","r");
    if (collection == NULL) {
        printf("null file/n");
        exit(EXIT_FAILURE);
    }

    DLListStr listOfURLs = NewDLListStr();

    char url[MAX_URL_LENGTH + 1];
    while (fscanf(collection, " %s", url) != EOF) {
        if (strcmp("\n", url) != 0) {
            removeNewlineChar(url);
            DLListStrAppend(listOfURLs, url);
        }
    }
    fclose(collection);
    return listOfURLs;
}




static void readSection1(Item urlname, Graph g) {
    //create file name
    char websiteName[MAX_URL_LENGTH + 5];
    strcpy(websiteName, urlname);
    strcat(websiteName, ".txt");
    
    FILE *website;
    website = fopen(websiteName, "r");
    
    //scan in start section but ignore whitespace 
    char url[MAX_URL_LENGTH + 1];
    while (fscanf(website, " %s", url) == 1) {
        if (strcmp(url, "#start") == 0) {
            // scan the next word which is section
            fscanf(website, " %*s");
            break;
        }
    }

    //now we are on the next line with urls
    while (fscanf(website, " %s", url) == 1) {
        if (strcmp("#end", url) == 0) {
            break;
        } 
        if (strcmp("\n", url) != 0) {
            //add urls to graph matrix
            removeNewlineChar(url);
            AddValueToGraph(g, urlname, url);
        }
    }

    fclose(website);
    
}


static InvertedIndex readSection2(Item urlname, InvertedIndex idx) {
    //create file name
    char websiteName[MAX_URL_LENGTH + 5];
    strcpy(websiteName, urlname);
    strcat(websiteName, ".txt");
    
    FILE *website;
    website = fopen(websiteName, "r");
    
    //scan in start section but ignore whitespace 
    int section = 0;
    char word[MAX_STRING_LENGTH + 1];
    //so it breaks when section = 2 
    while (section != 2 && fscanf(website, " %s", word) == 1) {
        if (strcmp(word, "#start") == 0) {
            // scan the next word which is section
            fscanf(website, " %*s");
            section++;
        }
    }

    //now we are on the next line with words
    while (fscanf(website, " %s", word) == 1) {
        if (strcmp("#end", word) == 0) {
            break;
        } 
    
        if (strcmp("\n", word) != 0) {
            //add urls to inverted index
            removeNewlineChar(word);
            normaliseWord(word);

            //chekc if its empty word
            if (word[0] != '\0') {
                idx = AddWordAndLinkToInvertedIndex(idx, word, urlname);
            }
        }
    }

    fclose(website);
    return idx;

}


//loops thoruhg each url in DLListStr and runs function to open urls 
// corresponding file
InvertedIndex findingCorrespondingURLsToWords(InvertedIndex idx, 
DLListStr listOfURLs) {
    int size = GetDLListStrLength(listOfURLs);
    SetCurrToFirstDLListStr(listOfURLs);
    for (int i = 0; i < size; i++) {
        idx = readSection2(GetValueDLListStr(listOfURLs), idx);
    }
    
    return idx;
}

