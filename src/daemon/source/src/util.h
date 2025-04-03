
#ifndef __UTIL__

#define __UTIL__
#include <stdio.h>

/* cut leading and trailing whitespace, and ensure only one space is between all 
 * 'words', i.e. all groups of whitespace seperated characters. Uses isspace() to
 * catagorize characters as whitespace.                                          
 * Returns the ending length of the string, or -1 on an error. */
int strtrm(char * str);

/* sets buf to an allocated block containing the contents of the file
 * located at path. Memory must be deallocated by the user.
 * Allocates memory to buf and returns the total size on success.
 * Returns -1, sets buf to NULL, and does not allocate memory on failure */
int load(char * path, char ** buf);

/* return an allocated buffer containing the contents of the file
 * located at path. Memory must be deallocated by the user.
 * returns NULL on error.                                        */
char * fload(FILE * fptr);

#endif
