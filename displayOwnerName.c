/*
 * Filename: displayOwnerName.c
 * Desctiption: Gets a pointer to the struct passwd for this uid so we can get
 *              the owner's name as a string (pw_name member).
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <pwd.h>

#include "myls.h"

/*
 * Function name: displayOwnerName()
 * Function prototype: void displayOwnerName( const uid_t uid );
 * Description: If the passwd entry cannot be found, just print the numeric
 *              value of the uid. In either case, the owner's name or uid 
 *              will be printed with a field width of 8 left justified. Use 
 *              the left adjustment flag '-' in the printf format specifier.
 * Parameters:
 *      arg 1: const uid_t uid -- The passwrd entry of the member
 *
 * Side Effects: Prints the ID of the file
 * Error Conditions: None
 * Return Value: None
 */


void
displayOwnerName( const uid_t uid )
{
   struct passwd *pswd;              //Sets up new passwd struct
   pswd = getpwuid(uid);             //Gets the uid of current file
   
   if (pswd == NULL)
      (void) printf("%-8u ", uid); //Prints numerical val

   else
      (void) printf("%-8s ", pswd->pw_name); //Prints the uid of the file
}
