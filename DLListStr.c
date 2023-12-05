/*
 Implementation of doubly-linked list ADT for string values.
 Written by Tristan Clinton-Muehr, 
 z5420825
 based on code written by John Shepherd 2015, Ashesh Mahidadia Jan 2020.
 Date 14/10/2023
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#include "DLListStr.h"
#include "helpers.h"
#include "readData.h"


// data structures representing DLListStr

typedef struct DLListNode {
	char value[MAX_URL_LENGTH + 1];  
					// value of this list item (string)
	struct DLListNode *prev;
	               // pointer previous node in list
	struct DLListNode *next;
	               // pointer to next node in list
	int matches;
} DLListNode;

typedef struct DLListRep {
    int  nitems;      // count of items in list
    DLListNode *first; // first node in list
    DLListNode *curr;  // current node in list
    DLListNode *last;  // last node in list
} DLListRep;

 

static DLListNode *newDLListNode(Item it);
static bool comparingTwoDLListNodesMatchesPagerank(double pagerank, 
DLListStr l, DLListSingleNode biggestNode);


// create a new DLListNode 
static DLListNode *newDLListNode(Item it) {
        DLListNode *new;
        new = malloc(sizeof(DLListNode));
        assert(new != NULL);

        strcpy(new->value, it);  // for int, new->value = it;
		new->matches = 1;

        new->prev = NULL;
		new->next = NULL;
        return new;
}


// create a new empty DLListStr
DLListStr NewDLListStr() {
	struct DLListRep *l;

	l = malloc(sizeof (struct DLListRep));
	assert (l != NULL);
	l->nitems = 0;
	l->first = NULL;
	l->last = NULL;
	l->curr = NULL;
	return l;
}


// free up all space associated with list
void FreeDLListStr(DLListStr l) {
	assert(l != NULL);
	
	DLListNode *curr, *prev;
	curr = l->first;
	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(l);
}


// checks for duplicate string and if found adds a match 
// returns 1 or True if match is found
bool CheckDLListStrDuplicates(DLListStr l, Item it) {
	l->curr = l->first;
	while (l->curr != NULL) {
		if (strcmp(it, l->curr->value) == 0) {
			l->curr->matches++;
			return true;
		}
		l->curr = l->curr->next;
	}
	return false;
}


// display items from a DLListStr, space separated into file
void ShowDLListStrSpace(DLListStr l, FILE *invertedIndex) {
	assert(l != NULL);
	
	DLListNode *curr;
	for (curr = l->first; curr != NULL; curr = curr->next){
		fprintf(invertedIndex, " %s", curr->value);
	}
}


// prints items from a DLListStr, one per line
void ShowDLListStrLine(DLListStr l) {
	assert(l != NULL);
	DLListNode *curr;
	for (curr = l->first; curr != NULL; curr = curr->next) {
		fprintf(stdout, "%s\n", curr->value);
	}
}


// appends DLListNode to end of DLListStr
void DLListStrAppend(DLListStr l, Item it) {
	DLListNode *n = newDLListNode(it);
	
	if (l->first == NULL) {
		l->first = l->last = n;
		n->next = NULL;
		n->prev = NULL;
	} else {
		l->last->next = n;
		n->next = NULL;
		n->prev = l->last;
		l->last = n;
	}

	l->nitems++;
}


//adds value to list in the correct postion
//assume that list is already sorted
void DLListStrAddValue(DLListStr l, Item it) {
	DLListNode *n = newDLListNode(it);
	
	if (l->first == NULL) {
		//if list is empty
		l->first = n;
		l->last = n;
		n->next = NULL;
		n->prev = NULL;
	} else if (strcmp(it, l->first->value) < 0) {
		//if inserted at beginning
		n->next = l->first;
		l->first->prev = n;
		l->first = n;
	} else {
		l->curr = l->first;
		while (l->curr->next != NULL && strcmp(l->curr->next->value, it) < 0) {
			l->curr = l->curr->next;
		}

		n->next = l->curr->next;

		//if the ndw node is not inserted
		//insert at the end
		if (l->curr->next != NULL) {
			n->next->prev = n;
		}

		l->curr->next = n;
		n->prev = l->curr;
	}
}


// deletes DLListNode
void DLListStrDelete(DLListStr l, DLListSingleNode nodeToDelete) {
	//base case 
    assert(l != NULL || nodeToDelete != NULL);
  
	if (l->nitems == 1) {
		//delete the last node
		l->first = NULL;
		l->last = NULL;
	} else if (nodeToDelete->prev == NULL) {
		//first node but theres more than one in list
		l->first = nodeToDelete->next;
		l->first->prev = NULL;

	} else if (nodeToDelete->next == NULL) {
		//last node but theres more than one in list
		l->last = nodeToDelete->prev;
		l->last->next = NULL;
	} else {
		//node is in the middle of other nodes
		nodeToDelete->prev->next = nodeToDelete->next;
		nodeToDelete->next->prev = nodeToDelete->prev;
	}
	
	// Finally, free the memory occupied by nodeToDelete
    free(nodeToDelete);
	l->nitems--;
}


//returns sorted l DLListStr 
//outputed list is max 30 nodes long
//most is matched and then highest pagerank is what is meant by biggest
DLListStr SortDLListStr(DLListStr l) {
	assert(l != NULL);

	DLListStr sortedList = NewDLListStr();
	
	while (l->nitems > 0) {
		//pointer to biggest URL in the list
		DLListSingleNode biggestNode = l->first;
		
		double biggestNodePagerank = getPagerank(biggestNode->value);
		
		//start at second URL in the list which could be null
		// l->first cant be null because its checked in the condition nitems != 0
		l->curr = l->first->next;
		
		//loop to find biggest node
		while (l->curr != NULL) {

			if (comparingTwoDLListNodesMatchesPagerank(biggestNodePagerank, 
			l, biggestNode) == false) {
				biggestNode = l->curr;
				biggestNodePagerank = getPagerank(biggestNode->value);
			}
			
			l->curr = l->curr->next;
		}
		
		DLListStrAppend(sortedList, biggestNode->value);
		DLListStrDelete(l, biggestNode);
	}

	return sortedList;
}


//sorts 2 nodes by comparing their matches then their pageranks
// if bigger, changes biggestNode pointer and also pagerank pointer
//copmares l->curr and biggestNode
//returns true if biggest node is bigger
static bool comparingTwoDLListNodesMatchesPagerank(double pagerank, 
DLListStr l, DLListSingleNode biggestNode) {
	if (biggestNode->matches > l->curr->matches) {
		// biggest node has more mathces
		return true;
	} else if (biggestNode->matches == l->curr->matches) {
		// same mathces so compare page ranks
		if (getPagerank(l->curr->value) > pagerank) {
			return false;
		} else {
			return true;
		}
		//if pageranks are the same then just pick either

	} else {
		//biggest node has less matches
		return false;
	}
}


//returns nitems
int GetDLListStrLength (DLListStr l) {
	return l->nitems;
}

//sets curr pointer to first node
void SetCurrToFirstDLListStr(DLListStr l) {
	l->curr = l->first;
}

//gets item from DLListStr 
//assumes that curr is not pointing to NULL
//changes l->curr to point to next node
Item GetValueDLListStr(DLListStr l) {
	Item it = l->curr->value;
	l->curr = l->curr->next;
	return it;
}