all:
	gcc -ansi -pedantic -Wall -o main.exe *.c

debug:
	gcc -ansi -pedantic -Wall -d DEBUG -o main.exe *.c

clean:
	rm *.exe
