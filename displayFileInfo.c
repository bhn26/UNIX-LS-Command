/*
 * Filename: displayFileInfo.c
 * Desctiption: Main file that handles all the display info about the file.
 *              this will check for all the alrt flags and display necessary
 *              information about the specific file or directory.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/mkdev.h>
#include <time.h>

#include "myls.h"

/*
 * Function name: displayFileInfo()
 * Function prototype: void displayFileInfo( struct fileInfo * const table, 
                                             const int entries, 
                                             const int displayMode);
 * Description: Takes in three parameters and displays info about the file or
 *              directory upon request of the user.
 * Parameters:
 *      arg 1: struct fileInfo * const table -- Table struct that holds info
 *      arg 2: const int entries -- Number of files in directory or single
 *      arg 3: const int displayMode -- alrt flag inputted by user
 *
 * Side Effects: Prints requested info about file or directory.
 * Error Conditions: None
 * Return Value: None
 */


void
displayFileInfo(struct fileInfo * const table, 
                const int entries, const int displayMode)
{
   int index, aFile, lFile, rFile, tFile, BCD = 0; //Various vals and flags
   struct timeval time;              //Timeval struct

   //Checks for the alrt flags to see if any were set
   aFile = displayMode & AFLAG;
   lFile = displayMode & LFLAG;
   rFile = displayMode & RFLAG;
   tFile = displayMode & TFLAG;

   //Checks the the alrt flags to sort accordingly
   if(rFile != 0 && tFile != 0)
      qsort(table, entries, sizeof(struct fileInfo), mtimeSortAscending);
   if(rFile == 0 && tFile != 0)
      qsort(table, entries, sizeof(struct fileInfo), mtimeSortDescending);
   if(rFile != 0 && tFile == 0)
      qsort(table, entries, sizeof(struct fileInfo), nameSortDescending);
   if(rFile == 0 && tFile == 0)
      qsort(table, entries, sizeof(struct fileInfo), nameSortAscending);
   
   //For loop to loop through everything and print it
   for( index = 0; index < entries; index++)
   {
      //Checks for -a flag
      if( aFile == 0 )
      {
         //Sets strings to compare for hidden file
         char string1[MAXNAMLEN];
         char string2[MAXNAMLEN];
         (void) strcpy(string1, (table+index)->name);
         (void) strcpy(string2, ".");

         //Checks to see if the file is a hidden file
         if( strncmp(string1, string2, 1) == 0)
            continue;
      }
      
      //Checks for -l flag
      if( lFile != 0)
      {
         //Check the stbuf.st_mode member for type and prints type
         if(S_ISDIR((table+index)->stbuf.st_mode) != 0)
            (void)printf("d");
         if(S_ISLNK((table+index)->stbuf.st_mode) != 0)
            (void)printf("l");
         if(S_ISBLK((table+index)->stbuf.st_mode) != 0)
         {
            (void)printf("b");
            BCD = 1;
         }
         if(S_ISCHR((table+index)->stbuf.st_mode) != 0)
         {
            (void)printf("c");
            BCD = 1;
         }
         if(S_ISREG((table+index)->stbuf.st_mode) != 0)
            (void)printf("-");

         //Displays basic info about the file
         displayPermissions((table+index)->stbuf.st_mode);
         (void)printf("%3lu ", (table+index)->stbuf.st_nlink);
         displayOwnerName((table+index)->stbuf.st_uid);
         displayGroupName((table+index)->stbuf.st_gid);
         
         //Checks if the file is a block character device
         if(BCD != 0)
         {
            (void)printf("%3ld,%3ld ", 
                          major((table+index)->stbuf.st_rdev),
                          minor((table+index)->stbuf.st_rdev));
         }
         //Else prints the size of the file
         else
            (void)printf("%7ld ", ((table+index)->stbuf.st_size));

         //Creates a rawtime pointer to everything
         char *rawtime = ctime(&(table+index)->stbuf.st_mtime);

         //Creates a string starting at the Month
         char *date = strchr(rawtime, ' ');
         date++;
         
         //Creates a string starting with the year
         char *year = strchr(date, ' ');
         year += 12;

         //Cuts off everything after the year
         year[5] = '\0';
 
         //Cuts off everything after the desired date/time
         date[12] = '\0';

         //Checks if the file is older than 6 months 
         (void)gettimeofday(&time, NULL); 
         if((table+index)->stbuf.st_mtime < (time.tv_sec - 15724800))
         { 
            //Cuts off everything after day to only print month and day
            date[6] = '\0';
            (void)fprintf(stdout, "%s %s ", date, year); 
         } 
         
         //Prints everything else with MDT
         else
         { 
            (void)fprintf(stdout, "%s ", date); 
         }
      }
      (void) printf("%s\n", (table+index)->name);   //Prints filename
   }
}

