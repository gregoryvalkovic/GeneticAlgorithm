all:
	gcc -ansi -pedantic -Wall -o main.exe *.c

debug:
	gcc -ansi -pedantic -Wall -o -d DEBUG main.exe *.c

clean:
	rm *.exe
