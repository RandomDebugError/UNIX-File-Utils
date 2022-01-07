#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

/* This program prints files and sub files of given directory recursively. With lack of expected output, *
 * output formatted to preference. */

int level = 0;

/* Declaring functions. */
void recursiveDirectorySearch(char *name);

int main(int argc, char **argv)
{
    
	struct dirent *d;
	DIR *dir;
	DIR *tmpDir;
	

    /* Condensed if-else learned from mystat-adams.c to handle if directory given or not. */
	(argc > 1) ? (dir = opendir(argv[1])) : (dir = opendir("."));
	
	/* Handles change of directory if directory given. VERY IMPORTNANT TO FUNCTIONALITY. */
    if(argc == 2)
    {
        chdir(argv[1]);
    }
	
    /* While loop handles first directory and recursively calls function to handle sub-directories. */
	while ((d= readdir(dir)) != NULL)
	{
		
		/* If statement checks to make sure that listed object isnt built in directory executables, *
         * which would result in infinite loop of output. */
		if (strcmp(d->d_name, ".") != 0 && strcmp(d->d_name, "..") != 0)
		{
            /* Prints name of object. */
            printf("|_ %s\n", d->d_name);

            /* Makes temp directory to check if object opens as directory. If yes it calls recursive function. *
             * struct if statement used in recursiveDirectorySearch() would not work here for some reason. */
			tmpDir = opendir(d->d_name);
			if (tmpDir != NULL)
            {
                recursiveDirectorySearch(d->d_name);
            }
            /* Closes directory. */
			closedir(tmpDir);
		}
	}
    /* Closes directory. */
	closedir(dir);

return 0;
}


/* Function uses passed directory name to execute recursivr search for files/ sub-directories. */
void recursiveDirectorySearch(char *name)
{
    struct stat s;
	struct dirent *d;
	DIR *dir;
    int i = 0; 
	
    
    dir = opendir(name);

    /* VERY IMPORTNANT TO FUNCTIONALITY. Changes current directory to whatever directory is being used *
     * by iteration of recursive call. WITHOUT THIS, PROGRAM WILL TREAT ALL FILES WITHIN DIRECTORY AS "D" OBJECTS *
     * THUS ONLY OUTPUTTING OBJECT NAMES, AND NOT SUB-FOLDER INFO. */
    chdir(name);
    
    /* Increases level depth. */
    level++;
	
    /* While loop does actions similar to main function while loop but supports functionality for recursive calls. */
	while ((d = readdir(dir)) != NULL)
	{
        /* Calls Stat on object for use in if statement. */
        stat(d->d_name, &s);

        /* Prints number of tabs equal to directory depth for aesthetics. */
		while ( i < level)
        {
            printf("\t");
            i++;
        }
			i = 0;

		
		/* If statement handles if object is not "." or "..". VERY IMPORTANT TO SAVE FROM INFINITE PRINT LOOP. */
		if (strcmp(d->d_name, ".") != 0 && strcmp(d->d_name, "..") != 0)
		{
            printf("|_ %s", d->d_name);
            
            /* Uses Stat() results to check if object is a directory, if yes then it calls recursive call of current *
             * function. then changes directory after it returns form recursive to parent directory do that next *
             * directory call of function can process correctly. */
			if ((S_ISDIR(s.st_mode)))
            {
				recursiveDirectorySearch(d->d_name);
                chdir(".."); 
            }	
		}
		printf("\n");
	}
	/* Closes directory. */
	closedir(dir);
}
