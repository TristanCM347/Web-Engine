# COMP2521 Assignment Makefile
#
# HOW TO USE
# 1. Ensure that your directory structure looks like:
#    ass/
#        test1/
#            ...
#        test2/
#            ...
#        test3/
#            ...
#        Makefile (this Makefile)
#        pagerank.c
#        invertedIndex.c
#        searchPagerank.c
#        Your supporting files...
#
# 2. Read all the comments below and edit the Makefile accordingly
#
# 3. After you use the make command, this will create executables in
#    the test1/*, test2/* and test3/* directories. You can run the
#    runtests script to test using these executables.

# Don't change these
CFLAGS0 = -Wall -Werror -g
CFLAGS1 = -Wall -Werror -g -fsanitize=address,undefined#,leak   isnt compatible with mac so wont check for meory leaks, use valgrind instead
CFLAGS2 = -Wall -Werror -g -fsanitize=memory,undefined

# Change this to your desired set of flags - you may need to use
# CFLAGS0 if using GDB or valgrind. CFLAGS1 will be what we use to
# test your program
CFLAGS = $(CFLAGS1)

# Notes:
# Your pagerank.c should have the main() function for Part 1
# Your invertedIndex.c should have the main() function for Part 2
# Your searchPagerank.c should have the main() function for Part 3
# List all your C files that DON'T contain a main() function here
# Header files should not be included in this list
# For example: SUPPORTING_FILES = hello.c world.c
SUPPORTING_FILES = DLListStr.c helpers.c BST.c readData.c Graph.c InvertedIdx.c

# Change compiler to your choice, we will be using clang
CC = clang






SUPPORTING_OBJS = $(patsubst %.c, %.o, $(SUPPORTING_FILES))

.PHONY: all
all: pagerank invertedIndex searchPagerank

pagerank: pagerank.o $(SUPPORTING_OBJS)
	$(CC) $(CFLAGS) -o pagerank pagerank.o $(SUPPORTING_OBJS) -lm
	find . -maxdepth 1 -type d -path './test*' -exec cp pagerank {} \;

invertedIndex: invertedIndex.o $(SUPPORTING_OBJS)
	$(CC) $(CFLAGS) -o invertedIndex invertedIndex.o $(SUPPORTING_OBJS) -lm
	find . -maxdepth 1 -type d -path './test*' -exec cp invertedIndex {} \;

searchPagerank: searchPagerank.o $(SUPPORTING_OBJS)
	$(CC) $(CFLAGS) -o searchPagerank searchPagerank.o $(SUPPORTING_OBJS) -lm
	find . -maxdepth 1 -type d -path './test*' -exec cp searchPagerank {} \;

.PHONY: clean
clean:
	rm -f pagerank invertedIndex searchPagerank
	rm -f test*/pagerank test*/invertedIndex test*/searchPagerank
	rm *.o

.PHONY: copy
copy:
	find . -maxdepth 1 -type d -path './test*' -exec cp pagerank {} \;
	find . -maxdepth 1 -type d -path './test*' -exec cp invertedIndex {} \;
	find . -maxdepth 1 -type d -path './test*' -exec cp searchPagerank {} \;