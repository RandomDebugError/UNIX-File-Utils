all: mystat myls mytail mysearch

mystat: mystat-adams.c
	gcc -o mystat mystat-adams.c

myls: myls-adams.c
	gcc -o myls myls-adams.c

mytail: mytail-adams.c
	gcc -o mytail mytail-adams.c

mysearch: mysearch-adams.c
	gcc -o mysearch mysearch-adams.c
