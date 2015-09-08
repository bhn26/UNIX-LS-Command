/*
 * Filename: displayPermissions.c
 * Desctiption: This displays the permission allowed by the user, owner, and
 *              others and prints out rwx for read, write and executables.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <sys/stat.h>

#include "myls.h"

/*
 * Function name: displayPermissions()
 * Function prototype: void displayPermissions( const mode_t mode );
 * Description: This file goes through the st_mode member of the current
 *              file and then displays the pemissions of it.
 * Parameters: 
 *      arg 1: const mode_t mode -- The st_mode of the current file
 *
 * Side Effects: Displays the permissions of the file
 * Error Conditions: None
 * Return Value: None
 */


void
displayPermissions( const mode_t mode )
{
   //Bitwise operations on the modes to get the masks
   unsigned int user = mode & S_IRWXU;
   unsigned int group = mode & S_IRWXG;
   unsigned int other = mode & S_IRWXO;
   
   //Shifts the masks in correct spots
   user = user >> 6;
   group = group >> 3;

   //Makes an array of masks to run through
   unsigned int perm[3] = {user, group, other};
   int i = 0;                        //Counter var

   //For loop to run through the perm array
   for( i = 0; i < 3; i++)
      //Checks if each corresponding mask matches and prints permissions
      switch(perm[i])
      {
         case 0:
            (void) printf ("---");
            break;
         case 1:
            (void) printf ("--x");
            break;
         case 2:
            (void) printf ("-w-");
            break;
         case 3:
            (void) printf ("-wx");
            break;
         case 4:
            (void) printf ("r--");
            break;
         case 5:
            (void) printf ("r-x");
            break;
         case 6:
            (void) printf ("rw-");
            break;
         case 7:
            (void) printf ("rwx");
            break;
      }
   (void) printf (" ");              //Prints the final space
}
