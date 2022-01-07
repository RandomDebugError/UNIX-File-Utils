#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

/* This program list the files in a given directory and gives option to display *
 * REQUESTED stat() level info with -l arguement. With lack of expected output, output formatted to preference. */

/* Declaring functions. */
void standardRun (DIR *dir);
void specialRun(DIR *dir, char **argv, int flag);


int main(int argc, char **argv)
{
    DIR *dir;
    int flag = 0;

    /* if-else-if statements that handle arguement choices. */
    if(argc == 1)
    {
        /* Runs default in current directory with standard processing. */
        dir = opendir(".");
        standardRun(dir);
    }else if(argc == 2 && (strcmp(argv[1], "-l") == 0))
     {
         /* Runs REQUESTED stat() processing on current directory. */
         dir = opendir(".");
         specialRun(dir, argv, flag);
     }else if(argc == 2)
      {
          /* Runs default on given directory with standard processing. */
          dir = opendir(argv[1]);
          standardRun(dir);
      }else if (argc == 3)
       {
           /* Runs REQUESTED stat() processing on given directory. */
           dir = opendir(argv[2]);
           flag = 1;
           specialRun(dir, argv, flag);
       }    
    /* Closes open directory. */
    closedir(dir);

    return 0;
}



/* Function prints out only name of items in directory. */
void standardRun(DIR *dir)
{
    struct dirent *d;

    /* While loop prints name of each item inside of directory. */
    while((d = readdir(dir)) != NULL)
    {
        printf("-------------------------------\n");
        printf("File Name: %s\n", d->d_name);
        printf("-------------------------------\n");
        printf("\n\n");
    }

}



/* Function prints name + REQUESTED information of items in directory. */
void specialRun(DIR *dir, char **argv, int flag)
{
    struct stat s;
    struct dirent *d;
 
    /* Sets current directory to given directory if not left blank. VERY IMPORTANT TO FUNCTIOMALITY. *
     * DIRECTORY WILL NOT BE CORRECT WITHOUT THIS CODE (https://www.geeksforgeeks.org/chdir-in-c-language-with-examples/). */
    if(flag == 1)
    {
        chdir(argv[2]);
    }

    /* While loop handles REQUESTED stat() info utilizing code from mystat-adams.c */
    while((d = readdir(dir)) != NULL)
    {
        stat(d -> d_name, &s);

        printf("-------------------------------\n");
        printf("File Name: %s\n", d-> d_name);
        printf("-------------------------------\n");

        printf("File Size: %ld bytes\n", s.st_size);
        printf("Blocks Allocated: %ld \n", s.st_blocks);
        printf("Reference Count: %lu \n", s.st_nlink);
        printf("File Permissions: ");
    
        (S_ISDIR(s.st_mode)) ? printf("d") : printf("-");
        (s.st_mode & S_IRUSR) ? printf("r") : printf("-");
        (s.st_mode & S_IWUSR) ? printf("w") : printf("-");
        (s.st_mode & S_IXUSR) ? printf("x") : printf("-");
        (s.st_mode & S_IRGRP) ? printf("r") : printf("-");
        (s.st_mode & S_IWGRP) ? printf("w") : printf("-");
        (s.st_mode & S_IXGRP) ? printf("x") : printf("-");
        (s.st_mode & S_IROTH) ? printf("r") : printf("-");
        (s.st_mode & S_IWOTH) ? printf("w") : printf("-");
        (s.st_mode & S_IXOTH) ? printf("x") : printf("-");
        printf("\n");
        printf("UID: %d\n", s.st_uid);
        printf("GID: %d\n", s.st_uid);
        printf("Inode Number: %lu \n\n", s.st_ino);
    }
}
