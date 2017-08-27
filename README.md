# Minishell - @42Born2Code

As beautiful as a shell

![Quick Demo][quick-demo]

## About

Minishell is the second project of the Unix branch at 42.
It's a minimum viable version of a real shell.
The main goal is to have a good understanding of process creation and
synchronisation using the C programmming language.

## Installation & Usage

### Requirements
The only requirements are:
- GNU make (v3.81)
- GCC (v4.2.1)

Those versions are the ones used during development.

### Building the program

1. Download/Clone this repo

        git clone https://github.com/r4meau/minishell
2. `cd` into the root directory and run `make`

        cd minishell
        make

### Running the program

After building the source, run `./minishell` from the project root.

## Main Project Instructions

### Mandatory

- Can only use C
- Must respect the school imposed coding style ([The Norme][norme-pdf])
- No memory leaks
- Implement a series of builtins: `echo`, `cd`, `setenv`, `unsetenv`, `env`, `exit`
- Manage the errors without using `errno`, by displaying a message adapted
to the error output
- Can only use these standard library functions:
    - malloc, free
    - access
    - open, close, read, write
    - opendir, readdir, closedir
    - getcwd, chdir
    - stat, lstat, fstat
    - fork, execve
    - wait, waitpid, wait3, wait4
    - signal, kill
    - exit
- Must have a Makefile to build the program
- The binary file must be named `minishell`
- Can use [Libft][libft-url]
- Handle program interruption (Ctrl + D)
- [Click here][1] for the rest

### Bonuses

- Signal management (specifically Ctrl + C)
- PATH's right management (error handling)
- Multiple commands (semi colons)


## Notes

- You can find the project instructions by [clicking here][1]
- I commented the whole codebase so it's easy to navigate and understand it.
- No need to mention the odd spacing in files, I'm using a tab size of 4.
- There are probably better ways to implement it, we are limited by a set of functions at my school (just to make it harder and give us a deeper understanding of what's happening in the back), please, review the [project instructions][1] before you explain how `X` or `Y` would have been a better way to do it ;)

## Sponsors
<a href="https://app.codesponsor.io/link/Fo4iMpT8bBWXwb54Lj7DPwqL/R4meau/minishell" rel="nofollow"><img src="https://app.codesponsor.io/embed/Fo4iMpT8bBWXwb54Lj7DPwqL/R4meau/minishell.svg" style="width: 888px; height: 68px;" alt="Sponsor" /></a>

Enjoy!

[1]: https://github.com/R4meau/minishell/blob/master/minishell.en.pdf
[quick-demo]: https://raw.githubusercontent.com/R4meau/minishell/master/minishell-quick-demo.gif?token=ADzLiR-sTesle5g6_4CQnHz4RFe69TgDks5ZK6oGwA%3D%3D
[libft-url]: https://github.com/R4meau/libft
[norme-pdf]: https://github.com/R4meau/minishell/blob/master/norme.en.pdf
