/*
 * Filename: myls.c
 * Description: This program will behave much like that of the command line
 *              call "ls". The user will call the program followed by either
 *              an alrt flag, a file name, or directory. It will then display
 *              everything about the request file or directory.
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>
#include <grp.h>
#include <stdio.h>

#include "myls.h"

//Global offsets variables
int offset = (int) offsetof (struct fileInfo, stbuf.st_mtime);
int groupOff = (int) offsetof (struct group, gr_name);

/*
 * Function name: myls()
 * Function prototype: int myls( int argc, char *argv[] );
 *                              or
 *                     int myls( void );
 * Description: We can call myls that will implement a small subset of ls 
 *              options (-a, -l, -t, and -r or -altr). You can supply myls 
 *              with any combination of files and directories.
 * Parameters: The parameters vary depending on what the user inputs. It being
 *             either a alrt flag, firectory, or file name.
 * Side Effects: Displays info about the directory or file.
 * Error Conditions: Has to have the correct params or it'll display usage.
 * Return Value: int 0 indicating successful execution.
 */


int
main( int argc, char *argv[])
{
   int size, index, flagALRT = 0;    //Variables to check integers
   struct fileInfo *table;           //Table struct to store everything
   const char *flag = {"alrt"};      //Available flags
   char c;                           //Checks for the certain flag

   //While loop that checks though for all possible flags
   while ((c = getopt(argc, argv, flag)) != -1)
   {
      //Switch statement that checks for the type of flag.
      switch(c)
      {
         case 'a':
            flagALRT += AFLAG;
            break;
         case 'l':
            flagALRT += LFLAG;
            break;
         case 'r':
            flagALRT += RFLAG;
            break;
         case 't':
            flagALRT += TFLAG;
            break;
         case '?':                   //Checks if there is an unknown flag
            (void)fprintf(stderr, "Usage: %s [-alrt] [file ...]\n", argv[0]);
            exit(EXIT_FAILURE);
      }
   }

   //Checks if it's the current directory input
   if( argc == optind )
   {
      size = buildFileInfoTable( "." , &table ); //Builds table in current
      displayFileInfo(table, size, flagALRT);    //Displays all the file info
      free(table);                               //Frees up the table
   }

   //Checks of specific file or files
   for(index = optind; index < argc; index++)
   {
      size = buildFileInfoTable(argv[index], &table); //Checks multiple files
      displayFileInfo(table, size, flagALRT);         //Display info about file
      free(table);                                    //Frees up the table
   }

   return ( 0 );                    /* Returns 0 if sucessfully executed */
}

