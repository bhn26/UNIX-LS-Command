/*
 * Filename: buildFileInfoTable.c
 * Desctiption: This file builds up a table of infoFile structs from either
 *              a single file or multiple from a directory. It'll then fill
 *              out the table with the stats of each file or file into the
 *              table and finally returning the size of the table.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <libgen.h>

#include "myls.h"

/*
 * Function name: buildFileInfoTable()
 * Function prototype: int buildFileInfoTable(const char *filename, 
 *                                          struct fileInfo ** const tablePtr);
 * Description: Builds a table consisting of the stat info about either a file 
 *              or multiple files in a given directory.
 * Parameters:
 *      arg 1: const char *filename -- filename or directory
 *      arg 2: struct fileInfo ** const tablePtr -- pointer to pointer of table
 *
 * Side Effects: Sets values into newly created tablePtr and returns and int
 * Error Conditions: None
 * Return Value: Int
 */


int
buildFileInfoTable( const char *filename, struct fileInfo ** const tablePtr )
{
   int tableSize = 0;                // Return value
   int status = 0;                   // Status of lstat
   struct stat buffer;               // Struct stat to store info
   DIR *dir;                         // Directory var
   struct dirent *dp;                // Dirent var
   struct fileInfo *table = NULL;

   //Calls lstat on the file or directory
   status = lstat( filename, &buffer );
   
   //Checks for errno and prints error message if it exists
   if ( errno != 0 && status != 0 )
   {
      (void) fprintf ( stderr, "lstat -- ");
      perror( filename );
      return 0;                      // Exits function
   }

   //Checks if filename is a directory or not
   if ( S_ISDIR( buffer.st_mode ) == 0 )
   {
      tableSize = 1;                 //Changes size of table to 1

      //Mallocs enough space for one struct fileInfo
      *tablePtr = (struct fileInfo*) malloc(sizeof(struct fileInfo));
            
      //Checks if malloc was succesful or not and prints error messages
      if( NULL == *tablePtr)
      {
          (void) fprintf(stderr, "Trying to malloc a struct fileInfo ");
          (void) fprintf(stderr, "(in buildFileInfoTable())\n");
          exit( EXIT_FAILURE );
      }

      //Sets tablePtr values
      (void) memset((*tablePtr)->name, '\0', MAXNAMLEN);
      (void) strncpy ((*tablePtr)->name, filename, MAXNAMLEN);
      (*tablePtr)->stbuf = buffer;

      return tableSize = 1;          // Returns size val
   }
   
   //Prints out the name of the directory
   (void) printf("%s:\n", filename);
  
   //Opens the directory to be read through
   if((dir = opendir (filename)) == NULL)
   {
      //If directory could no be opened, print error messages
      (void) fprintf ( stderr, "opendir -- ");
      perror (filename);
      exit( EXIT_FAILURE );
   }

   //Runs through the directory using readdir
   while((dp = readdir(dir)) != NULL )
   {
      //Creates two new strings to concatenate
      char pathName[MAXNAMLEN];
      char path2[MAXNAMLEN];
      (void) strcpy(pathName, filename);
      (void) strcpy(path2, dp->d_name);
      
      //Concatenates the new strings to make a pathName
      (void) strcat(pathName, "/");
      (void) strcat(pathName, path2);

      //Calls lstat on the file or directory
      status = lstat( pathName, &buffer );

      //Reallocates space for the new struct files to fit
      *tablePtr = (struct fileInfo*) realloc (table, 
                   (tableSize+1)*((sizeof(struct fileInfo))));

      //Sets the new pointer
      if(*tablePtr != NULL)
         table = *tablePtr;

      //Checks if realloc failed, if so, print error statements
      else
      {
         (void) fprintf(stderr, "Trying to realloc another struct ");
         (void) fprintf(stderr, "fileInfo (in buildFileInfoTable())\n");
         (void) fprintf( stderr, "Only partial info will be displayed.\n" );
         break;
      }

      //Checks for errno and prints error message if it exists
      if ( errno != 0 && status != 0 )
      {
         (void) fprintf ( stderr, "lstat -- ");
         perror( filename );
         exit ( EXIT_FAILURE );         // Exit if perror exists
      }

      //Sets tablePtr values
      (void) memset((*tablePtr+tableSize)->name, '\0', MAXNAMLEN);
      (void) strncpy((*tablePtr+tableSize)->name, dp->d_name, MAXNAMLEN);
      (*tablePtr+tableSize)->stbuf = buffer;

      //(void) printf("%s\n", (*tablePtr+tableSize)->name);
      
      tableSize += 1;                //Increments tableSize
   }

   (void) closedir(dir);               //Closes the directory

   return tableSize;                 // Return size of table
}
