#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* This program prints the last N lines of a file. With lack of expected output, output formatted to preference. */

/* Delcaring global variables for use in Main and functions. */
char curChar;
int numLines,
        fp,
        position,
        lineCount = 0,
        line = 2;

/* Declaring functions. */
void processLines();
void findLines();

int main(int argc, char **argv)
{
	
    /* Declaring variable for user entered number of lines. Then adjust entered value to positive value for *
     * "-N" to int for use in program. */
	
    numLines =  (-1) * atoi(argv[1]);
    

    /* Opens file in format that can be used in lseek(). Then finds end of file. */
	fp = open(argv[2], O_RDONLY);
    position = lseek(fp, 0, SEEK_END);

	/* Invokes Function that finds the N lines from the end of the file. */
	findLines(fp, numLines, position);

    /* Invokes Function that prints the N lines at end of function, or as many as exist within file. */
	processLines(fp);
      
    /* Closes file. */
	close(fp);

    return 0;
}




/* Function uses end of file and then counts back by character till it accumulates the requested number *
 * of lines. It then sets current file position to that point. */
void findLines()
{
    /* While loop counts number of lines from end of file until it reaches numLines*/
	while (lineCount <=  numLines)
	{
        /* Reads current character. */
		read(fp, &curChar, sizeof(curChar));

        /* If its a newline char, it adds another line to the count. */
		if (curChar == '\n')
        {
            lineCount++;
        }

        /* Updates position number to 1 before current, then updates file position to match. */
		position--;
		position = lseek(fp, position, SEEK_SET);
	}
    
    /* If that position is the begining of the file following sets it to the first character of the file. *
     * Else it moves the position forward twice (once for last char of prev line and one for newline char). */
     (position == -1) ? (position++) : (position = position + 2);	

    /* Sets file position to current pos number place. */
	position = lseek(fp, position, SEEK_SET);
}


/* Function uses given position to print out rest of file from byte position. */
void processLines()
{
    int lineChar;
    
    /* Prints pramble for last N lines. */
    printf("\n-------------------------\n");
    printf("The Last %d Lines:\n", numLines);
    printf("-------------------------\n\n");
    printf("1. ");

    /* Reads current character. */
    lineChar = read(fp, &curChar, sizeof(curChar));

    /* While loop continues as long as read keeps finding valid characters. */
	while (lineChar == 1)
	{
        /* Prints current character of file. */
		printf("%c", curChar);

        /* If statement check to see if new line character represents end of requested lines. */
         if(curChar == '\n')
        {
            (line == lineCount) ? line++  : printf("%d. ", line);
            line++;
        }
        /* Reads next character for continuation of while loop. */
		lineChar = read(fp, &curChar, sizeof(curChar));
	}
}
