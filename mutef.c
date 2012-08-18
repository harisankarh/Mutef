/* mutexopen.c --- 
 * Filename: mutexopen.c
 * Description: 
 * Author: harisankarh
 * Organization:  IIT Madras
 * Created: Wed Aug  1 14:53:35 2012 (+0530)
 * Last-Updated: Wed Aug  1 15:22:35 2012 (+0530)
 *           By: harisankarh
 *     Update #: 47
 */
#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
main(int argc, char **argv)
{
  char filename[200];
  char lockfile[200];
  char command[200];
  struct stat filestat;

  if(argc != 2)
    {
      printf("format: hnb <filename>\n");
      exit(0);
    }

  // make the filename with lock

  strcpy(filename,argv[1]);
  strcpy(lockfile,argv[1]);
  strcat(lockfile,"_lock");

  //check if the lock file exists

  printf("Checking for lock file %s\n",lockfile);
  if(stat(lockfile,&filestat) < 0)
    {
  // else create the lock file
      printf("No lock file: creating one ..\n");
      sprintf(command,"touch %s",lockfile);
      system(command);
  // open the file using hnb
      sprintf(command,"orighnb %s",filename);
      system(command);
 // after closing using hnb, delete the lock file
      sprintf(command,"rm %s",lockfile);
      system(command);
    }
  else
    {
   // if so, warn and exit
      printf("ERROR: file already open! (delete lock file if you are sure otherwise)");
    }

}
