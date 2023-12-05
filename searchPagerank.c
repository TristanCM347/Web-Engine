/*
 Outputs search terms from Inputed query words
 Written by Tristan Clinton-Muehr
 z5420825
 https://en.wikipedia.org/wiki/PageRank
 Date 14/10/2023
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "DLListStr.h"
#include "helpers.h"
#include "readData.h"


int main(int argc, char **argv) {
    DLListStr matchedURLList = findingMatchedURLS(argc, argv);

    DLListStr matchedURLListOrdered = SortDLListStr(matchedURLList);

    ShowDLListStrLine(matchedURLListOrdered);
    
    FreeDLListStr(matchedURLListOrdered);
    FreeDLListStr(matchedURLList);
    return 0;
}


