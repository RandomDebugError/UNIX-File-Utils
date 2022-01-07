#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

/* This program simulates the required fields of the stat() call. */

int main(int argc, char **argv)
{
    /* Make a stat object and call stat on the specified file. */
    struct stat s;
    stat(argv[1], &s);


   
    /* Prints the size, blocks, and number of links buy invoking the data members of the stat object. */
    printf("File Size: %ld bytes\n", s.st_size);
    printf("Blocks Allocated: %ld \n", s.st_blocks);
    printf("Reference Count: %lu \n", s.st_nlink);
    printf("File Permissions: ");
    
    /* A series of shorted if-else statements (format found: https://www.geeksforgeeks.org/conditional-or-ternary-operator-in-c-c/) that *
     * check to see for the individual permissions (https://pubs.opengroup.org/onlinepubs/007904875/basedefs/sys/stat.h.html) of the file in question. */
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

    /* Prints the inode number of the file. */
    printf("Inode Number: %lu \n", s.st_ino);

    return 0;
}

