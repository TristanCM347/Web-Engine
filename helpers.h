/*
 Interface to helper functions
 Written by Tristan Clinton-Muehr, 
 z5420825
 Date 14/10/2023
*/

#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>

#define DIFFERENCE_UPPERCASE_LOWERCASE 32

typedef char *Item; 

// removes new line char from word if there is one and replaces with with '\0'
void removeNewlineChar(Item);

// removes comma char from word if there is one and replaces with with '\0'
// inputed string must be null terminated
void removeCommaChar(Item);

//normalises word by convertin letters to lowercase and removing specified
//punctuation marks at end of words
void normaliseWord(Item);

#endif
