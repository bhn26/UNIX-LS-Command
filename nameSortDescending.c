/*
 * Filename: nameSortDescending.c
 * Desctiption: This will sort out the name member field of the infoTable in
 *              order to display it in sorted order.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

#include "myls.h"

/*
 * Function name: nameSortDescending()
 * Function prototype: int nameSortDescending(const void *p1, const void *p2);
 * Description: Sorts the name member field in reverse alphebetical order.
 * Parameters:
 *      arg 1: const void *p2 -- The first name field to be compared
 *      arg 2: const void *p1 -- The second name field to be compared
 *
 * Side Effects: Returns an int after compared two strings
 * Error Conditions: None
 * Return Value: Int
 */


int
nameSortDescending( const void *p1, const void *p2 )
{
   int ret = 0;                      //Val to be return
   struct fileInfo *ptr1, *ptr2;     //Used for casting

   ptr1 = (struct fileInfo*) p1;     //Casts the pointers
   ptr2 = (struct fileInfo*) p2;

   ret = strcmp(ptr1->name, ptr2->name); //Compares the strings
   return (-1*ret);                  //Return the values
}
