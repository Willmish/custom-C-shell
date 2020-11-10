# custom-C-shell
A custom unix-like C shell


This program creates a unix-like shell which is able to execute simple `builtin` commands, specified below as well as try to execute other commands by `fork()`ing itself and executing the command as a child process.

## Short description 
The operation of this shell-like program relies on a *REPL* loop, which can be stopped with an interrupt signal or an `exit` command.

First, by default it displays a prompt, before any other operations take place. It by default consists of the current user's name, location and `??` symbol indicating this is the prompt.

### Read
The program reads from stdin all characters until a `NEWLINE` (`\n`) character is found. It dynamically allocates memory for the string and returns a pointer to that string.

## Evaluate
Next it splits the program into separate arguments (tokens) based on delimiter characters which for simplicity are taken as whitespaces. It then returns a structure containing an array of seperate arguments.

If no arguments are passed, the loop `continue`s to the next iteration. Then, the arguments are passed to an executor, which ensures that they are NULL-terminated and runs the command in a child process.

## Print
The child process runs the command and outputs to `stdout`.

 Features to add:
- Bin folder (rm command moves to the bin folder, empty every n days or when max limit reached)
- change directory
- make directory
- move file
- remove file
- move directory
- open vim
- list all elements (ls)
- omit TAB in input

less important:
- piping output
- grep
- sed
- open any program
- tmux integration/multi windowing
- change dir autofill
- command autofill
- unix Signals (SIGTERM, etc.)
- store commands in history


## References:
- Linux manual
- Bash's source code - https://git.savannah.gnu.org/cgit/bash.git/tree/
- Bash manual - https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html
- https://brennan.io/2015/01/16/write-a-shell-in-c/
