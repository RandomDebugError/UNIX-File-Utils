# UNIX-File-Utils
Programs that emulate common UNIX Utils


4 seperate programs written in C that emulate the STAT, List Files, Tail, and Recursive Search UNIX Utils.

Stat: Calls stat() on given file/directory and returns file size, # of blocks allocated, link count, file permissions, and file inode.

List: Lists the fills in a given directory. Invoking with -l flag returns information about the files.

Tail: Returns the last n lines of a file where n = the number of desired lines.

Recursive Search: Returns the names of each file and directory in the file system tree recursively.
