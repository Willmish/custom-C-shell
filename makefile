szshell: main.c shell.c ui.c commands.c structures.c
	gcc -o szsh main.c shell.c ui.c commands.c structures.c

clean:
	rm szsh
