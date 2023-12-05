/*
 Implementation of helper functions
 Written by Tristan Clinton-Muehr, 
 z5420825
 Date 14/10/2023
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#include "helpers.h"


// removes new line char from word if there is one and replaces with with '\0'
// inputed string must be null terminated
void removeNewlineChar(Item word) {
    // find new line
    char* ptr = strchr(word, '\n');
    if (ptr) {
        // if new line found replace with null character
            *ptr = '\0';
        }
}


// removes comma char from word if there is one and replaces with with '\0'
// inputed string must be null terminated
void removeCommaChar(Item word) {
    // find new line
    char* ptr = strchr(word, ',');
    if (ptr) {
        // if new line found replace with null character
            *ptr = '\0';
        }
}


//normalises word by convertin letters to lowercase and removing specified
//punctuation marks at end of words
void normaliseWord(Item word) {  
    int i = 0;
    while (word[i] != '\0') {
        i++;
    }
    //at the end of the string
    i--;
    
    bool afterEndOfWord = true;

    //index is still in the word 
    while (i >= 0) {
        if ((word[i] == '.' || word[i] == ',' || word[i] == ':' || 
        word[i] == ';' || word[i] == '?' || word[i] == '*') 
        && afterEndOfWord == true) {
            //remove character
            word[i] = '\0';
        } else if ((word[i] == '.' || word[i] == ',' || word[i] == ':' || 
        word[i] == ';' || word[i] == '?' || word[i] == '*') 
        && afterEndOfWord == false) {
            //leave it in the word
        } else {
            //its not a special character so check if its uppercase now
            afterEndOfWord = false;
            if (word[i] >= 'A' && word[i] <= 'Z') {
                word[i] = word[i] + DIFFERENCE_UPPERCASE_LOWERCASE;
            }
        }

        i--;
    }
}
