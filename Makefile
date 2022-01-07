all: stat ls tail search

stat: stat.c
	gcc -o stat stat.c

ls: ls.c
	gcc -o ls ls.c

tail: tail-.c
	gcc -o tail tail.c

search: search.c
	gcc -o search search.c
