# custom-C-shell
A custom unix-like C shell


This program creates a unix-like shell which is able to execute simple `builtin` commands, specified below as well as try to execute other commands by `fork()`ing itself and executing the command as a child process.

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
- https://brennan.io/2015/01/16/write-a-shell-in-c/
