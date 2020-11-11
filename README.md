# custom-C-shell
A custom unix-like C shell


This program creates a unix-like shell which is able to execute simple `builtin` commands, specified below as well as try to execute other commands by `fork()`ing itself and executing the command as a child process.

## Short description 
The operation of this shell-like program relies on a *REPL* loop, which can be stopped with an EOF or an `exit` command.

First, by default it displays a prompt, before any other operations take place. It by default consists of the current user's name, location and `??` symbol indicating this is the prompt.

### Read
The program reads from `stdin` all characters until a `NEWLINE` (`\n`) character is found. It dynamically allocates memory for the string and returns a pointer to that string. (using `getline`)

### Evaluate
Next it splits the program into separate arguments (tokens) based on delimiter characters which for simplicity are taken as whitespaces. It then returns a structure containing an array of seperate arguments.

If no arguments are passed, the loop `continue`s to the next iteration.
It then checks whether the command is a `builtin` command. If so, it passes its arguments to an apropriate function.

Otherwise, the arguments are passed to an executor, which ensures that they are NULL-terminated and searches for the command in `$PATH` and, if found, executes it in a child process. If it's not found, a message is printed to `stdout` informing the user.

### Print
If a builtin command was run, any output is printed to `stdout` and all errors are passed back for error handling.
If the command run was not a builtin, the child process runs the command and outputs to `stdout`. Any errors encountered are also displayed at `stdout`.


### Exiting the shell
The shell can be exited (stopped) by the builtin `exit`command or by an EOF (`Ctrl+D`). It will not be stopped by an interrupt signal (`SIGINT`) (`Ctrl+C`) or by a stop signal (`SIGTSTP`) (`Ctrl+Z`).

### Commands available
Currently, builtin commands available are:
- `cd [dir]` - Allows changing directory (takes a single argument)
- `exit` - Exits the shell
- `help` - Displays a short message with a list of builtin commands
- `history [n]` - Displays the history of the current session. If n is specified, displays last `n` commands.

## Running the program
In order to build the program, enter the `/src` directory and run the command `make`. This should call the simple makefile which is basically calling the command:
`gcc -o szsh main.c shell.c ui.c commands.c structures.c`

Then simply run the executable `szsh` (`./szsh` command).




## References:
- Linux manual (man pages)
- Bash's source code - https://git.savannah.gnu.org/cgit/bash.git/tree/
- Bash manual - https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html
- https://brennan.io/2015/01/16/write-a-shell-in-c/
- https://github.com/moisam/lets-build-a-linux-shell
